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
struct gov_attr_set {int /*<<< orphan*/  update_lock; int /*<<< orphan*/  policy_list; int /*<<< orphan*/  usage_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add (struct list_head*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void gov_attr_set_get(struct gov_attr_set *attr_set, struct list_head *list_node)
{
	mutex_lock(&attr_set->update_lock);
	attr_set->usage_count++;
	list_add(list_node, &attr_set->policy_list);
	mutex_unlock(&attr_set->update_lock);
}