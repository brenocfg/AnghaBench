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
struct rpmpd {int enabled; } ;
struct generic_pm_domain {int dummy; } ;

/* Variables and functions */
 struct rpmpd* domain_to_rpmpd (struct generic_pm_domain*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rpmpd_lock ; 
 int rpmpd_send_enable (struct rpmpd*,int) ; 

__attribute__((used)) static int rpmpd_power_off(struct generic_pm_domain *domain)
{
	int ret;
	struct rpmpd *pd = domain_to_rpmpd(domain);

	mutex_lock(&rpmpd_lock);

	ret = rpmpd_send_enable(pd, false);
	if (!ret)
		pd->enabled = false;

	mutex_unlock(&rpmpd_lock);

	return ret;
}