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
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_pll_configure_sr_hpm_lp (int /*<<< orphan*/ *,struct regmap*,int /*<<< orphan*/ *,int) ; 
 struct regmap* dev_get_regmap (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mmcc_apq8084_desc ; 
 int /*<<< orphan*/  mmpll1 ; 
 int /*<<< orphan*/  mmpll1_config ; 
 int /*<<< orphan*/  mmpll3 ; 
 int /*<<< orphan*/  mmpll3_config ; 
 int qcom_cc_probe (struct platform_device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mmcc_apq8084_probe(struct platform_device *pdev)
{
	int ret;
	struct regmap *regmap;

	ret = qcom_cc_probe(pdev, &mmcc_apq8084_desc);
	if (ret)
		return ret;

	regmap = dev_get_regmap(&pdev->dev, NULL);
	clk_pll_configure_sr_hpm_lp(&mmpll1, regmap, &mmpll1_config, true);
	clk_pll_configure_sr_hpm_lp(&mmpll3, regmap, &mmpll3_config, false);

	return 0;
}