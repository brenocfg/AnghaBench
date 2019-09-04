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
struct hns3_enet_ring_group {scalar_t__ count; int /*<<< orphan*/ * ring; } ;

/* Variables and functions */

__attribute__((used)) static void hns3_clear_ring_group(struct hns3_enet_ring_group *group)
{
	group->ring = NULL;
	group->count = 0;
}