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
struct gdsc_desc {size_t num; struct gdsc** scs; struct device* dev; } ;
struct gdsc {int /*<<< orphan*/  pd; scalar_t__ parent; } ;
struct device {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  of_genpd_del_provider (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_genpd_remove_subdomain (scalar_t__,int /*<<< orphan*/ *) ; 

void gdsc_unregister(struct gdsc_desc *desc)
{
	int i;
	struct device *dev = desc->dev;
	struct gdsc **scs = desc->scs;
	size_t num = desc->num;

	/* Remove subdomains */
	for (i = 0; i < num; i++) {
		if (!scs[i])
			continue;
		if (scs[i]->parent)
			pm_genpd_remove_subdomain(scs[i]->parent, &scs[i]->pd);
	}
	of_genpd_del_provider(dev->of_node);
}