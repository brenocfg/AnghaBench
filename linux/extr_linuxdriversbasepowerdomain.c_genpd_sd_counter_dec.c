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
struct generic_pm_domain {int /*<<< orphan*/  sd_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool genpd_sd_counter_dec(struct generic_pm_domain *genpd)
{
	bool ret = false;

	if (!WARN_ON(atomic_read(&genpd->sd_count) == 0))
		ret = !!atomic_dec_and_test(&genpd->sd_count);

	return ret;
}