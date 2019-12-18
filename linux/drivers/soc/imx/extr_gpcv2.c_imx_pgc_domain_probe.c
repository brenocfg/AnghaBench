#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  of_node; struct imx_pgc_domain* platform_data; } ;
struct platform_device {TYPE_1__ dev; } ;
struct imx_pgc_domain {int /*<<< orphan*/  genpd; TYPE_1__* dev; scalar_t__ voltage; int /*<<< orphan*/  regulator; } ;

/* Variables and functions */
 int ENODEV ; 
 int EPROBE_DEFER ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  devm_regulator_get_optional (TYPE_1__*,char*) ; 
 int imx_pgc_get_clocks (struct imx_pgc_domain*) ; 
 int /*<<< orphan*/  imx_pgc_put_clocks (struct imx_pgc_domain*) ; 
 int of_genpd_add_provider_simple (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int pm_genpd_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pm_genpd_remove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regulator_set_voltage (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int imx_pgc_domain_probe(struct platform_device *pdev)
{
	struct imx_pgc_domain *domain = pdev->dev.platform_data;
	int ret;

	domain->dev = &pdev->dev;

	domain->regulator = devm_regulator_get_optional(domain->dev, "power");
	if (IS_ERR(domain->regulator)) {
		if (PTR_ERR(domain->regulator) != -ENODEV) {
			if (PTR_ERR(domain->regulator) != -EPROBE_DEFER)
				dev_err(domain->dev, "Failed to get domain's regulator\n");
			return PTR_ERR(domain->regulator);
		}
	} else if (domain->voltage) {
		regulator_set_voltage(domain->regulator,
				      domain->voltage, domain->voltage);
	}

	ret = imx_pgc_get_clocks(domain);
	if (ret) {
		if (ret != -EPROBE_DEFER)
			dev_err(domain->dev, "Failed to get domain's clocks\n");
		return ret;
	}

	ret = pm_genpd_init(&domain->genpd, NULL, true);
	if (ret) {
		dev_err(domain->dev, "Failed to init power domain\n");
		imx_pgc_put_clocks(domain);
		return ret;
	}

	ret = of_genpd_add_provider_simple(domain->dev->of_node,
					   &domain->genpd);
	if (ret) {
		dev_err(domain->dev, "Failed to add genpd provider\n");
		pm_genpd_remove(&domain->genpd);
		imx_pgc_put_clocks(domain);
	}

	return ret;
}