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
struct stm_device {int /*<<< orphan*/  pdrv; int /*<<< orphan*/ * policy; int /*<<< orphan*/  policy_mutex; } ;

/* Variables and functions */
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stm_put_device (struct stm_device*) ; 
 int /*<<< orphan*/  stm_put_protocol (int /*<<< orphan*/ ) ; 

void stp_policy_unbind(struct stp_policy *policy)
{
	struct stm_device *stm = policy->stm;

	/*
	 * stp_policy_release() will not call here if the policy is already
	 * unbound; other users should not either, as no link exists between
	 * this policy and anything else in that case
	 */
	if (WARN_ON_ONCE(!policy->stm))
		return;

	lockdep_assert_held(&stm->policy_mutex);

	stm->policy = NULL;
	policy->stm = NULL;

	stm_put_protocol(stm->pdrv);
	stm_put_device(stm);
}