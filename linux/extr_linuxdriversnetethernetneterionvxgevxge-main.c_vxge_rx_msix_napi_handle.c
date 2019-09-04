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
struct vxge_ring {int /*<<< orphan*/  napi; int /*<<< orphan*/  rx_vector_no; scalar_t__ handle; } ;
struct __vxge_hw_channel {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  adaptive_coalesce_rx_interrupts (struct vxge_ring*) ; 
 int /*<<< orphan*/  napi_schedule (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vxge_hw_channel_msix_clear (struct __vxge_hw_channel*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vxge_hw_channel_msix_mask (struct __vxge_hw_channel*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t vxge_rx_msix_napi_handle(int irq, void *dev_id)
{
	struct vxge_ring *ring = (struct vxge_ring *)dev_id;

	adaptive_coalesce_rx_interrupts(ring);

	vxge_hw_channel_msix_mask((struct __vxge_hw_channel *)ring->handle,
				  ring->rx_vector_no);

	vxge_hw_channel_msix_clear((struct __vxge_hw_channel *)ring->handle,
				   ring->rx_vector_no);

	napi_schedule(&ring->napi);
	return IRQ_HANDLED;
}