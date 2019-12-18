#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct rapl_package {int nr_domains; int /*<<< orphan*/  plist; TYPE_1__* priv; int /*<<< orphan*/  name; struct rapl_domain* domains; } ;
struct rapl_domain {scalar_t__ id; int /*<<< orphan*/  power_zone; int /*<<< orphan*/  name; } ;
struct TYPE_2__ {int /*<<< orphan*/  control_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  PL1_CLAMP ; 
 int /*<<< orphan*/  PL1_ENABLE ; 
 int /*<<< orphan*/  PL2_CLAMP ; 
 int /*<<< orphan*/  PL2_ENABLE ; 
 scalar_t__ RAPL_DOMAIN_PACKAGE ; 
 int find_nr_power_limit (struct rapl_domain*) ; 
 int /*<<< orphan*/  kfree (struct rapl_package*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  package_power_limit_irq_restore (struct rapl_package*) ; 
 int /*<<< orphan*/  powercap_unregister_zone (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rapl_write_data_raw (struct rapl_domain*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void rapl_remove_package(struct rapl_package *rp)
{
	struct rapl_domain *rd, *rd_package = NULL;

	package_power_limit_irq_restore(rp);

	for (rd = rp->domains; rd < rp->domains + rp->nr_domains; rd++) {
		rapl_write_data_raw(rd, PL1_ENABLE, 0);
		rapl_write_data_raw(rd, PL1_CLAMP, 0);
		if (find_nr_power_limit(rd) > 1) {
			rapl_write_data_raw(rd, PL2_ENABLE, 0);
			rapl_write_data_raw(rd, PL2_CLAMP, 0);
		}
		if (rd->id == RAPL_DOMAIN_PACKAGE) {
			rd_package = rd;
			continue;
		}
		pr_debug("remove package, undo power limit on %s: %s\n",
			 rp->name, rd->name);
		powercap_unregister_zone(rp->priv->control_type,
					 &rd->power_zone);
	}
	/* do parent zone last */
	powercap_unregister_zone(rp->priv->control_type,
				 &rd_package->power_zone);
	list_del(&rp->plist);
	kfree(rp);
}