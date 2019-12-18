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
struct opp_table {int required_opp_count; int /*<<< orphan*/ ** genpd_virt_devs; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_pm_domain_detach (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ **) ; 

__attribute__((used)) static void _opp_detach_genpd(struct opp_table *opp_table)
{
	int index;

	for (index = 0; index < opp_table->required_opp_count; index++) {
		if (!opp_table->genpd_virt_devs[index])
			continue;

		dev_pm_domain_detach(opp_table->genpd_virt_devs[index], false);
		opp_table->genpd_virt_devs[index] = NULL;
	}

	kfree(opp_table->genpd_virt_devs);
	opp_table->genpd_virt_devs = NULL;
}