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
struct genpd_onecell_data {int num_domains; int /*<<< orphan*/ * domains; } ;
struct qmp {struct device* dev; struct genpd_onecell_data pd_data; } ;
struct device {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  of_genpd_del_provider (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_genpd_remove (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qmp_pd_remove(struct qmp *qmp)
{
	struct genpd_onecell_data *data = &qmp->pd_data;
	struct device *dev = qmp->dev;
	int i;

	of_genpd_del_provider(dev->of_node);

	for (i = 0; i < data->num_domains; i++)
		pm_genpd_remove(data->domains[i]);
}