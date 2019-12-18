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
struct mtu3_gpd_ring {scalar_t__ dequeue; scalar_t__ end; scalar_t__ start; } ;

/* Variables and functions */

__attribute__((used)) static struct qmu_gpd *advance_deq_gpd(struct mtu3_gpd_ring *ring)
{
	if (ring->dequeue < ring->end)
		ring->dequeue++;
	else
		ring->dequeue = ring->start;

	return ring->dequeue;
}