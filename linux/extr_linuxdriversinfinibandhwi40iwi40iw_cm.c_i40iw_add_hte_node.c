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
struct i40iw_cm_node {int /*<<< orphan*/  list; } ;
struct i40iw_cm_core {int /*<<< orphan*/  ht_lock; int /*<<< orphan*/  non_accelerated_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  i40iw_pr_err (char*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void i40iw_add_hte_node(struct i40iw_cm_core *cm_core,
			       struct i40iw_cm_node *cm_node)
{
	unsigned long flags;

	if (!cm_node || !cm_core) {
		i40iw_pr_err("cm_node or cm_core == NULL\n");
		return;
	}

	spin_lock_irqsave(&cm_core->ht_lock, flags);
	list_add_tail(&cm_node->list, &cm_core->non_accelerated_list);
	spin_unlock_irqrestore(&cm_core->ht_lock, flags);
}