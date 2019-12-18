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
struct sys_t_policy_node {int /*<<< orphan*/  ts_interval; } ;
struct mutex {int dummy; } ;
struct config_item {TYPE_2__* ci_group; } ;
typedef  size_t ssize_t ;
struct TYPE_4__ {TYPE_1__* cg_subsys; } ;
struct TYPE_3__ {struct mutex su_mutex; } ;

/* Variables and functions */
 int kstrtouint (char const*,int,unsigned int*) ; 
 int /*<<< orphan*/  msecs_to_jiffies (unsigned int) ; 
 int /*<<< orphan*/  mutex_lock (struct mutex*) ; 
 int /*<<< orphan*/  mutex_unlock (struct mutex*) ; 
 struct sys_t_policy_node* to_pdrv_policy_node (struct config_item*) ; 

__attribute__((used)) static ssize_t
sys_t_policy_ts_interval_store(struct config_item *item, const char *page,
			       size_t count)
{
	struct mutex *mutexp = &item->ci_group->cg_subsys->su_mutex;
	struct sys_t_policy_node *pn = to_pdrv_policy_node(item);
	unsigned int ms;
	int ret;

	mutex_lock(mutexp);
	ret = kstrtouint(page, 10, &ms);
	mutex_unlock(mutexp);

	if (!ret) {
		pn->ts_interval = msecs_to_jiffies(ms);
		return count;
	}

	return ret;
}