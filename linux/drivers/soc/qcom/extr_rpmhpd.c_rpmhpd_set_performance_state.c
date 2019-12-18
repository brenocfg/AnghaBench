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
struct rpmhpd {int level_count; unsigned int* level; int corner; scalar_t__ enabled; } ;
struct generic_pm_domain {int dummy; } ;

/* Variables and functions */
 struct rpmhpd* domain_to_rpmhpd (struct generic_pm_domain*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int rpmhpd_aggregate_corner (struct rpmhpd*,int) ; 
 int /*<<< orphan*/  rpmhpd_lock ; 

__attribute__((used)) static int rpmhpd_set_performance_state(struct generic_pm_domain *domain,
					unsigned int level)
{
	struct rpmhpd *pd = domain_to_rpmhpd(domain);
	int ret = 0, i;

	mutex_lock(&rpmhpd_lock);

	for (i = 0; i < pd->level_count; i++)
		if (level <= pd->level[i])
			break;

	/*
	 * If the level requested is more than that supported by the
	 * max corner, just set it to max anyway.
	 */
	if (i == pd->level_count)
		i--;

	if (pd->enabled) {
		ret = rpmhpd_aggregate_corner(pd, i);
		if (ret)
			goto out;
	}

	pd->corner = i;
out:
	mutex_unlock(&rpmhpd_lock);

	return ret;
}