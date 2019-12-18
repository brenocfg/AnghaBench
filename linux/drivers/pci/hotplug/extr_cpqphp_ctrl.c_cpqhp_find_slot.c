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
typedef  scalar_t__ u8 ;
struct slot {scalar_t__ device; struct slot* next; } ;
struct controller {struct slot* slot; } ;

/* Variables and functions */

__attribute__((used)) static struct slot *cpqhp_find_slot(struct controller *ctrl, u8 device)
{
	struct slot *slot = ctrl->slot;

	while (slot && (slot->device != device))
		slot = slot->next;

	return slot;
}