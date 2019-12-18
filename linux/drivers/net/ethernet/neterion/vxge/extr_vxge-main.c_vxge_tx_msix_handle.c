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
struct vxge_fifo {int /*<<< orphan*/  tx_vector_no; scalar_t__ handle; } ;
struct __vxge_hw_channel {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  VXGE_COMPLETE_VPATH_TX (struct vxge_fifo*) ; 
 int /*<<< orphan*/  adaptive_coalesce_tx_interrupts (struct vxge_fifo*) ; 
 int /*<<< orphan*/  vxge_hw_channel_msix_clear (struct __vxge_hw_channel*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vxge_hw_channel_msix_mask (struct __vxge_hw_channel*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vxge_hw_channel_msix_unmask (struct __vxge_hw_channel*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t vxge_tx_msix_handle(int irq, void *dev_id)
{
	struct vxge_fifo *fifo = (struct vxge_fifo *)dev_id;

	adaptive_coalesce_tx_interrupts(fifo);

	vxge_hw_channel_msix_mask((struct __vxge_hw_channel *)fifo->handle,
				  fifo->tx_vector_no);

	vxge_hw_channel_msix_clear((struct __vxge_hw_channel *)fifo->handle,
				   fifo->tx_vector_no);

	VXGE_COMPLETE_VPATH_TX(fifo);

	vxge_hw_channel_msix_unmask((struct __vxge_hw_channel *)fifo->handle,
				    fifo->tx_vector_no);

	return IRQ_HANDLED;
}