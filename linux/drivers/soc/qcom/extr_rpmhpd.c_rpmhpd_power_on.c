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
struct rpmhpd {int enabled; scalar_t__ corner; } ;
struct generic_pm_domain {int dummy; } ;

/* Variables and functions */
 struct rpmhpd* domain_to_rpmhpd (struct generic_pm_domain*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int rpmhpd_aggregate_corner (struct rpmhpd*,scalar_t__) ; 
 int /*<<< orphan*/  rpmhpd_lock ; 

__attribute__((used)) static int rpmhpd_power_on(struct generic_pm_domain *domain)
{
	struct rpmhpd *pd = domain_to_rpmhpd(domain);
	int ret = 0;

	mutex_lock(&rpmhpd_lock);

	if (pd->corner)
		ret = rpmhpd_aggregate_corner(pd, pd->corner);

	if (!ret)
		pd->enabled = true;

	mutex_unlock(&rpmhpd_lock);

	return ret;
}