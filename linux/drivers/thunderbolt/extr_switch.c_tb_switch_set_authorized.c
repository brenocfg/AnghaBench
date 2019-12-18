#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  kobj; } ;
struct tb_switch {int authorized; TYPE_2__* tb; TYPE_1__ dev; int /*<<< orphan*/  key; } ;
struct TYPE_6__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  KOBJ_CHANGE ; 
 int /*<<< orphan*/  kobject_uevent (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int restart_syscall () ; 
 int tb_domain_approve_switch (TYPE_2__*,struct tb_switch*) ; 
 int tb_domain_approve_switch_key (TYPE_2__*,struct tb_switch*) ; 
 int tb_domain_challenge_switch_key (TYPE_2__*,struct tb_switch*) ; 

__attribute__((used)) static int tb_switch_set_authorized(struct tb_switch *sw, unsigned int val)
{
	int ret = -EINVAL;

	if (!mutex_trylock(&sw->tb->lock))
		return restart_syscall();

	if (sw->authorized)
		goto unlock;

	switch (val) {
	/* Approve switch */
	case 1:
		if (sw->key)
			ret = tb_domain_approve_switch_key(sw->tb, sw);
		else
			ret = tb_domain_approve_switch(sw->tb, sw);
		break;

	/* Challenge switch */
	case 2:
		if (sw->key)
			ret = tb_domain_challenge_switch_key(sw->tb, sw);
		break;

	default:
		break;
	}

	if (!ret) {
		sw->authorized = val;
		/* Notify status change to the userspace */
		kobject_uevent(&sw->dev.kobj, KOBJ_CHANGE);
	}

unlock:
	mutex_unlock(&sw->tb->lock);
	return ret;
}