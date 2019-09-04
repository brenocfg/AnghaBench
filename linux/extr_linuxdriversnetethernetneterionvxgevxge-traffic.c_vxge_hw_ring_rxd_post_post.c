#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vxge_hw_ring_rxd_1 {int /*<<< orphan*/  control_0; } ;
struct __vxge_hw_ring {TYPE_2__* stats; } ;
struct TYPE_3__ {scalar_t__ usage_cnt; } ;
struct TYPE_4__ {TYPE_1__ common_stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  VXGE_HW_RING_RXD_LIST_OWN_ADAPTER ; 

void vxge_hw_ring_rxd_post_post(struct __vxge_hw_ring *ring, void *rxdh)
{
	struct vxge_hw_ring_rxd_1 *rxdp = (struct vxge_hw_ring_rxd_1 *)rxdh;

	rxdp->control_0	= VXGE_HW_RING_RXD_LIST_OWN_ADAPTER;

	if (ring->stats->common_stats.usage_cnt > 0)
		ring->stats->common_stats.usage_cnt--;
}