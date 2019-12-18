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
struct generic_pm_domain {int flags; int /*<<< orphan*/  power_on; int /*<<< orphan*/  power_off; int /*<<< orphan*/  detach_dev; int /*<<< orphan*/  attach_dev; } ;
struct rmobile_pm_domain {struct dev_power_governor* gov; struct generic_pm_domain genpd; } ;
struct dev_power_governor {int dummy; } ;

/* Variables and functions */
 int GENPD_FLAG_ACTIVE_WAKEUP ; 
 int GENPD_FLAG_ALWAYS_ON ; 
 int GENPD_FLAG_PM_CLK ; 
 int /*<<< orphan*/  __rmobile_pd_power_up (struct rmobile_pm_domain*) ; 
 int /*<<< orphan*/  cpg_mstp_attach_dev ; 
 int /*<<< orphan*/  cpg_mstp_detach_dev ; 
 int /*<<< orphan*/  pm_genpd_init (struct generic_pm_domain*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  rmobile_pd_power_down ; 
 int /*<<< orphan*/  rmobile_pd_power_up ; 
 int /*<<< orphan*/  simple_qos_governor ; 

__attribute__((used)) static void rmobile_init_pm_domain(struct rmobile_pm_domain *rmobile_pd)
{
	struct generic_pm_domain *genpd = &rmobile_pd->genpd;
	struct dev_power_governor *gov = rmobile_pd->gov;

	genpd->flags |= GENPD_FLAG_PM_CLK | GENPD_FLAG_ACTIVE_WAKEUP;
	genpd->attach_dev = cpg_mstp_attach_dev;
	genpd->detach_dev = cpg_mstp_detach_dev;

	if (!(genpd->flags & GENPD_FLAG_ALWAYS_ON)) {
		genpd->power_off = rmobile_pd_power_down;
		genpd->power_on = rmobile_pd_power_up;
		__rmobile_pd_power_up(rmobile_pd);
	}

	pm_genpd_init(genpd, gov ? : &simple_qos_governor, false);
}