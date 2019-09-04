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
struct __vxge_hw_ring {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  vxge_hw_ring_rxd_post_post (struct __vxge_hw_ring*,void*) ; 
 int /*<<< orphan*/  wmb () ; 

void vxge_hw_ring_rxd_post_post_wmb(struct __vxge_hw_ring *ring, void *rxdh)
{
	wmb();
	vxge_hw_ring_rxd_post_post(ring, rxdh);
}