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
struct rlb_client_info {scalar_t__ vlan_id; int /*<<< orphan*/ * slave; scalar_t__ assigned; void* used_prev; void* used_next; } ;

/* Variables and functions */
 void* RLB_NULL_INDEX ; 

__attribute__((used)) static void rlb_init_table_entry_dst(struct rlb_client_info *entry)
{
	entry->used_next = RLB_NULL_INDEX;
	entry->used_prev = RLB_NULL_INDEX;
	entry->assigned = 0;
	entry->slave = NULL;
	entry->vlan_id = 0;
}