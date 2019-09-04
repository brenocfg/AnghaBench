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
struct list_head {int dummy; } ;
struct gov_attr_set {int usage_count; int /*<<< orphan*/  policy_list; int /*<<< orphan*/  update_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add (struct list_head*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

void gov_attr_set_init(struct gov_attr_set *attr_set, struct list_head *list_node)
{
	INIT_LIST_HEAD(&attr_set->policy_list);
	mutex_init(&attr_set->update_lock);
	attr_set->usage_count = 1;
	list_add(list_node, &attr_set->policy_list);
}