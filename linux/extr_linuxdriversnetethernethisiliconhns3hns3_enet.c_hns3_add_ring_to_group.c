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
struct hns3_enet_ring_group {int /*<<< orphan*/  count; struct hns3_enet_ring* ring; } ;
struct hns3_enet_ring {struct hns3_enet_ring* next; } ;

/* Variables and functions */

__attribute__((used)) static void hns3_add_ring_to_group(struct hns3_enet_ring_group *group,
				   struct hns3_enet_ring *ring)
{
	ring->next = group->ring;
	group->ring = ring;

	group->count++;
}