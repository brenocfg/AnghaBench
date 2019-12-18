#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct reset_control {int dummy; } ;
typedef  struct reset_control regmap ;
struct TYPE_6__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct meson_gx_pwrc_vpu {int /*<<< orphan*/  genpd; struct reset_control* vapb_clk; struct reset_control* vpu_clk; struct reset_control* rstc; struct reset_control* regmap_hhi; struct reset_control* regmap_ao; } ;
typedef  struct reset_control clk ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct reset_control*) ; 
 int PTR_ERR (struct reset_control*) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 struct reset_control* devm_clk_get (TYPE_1__*,char*) ; 
 struct meson_gx_pwrc_vpu* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 struct reset_control* devm_reset_control_array_get (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  memcpy (struct meson_gx_pwrc_vpu*,struct meson_gx_pwrc_vpu const*,int) ; 
 int meson_gx_pwrc_vpu_get_power (struct meson_gx_pwrc_vpu*) ; 
 int meson_gx_pwrc_vpu_setup_clk (struct meson_gx_pwrc_vpu*) ; 
 struct meson_gx_pwrc_vpu* of_device_get_match_data (TYPE_1__*) ; 
 int of_genpd_add_provider_simple (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_get_parent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct meson_gx_pwrc_vpu*) ; 
 int /*<<< orphan*/  pm_domain_always_on_gov ; 
 int /*<<< orphan*/  pm_genpd_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 struct reset_control* syscon_node_to_regmap (int /*<<< orphan*/ ) ; 
 struct reset_control* syscon_regmap_lookup_by_phandle (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int meson_gx_pwrc_vpu_probe(struct platform_device *pdev)
{
	const struct meson_gx_pwrc_vpu *vpu_pd_match;
	struct regmap *regmap_ao, *regmap_hhi;
	struct meson_gx_pwrc_vpu *vpu_pd;
	struct reset_control *rstc;
	struct clk *vpu_clk;
	struct clk *vapb_clk;
	bool powered_off;
	int ret;

	vpu_pd_match = of_device_get_match_data(&pdev->dev);
	if (!vpu_pd_match) {
		dev_err(&pdev->dev, "failed to get match data\n");
		return -ENODEV;
	}

	vpu_pd = devm_kzalloc(&pdev->dev, sizeof(*vpu_pd), GFP_KERNEL);
	if (!vpu_pd)
		return -ENOMEM;

	memcpy(vpu_pd, vpu_pd_match, sizeof(*vpu_pd));

	regmap_ao = syscon_node_to_regmap(of_get_parent(pdev->dev.of_node));
	if (IS_ERR(regmap_ao)) {
		dev_err(&pdev->dev, "failed to get regmap\n");
		return PTR_ERR(regmap_ao);
	}

	regmap_hhi = syscon_regmap_lookup_by_phandle(pdev->dev.of_node,
						     "amlogic,hhi-sysctrl");
	if (IS_ERR(regmap_hhi)) {
		dev_err(&pdev->dev, "failed to get HHI regmap\n");
		return PTR_ERR(regmap_hhi);
	}

	rstc = devm_reset_control_array_get(&pdev->dev, false, false);
	if (IS_ERR(rstc)) {
		if (PTR_ERR(rstc) != -EPROBE_DEFER)
			dev_err(&pdev->dev, "failed to get reset lines\n");
		return PTR_ERR(rstc);
	}

	vpu_clk = devm_clk_get(&pdev->dev, "vpu");
	if (IS_ERR(vpu_clk)) {
		dev_err(&pdev->dev, "vpu clock request failed\n");
		return PTR_ERR(vpu_clk);
	}

	vapb_clk = devm_clk_get(&pdev->dev, "vapb");
	if (IS_ERR(vapb_clk)) {
		dev_err(&pdev->dev, "vapb clock request failed\n");
		return PTR_ERR(vapb_clk);
	}

	vpu_pd->regmap_ao = regmap_ao;
	vpu_pd->regmap_hhi = regmap_hhi;
	vpu_pd->rstc = rstc;
	vpu_pd->vpu_clk = vpu_clk;
	vpu_pd->vapb_clk = vapb_clk;

	platform_set_drvdata(pdev, vpu_pd);

	powered_off = meson_gx_pwrc_vpu_get_power(vpu_pd);

	/* If already powered, sync the clock states */
	if (!powered_off) {
		ret = meson_gx_pwrc_vpu_setup_clk(vpu_pd);
		if (ret)
			return ret;
	}

	pm_genpd_init(&vpu_pd->genpd, &pm_domain_always_on_gov,
		      powered_off);

	return of_genpd_add_provider_simple(pdev->dev.of_node,
					    &vpu_pd->genpd);
}