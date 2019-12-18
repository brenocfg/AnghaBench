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
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  u32 ;
struct vmw_private {scalar_t__ last_read_seqno; int /*<<< orphan*/  fman; int /*<<< orphan*/ * mmio_virt; } ;
struct vmw_fifo_state {int /*<<< orphan*/  marker_queue; } ;

/* Variables and functions */
 int SVGA_FIFO_FENCE ; 
 int /*<<< orphan*/  vmw_fences_update (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmw_marker_pull (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ vmw_mmio_read (int /*<<< orphan*/ *) ; 

void vmw_update_seqno(struct vmw_private *dev_priv,
			 struct vmw_fifo_state *fifo_state)
{
	u32 *fifo_mem = dev_priv->mmio_virt;
	uint32_t seqno = vmw_mmio_read(fifo_mem + SVGA_FIFO_FENCE);

	if (dev_priv->last_read_seqno != seqno) {
		dev_priv->last_read_seqno = seqno;
		vmw_marker_pull(&fifo_state->marker_queue, seqno);
		vmw_fences_update(dev_priv->fman);
	}
}