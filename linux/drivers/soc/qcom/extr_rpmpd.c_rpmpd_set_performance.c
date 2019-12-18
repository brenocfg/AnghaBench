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
struct rpmpd {unsigned int max_state; unsigned int corner; scalar_t__ key; int /*<<< orphan*/  enabled; } ;
struct generic_pm_domain {int dummy; } ;

/* Variables and functions */
 scalar_t__ KEY_FLOOR_CORNER ; 
 scalar_t__ KEY_FLOOR_LEVEL ; 
 struct rpmpd* domain_to_rpmpd (struct generic_pm_domain*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int rpmpd_aggregate_corner (struct rpmpd*) ; 
 int /*<<< orphan*/  rpmpd_lock ; 

__attribute__((used)) static int rpmpd_set_performance(struct generic_pm_domain *domain,
				 unsigned int state)
{
	int ret = 0;
	struct rpmpd *pd = domain_to_rpmpd(domain);

	if (state > pd->max_state)
		state = pd->max_state;

	mutex_lock(&rpmpd_lock);

	pd->corner = state;

	/* Always send updates for vfc and vfl */
	if (!pd->enabled && pd->key != KEY_FLOOR_CORNER &&
	    pd->key != KEY_FLOOR_LEVEL)
		goto out;

	ret = rpmpd_aggregate_corner(pd);

out:
	mutex_unlock(&rpmpd_lock);

	return ret;
}