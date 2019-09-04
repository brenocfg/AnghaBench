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
struct stp_policy {struct stm_device* stm; } ;
struct stm_device {int /*<<< orphan*/  policy_mutex; } ;
struct config_item {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct stp_policy*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stp_policy_unbind (struct stp_policy*) ; 
 struct stp_policy* to_stp_policy (struct config_item*) ; 

__attribute__((used)) static void stp_policy_release(struct config_item *item)
{
	struct stp_policy *policy = to_stp_policy(item);
	struct stm_device *stm = policy->stm;

	/* a policy *can* be unbound and still exist in configfs tree */
	if (!stm)
		return;

	mutex_lock(&stm->policy_mutex);
	stp_policy_unbind(policy);
	mutex_unlock(&stm->policy_mutex);

	kfree(policy);
}