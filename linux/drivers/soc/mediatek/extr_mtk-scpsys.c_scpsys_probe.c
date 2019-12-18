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
struct scp_subdomain {size_t origin; size_t subdomain; } ;
struct scp_soc_data {int num_subdomains; struct scp_subdomain* subdomains; int /*<<< orphan*/  num_domains; int /*<<< orphan*/  bus_prot_reg_update; int /*<<< orphan*/  regs; int /*<<< orphan*/  domains; } ;
struct genpd_onecell_data {int /*<<< orphan*/ * domains; } ;
struct scp {struct genpd_onecell_data pd_data; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_PM ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct scp*) ; 
 int PTR_ERR (struct scp*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 struct scp* init_scp (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_register_power_domains (struct platform_device*,struct scp*,int /*<<< orphan*/ ) ; 
 struct scp_soc_data* of_device_get_match_data (int /*<<< orphan*/ *) ; 
 int pm_genpd_add_subdomain (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int scpsys_probe(struct platform_device *pdev)
{
	const struct scp_subdomain *sd;
	const struct scp_soc_data *soc;
	struct scp *scp;
	struct genpd_onecell_data *pd_data;
	int i, ret;

	soc = of_device_get_match_data(&pdev->dev);

	scp = init_scp(pdev, soc->domains, soc->num_domains, &soc->regs,
			soc->bus_prot_reg_update);
	if (IS_ERR(scp))
		return PTR_ERR(scp);

	mtk_register_power_domains(pdev, scp, soc->num_domains);

	pd_data = &scp->pd_data;

	for (i = 0, sd = soc->subdomains; i < soc->num_subdomains; i++, sd++) {
		ret = pm_genpd_add_subdomain(pd_data->domains[sd->origin],
					     pd_data->domains[sd->subdomain]);
		if (ret && IS_ENABLED(CONFIG_PM))
			dev_err(&pdev->dev, "Failed to add subdomain: %d\n",
				ret);
	}

	return 0;
}