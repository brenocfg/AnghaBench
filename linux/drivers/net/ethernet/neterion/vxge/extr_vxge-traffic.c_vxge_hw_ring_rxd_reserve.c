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
struct vxge_hw_ring_rxd_1 {scalar_t__ control_1; scalar_t__ control_0; } ;
struct __vxge_hw_channel {int dummy; } ;
struct __vxge_hw_ring {struct __vxge_hw_channel channel; } ;
typedef  enum vxge_hw_status { ____Placeholder_vxge_hw_status } vxge_hw_status ;

/* Variables and functions */
 int VXGE_HW_OK ; 
 int vxge_hw_channel_dtr_alloc (struct __vxge_hw_channel*,void**) ; 

enum vxge_hw_status vxge_hw_ring_rxd_reserve(struct __vxge_hw_ring *ring,
	void **rxdh)
{
	enum vxge_hw_status status;
	struct __vxge_hw_channel *channel;

	channel = &ring->channel;

	status = vxge_hw_channel_dtr_alloc(channel, rxdh);

	if (status == VXGE_HW_OK) {
		struct vxge_hw_ring_rxd_1 *rxdp =
			(struct vxge_hw_ring_rxd_1 *)*rxdh;

		rxdp->control_0	= rxdp->control_1 = 0;
	}

	return status;
}