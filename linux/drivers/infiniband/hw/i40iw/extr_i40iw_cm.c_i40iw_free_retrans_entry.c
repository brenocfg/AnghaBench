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
struct i40iw_timer_entry {scalar_t__ sqbuf; } ;
struct i40iw_device {int /*<<< orphan*/  vsi; } ;
struct i40iw_cm_node {int /*<<< orphan*/  ref_count; struct i40iw_timer_entry* send_entry; struct i40iw_device* iwdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i40iw_free_sqbuf (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  kfree (struct i40iw_timer_entry*) ; 

__attribute__((used)) static void i40iw_free_retrans_entry(struct i40iw_cm_node *cm_node)
{
	struct i40iw_device *iwdev = cm_node->iwdev;
	struct i40iw_timer_entry *send_entry;

	send_entry = cm_node->send_entry;
	if (send_entry) {
		cm_node->send_entry = NULL;
		i40iw_free_sqbuf(&iwdev->vsi, (void *)send_entry->sqbuf);
		kfree(send_entry);
		atomic_dec(&cm_node->ref_count);
	}
}