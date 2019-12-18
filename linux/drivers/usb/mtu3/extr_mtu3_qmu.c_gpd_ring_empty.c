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
struct qmu_gpd {int dummy; } ;
struct mtu3_gpd_ring {struct qmu_gpd* dequeue; struct qmu_gpd* start; struct qmu_gpd* end; struct qmu_gpd* enqueue; } ;

/* Variables and functions */

__attribute__((used)) static int gpd_ring_empty(struct mtu3_gpd_ring *ring)
{
	struct qmu_gpd *enq = ring->enqueue;
	struct qmu_gpd *next;

	if (ring->enqueue < ring->end)
		next = enq + 1;
	else
		next = ring->start;

	/* one gpd is reserved to simplify gpd preparation */
	return next == ring->dequeue;
}