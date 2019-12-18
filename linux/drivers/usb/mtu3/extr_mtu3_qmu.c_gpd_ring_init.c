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
struct mtu3_gpd_ring {struct qmu_gpd* end; struct qmu_gpd* dequeue; struct qmu_gpd* enqueue; struct qmu_gpd* start; } ;

/* Variables and functions */
 int MAX_GPD_NUM ; 

__attribute__((used)) static void gpd_ring_init(struct mtu3_gpd_ring *ring, struct qmu_gpd *gpd)
{
	ring->start = gpd;
	ring->enqueue = gpd;
	ring->dequeue = gpd;
	ring->end = gpd + MAX_GPD_NUM - 1;
}