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
typedef  int /*<<< orphan*/  u32 ;
struct vmw_private {int /*<<< orphan*/  traces_state; int /*<<< orphan*/  enable_state; int /*<<< orphan*/  config_done_state; int /*<<< orphan*/  last_read_seqno; int /*<<< orphan*/ * mmio_virt; } ;
struct vmw_fifo_state {int /*<<< orphan*/ * dynamic_buffer; int /*<<< orphan*/ * static_buffer; int /*<<< orphan*/  marker_queue; } ;

/* Variables and functions */
 int SVGA_FIFO_FENCE ; 
 int /*<<< orphan*/  SVGA_REG_BUSY ; 
 int /*<<< orphan*/  SVGA_REG_CONFIG_DONE ; 
 int /*<<< orphan*/  SVGA_REG_ENABLE ; 
 int /*<<< orphan*/  SVGA_REG_SYNC ; 
 int /*<<< orphan*/  SVGA_REG_TRACES ; 
 int /*<<< orphan*/  SVGA_SYNC_GENERIC ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmw_marker_queue_takedown (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmw_mmio_read (int /*<<< orphan*/ *) ; 
 scalar_t__ vmw_read (struct vmw_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmw_write (struct vmw_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void vmw_fifo_release(struct vmw_private *dev_priv, struct vmw_fifo_state *fifo)
{
	u32  *fifo_mem = dev_priv->mmio_virt;

	vmw_write(dev_priv, SVGA_REG_SYNC, SVGA_SYNC_GENERIC);
	while (vmw_read(dev_priv, SVGA_REG_BUSY) != 0)
		;

	dev_priv->last_read_seqno = vmw_mmio_read(fifo_mem + SVGA_FIFO_FENCE);

	vmw_write(dev_priv, SVGA_REG_CONFIG_DONE,
		  dev_priv->config_done_state);
	vmw_write(dev_priv, SVGA_REG_ENABLE,
		  dev_priv->enable_state);
	vmw_write(dev_priv, SVGA_REG_TRACES,
		  dev_priv->traces_state);

	vmw_marker_queue_takedown(&fifo->marker_queue);

	if (likely(fifo->static_buffer != NULL)) {
		vfree(fifo->static_buffer);
		fifo->static_buffer = NULL;
	}

	if (likely(fifo->dynamic_buffer != NULL)) {
		vfree(fifo->dynamic_buffer);
		fifo->dynamic_buffer = NULL;
	}
}