#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct device_node {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 size_t GPC_PGC_DOMAIN_ARM ; 
 size_t GPC_PGC_DOMAIN_PU ; 
 TYPE_2__* imx_gpc_domains ; 
 int /*<<< orphan*/  imx_pgc_put_clocks (TYPE_2__*) ; 
 int /*<<< orphan*/  of_genpd_del_provider (int /*<<< orphan*/ ) ; 
 struct device_node* of_get_child_by_name (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  of_property_read_bool (int /*<<< orphan*/ ,char*) ; 
 int pm_genpd_remove (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int imx_gpc_remove(struct platform_device *pdev)
{
	struct device_node *pgc_node;
	int ret;

	pgc_node = of_get_child_by_name(pdev->dev.of_node, "pgc");

	/* bail out if DT too old and doesn't provide the necessary info */
	if (!of_property_read_bool(pdev->dev.of_node, "#power-domain-cells") &&
	    !pgc_node)
		return 0;

	/*
	 * If the old DT binding is used the toplevel driver needs to
	 * de-register the power domains
	 */
	if (!pgc_node) {
		of_genpd_del_provider(pdev->dev.of_node);

		ret = pm_genpd_remove(&imx_gpc_domains[GPC_PGC_DOMAIN_PU].base);
		if (ret)
			return ret;
		imx_pgc_put_clocks(&imx_gpc_domains[GPC_PGC_DOMAIN_PU]);

		ret = pm_genpd_remove(&imx_gpc_domains[GPC_PGC_DOMAIN_ARM].base);
		if (ret)
			return ret;
	}

	return 0;
}