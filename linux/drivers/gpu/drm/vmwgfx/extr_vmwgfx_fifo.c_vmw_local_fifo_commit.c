#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  u32 ;
struct vmw_temp_set_context {int dummy; } ;
struct vmw_fifo_state {int capabilities; int dx; int reserved_size; int /*<<< orphan*/  fifo_mutex; int /*<<< orphan*/  rwsem; scalar_t__ using_bounce_buffer; int /*<<< orphan*/ * dynamic_buffer; } ;
struct vmw_private {int /*<<< orphan*/ * mmio_virt; struct vmw_fifo_state fifo; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int SVGA_FIFO_CAP_RESERVE ; 
 int SVGA_FIFO_MAX ; 
 int SVGA_FIFO_MIN ; 
 int SVGA_FIFO_NEXT_CMD ; 
 int SVGA_FIFO_RESERVED ; 
 int /*<<< orphan*/  SVGA_SYNC_GENERIC ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmw_fifo_ping_host (struct vmw_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmw_fifo_res_copy (struct vmw_fifo_state*,int /*<<< orphan*/ *,int,int,int,int) ; 
 int /*<<< orphan*/  vmw_fifo_slow_copy (struct vmw_fifo_state*,int /*<<< orphan*/ *,int,int,int,int) ; 
 int vmw_mmio_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmw_mmio_write (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void vmw_local_fifo_commit(struct vmw_private *dev_priv, uint32_t bytes)
{
	struct vmw_fifo_state *fifo_state = &dev_priv->fifo;
	u32  *fifo_mem = dev_priv->mmio_virt;
	uint32_t next_cmd = vmw_mmio_read(fifo_mem + SVGA_FIFO_NEXT_CMD);
	uint32_t max = vmw_mmio_read(fifo_mem + SVGA_FIFO_MAX);
	uint32_t min = vmw_mmio_read(fifo_mem + SVGA_FIFO_MIN);
	bool reserveable = fifo_state->capabilities & SVGA_FIFO_CAP_RESERVE;

	if (fifo_state->dx)
		bytes += sizeof(struct vmw_temp_set_context);

	fifo_state->dx = false;
	BUG_ON((bytes & 3) != 0);
	BUG_ON(bytes > fifo_state->reserved_size);

	fifo_state->reserved_size = 0;

	if (fifo_state->using_bounce_buffer) {
		if (reserveable)
			vmw_fifo_res_copy(fifo_state, fifo_mem,
					  next_cmd, max, min, bytes);
		else
			vmw_fifo_slow_copy(fifo_state, fifo_mem,
					   next_cmd, max, min, bytes);

		if (fifo_state->dynamic_buffer) {
			vfree(fifo_state->dynamic_buffer);
			fifo_state->dynamic_buffer = NULL;
		}

	}

	down_write(&fifo_state->rwsem);
	if (fifo_state->using_bounce_buffer || reserveable) {
		next_cmd += bytes;
		if (next_cmd >= max)
			next_cmd -= max - min;
		mb();
		vmw_mmio_write(next_cmd, fifo_mem + SVGA_FIFO_NEXT_CMD);
	}

	if (reserveable)
		vmw_mmio_write(0, fifo_mem + SVGA_FIFO_RESERVED);
	mb();
	up_write(&fifo_state->rwsem);
	vmw_fifo_ping_host(dev_priv, SVGA_SYNC_GENERIC);
	mutex_unlock(&fifo_state->fifo_mutex);
}