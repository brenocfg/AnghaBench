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
struct regmap {int dummy; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct regmap*) ; 
 int PTR_ERR (struct regmap*) ; 
 int /*<<< orphan*/  clk_pll_configure_sr_hpm_lp (int /*<<< orphan*/ *,struct regmap*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mmcc_msm8974_desc ; 
 int /*<<< orphan*/  mmpll1 ; 
 int /*<<< orphan*/  mmpll1_config ; 
 int /*<<< orphan*/  mmpll3 ; 
 int /*<<< orphan*/  mmpll3_config ; 
 struct regmap* qcom_cc_map (struct platform_device*,int /*<<< orphan*/ *) ; 
 int qcom_cc_really_probe (struct platform_device*,int /*<<< orphan*/ *,struct regmap*) ; 

__attribute__((used)) static int mmcc_msm8974_probe(struct platform_device *pdev)
{
	struct regmap *regmap;

	regmap = qcom_cc_map(pdev, &mmcc_msm8974_desc);
	if (IS_ERR(regmap))
		return PTR_ERR(regmap);

	clk_pll_configure_sr_hpm_lp(&mmpll1, regmap, &mmpll1_config, true);
	clk_pll_configure_sr_hpm_lp(&mmpll3, regmap, &mmpll3_config, false);

	return qcom_cc_really_probe(pdev, &mmcc_msm8974_desc, regmap);
}