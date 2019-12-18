#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int reset_names_count; int clk_names_count; int (* get_power ) (struct meson_ee_pwrc_domain*) ;int /*<<< orphan*/  name; } ;
struct TYPE_4__ {int /*<<< orphan*/  power_off; int /*<<< orphan*/  power_on; int /*<<< orphan*/  name; } ;
struct meson_ee_pwrc_domain {int num_rstc; int num_clks; TYPE_1__ desc; TYPE_2__ base; int /*<<< orphan*/  clks; int /*<<< orphan*/  rstc; struct meson_ee_pwrc* pwrc; } ;
struct meson_ee_pwrc {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int clk_bulk_prepare_enable (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ) ; 
 int devm_clk_bulk_get_all (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_reset_control_array_get (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  meson_ee_pwrc_off ; 
 int /*<<< orphan*/  meson_ee_pwrc_on ; 
 int /*<<< orphan*/  pm_domain_always_on_gov ; 
 int /*<<< orphan*/  pm_genpd_init (TYPE_2__*,int /*<<< orphan*/ *,int) ; 
 int reset_control_get_count (int /*<<< orphan*/ *) ; 
 int stub1 (struct meson_ee_pwrc_domain*) ; 
 int stub2 (struct meson_ee_pwrc_domain*) ; 

__attribute__((used)) static int meson_ee_pwrc_init_domain(struct platform_device *pdev,
				     struct meson_ee_pwrc *pwrc,
				     struct meson_ee_pwrc_domain *dom)
{
	dom->pwrc = pwrc;
	dom->num_rstc = dom->desc.reset_names_count;
	dom->num_clks = dom->desc.clk_names_count;

	if (dom->num_rstc) {
		int count = reset_control_get_count(&pdev->dev);

		if (count != dom->num_rstc)
			dev_warn(&pdev->dev, "Invalid resets count %d for domain %s\n",
				 count, dom->desc.name);

		dom->rstc = devm_reset_control_array_get(&pdev->dev, false,
							 false);
		if (IS_ERR(dom->rstc))
			return PTR_ERR(dom->rstc);
	}

	if (dom->num_clks) {
		int ret = devm_clk_bulk_get_all(&pdev->dev, &dom->clks);
		if (ret < 0)
			return ret;

		if (dom->num_clks != ret) {
			dev_warn(&pdev->dev, "Invalid clocks count %d for domain %s\n",
				 ret, dom->desc.name);
			dom->num_clks = ret;
		}
	}

	dom->base.name = dom->desc.name;
	dom->base.power_on = meson_ee_pwrc_on;
	dom->base.power_off = meson_ee_pwrc_off;

	/*
         * TOFIX: This is a special case for the VPU power domain, which can
	 * be enabled previously by the bootloader. In this case the VPU
         * pipeline may be functional but no driver maybe never attach
         * to this power domain, and if the domain is disabled it could
         * cause system errors. This is why the pm_domain_always_on_gov
         * is used here.
         * For the same reason, the clocks should be enabled in case
         * we need to power the domain off, otherwise the internal clocks
         * prepare/enable counters won't be in sync.
         */
	if (dom->num_clks && dom->desc.get_power && !dom->desc.get_power(dom)) {
		int ret = clk_bulk_prepare_enable(dom->num_clks, dom->clks);
		if (ret)
			return ret;

		pm_genpd_init(&dom->base, &pm_domain_always_on_gov, false);
	} else
		pm_genpd_init(&dom->base, NULL,
			      (dom->desc.get_power ?
			       dom->desc.get_power(dom) : true));

	return 0;
}