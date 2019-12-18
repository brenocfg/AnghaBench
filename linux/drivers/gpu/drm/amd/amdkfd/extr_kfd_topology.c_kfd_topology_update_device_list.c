#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct list_head {int /*<<< orphan*/  next; } ;
struct TYPE_2__ {int /*<<< orphan*/  num_devices; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_empty (struct list_head*) ; 
 int /*<<< orphan*/  list_move_tail (int /*<<< orphan*/ ,struct list_head*) ; 
 TYPE_1__ sys_props ; 

__attribute__((used)) static void kfd_topology_update_device_list(struct list_head *temp_list,
					struct list_head *master_list)
{
	while (!list_empty(temp_list)) {
		list_move_tail(temp_list->next, master_list);
		sys_props.num_devices++;
	}
}