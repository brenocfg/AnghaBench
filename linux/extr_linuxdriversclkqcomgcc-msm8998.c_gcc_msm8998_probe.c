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
 int /*<<< orphan*/  BIT (int) ; 
 scalar_t__ IS_ERR (struct regmap*) ; 
 int PTR_ERR (struct regmap*) ; 
 int /*<<< orphan*/  gcc_msm8998_desc ; 
 struct regmap* qcom_cc_map (struct platform_device*,int /*<<< orphan*/ *) ; 
 int qcom_cc_really_probe (struct platform_device*,int /*<<< orphan*/ *,struct regmap*) ; 
 int regmap_update_bits (struct regmap*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gcc_msm8998_probe(struct platform_device *pdev)
{
	struct regmap *regmap;
	int ret;

	regmap = qcom_cc_map(pdev, &gcc_msm8998_desc);
	if (IS_ERR(regmap))
		return PTR_ERR(regmap);

	/*
	 * Set the HMSS_AHB_CLK_SLEEP_ENA bit to allow the hmss_ahb_clk to be
	 * turned off by hardware during certain apps low power modes.
	 */
	ret = regmap_update_bits(regmap, 0x52008, BIT(21), BIT(21));
	if (ret)
		return ret;

	return qcom_cc_really_probe(pdev, &gcc_msm8998_desc, regmap);
}