#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sys_t_policy_node {int /*<<< orphan*/  uuid; } ;
struct mutex {int dummy; } ;
struct config_item {TYPE_2__* ci_group; } ;
typedef  int ssize_t ;
struct TYPE_4__ {TYPE_1__* cg_subsys; } ;
struct TYPE_3__ {struct mutex su_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (struct mutex*) ; 
 int /*<<< orphan*/  mutex_unlock (struct mutex*) ; 
 struct sys_t_policy_node* to_pdrv_policy_node (struct config_item*) ; 
 int uuid_parse (char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t
sys_t_policy_uuid_store(struct config_item *item, const char *page,
			size_t count)
{
	struct mutex *mutexp = &item->ci_group->cg_subsys->su_mutex;
	struct sys_t_policy_node *pn = to_pdrv_policy_node(item);
	int ret;

	mutex_lock(mutexp);
	ret = uuid_parse(page, &pn->uuid);
	mutex_unlock(mutexp);

	return ret < 0 ? ret : count;
}