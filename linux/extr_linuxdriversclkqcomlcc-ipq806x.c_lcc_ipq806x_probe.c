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
typedef  int /*<<< orphan*/  u32 ;
struct regmap {int dummy; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct regmap*) ; 
 int PTR_ERR (struct regmap*) ; 
 int /*<<< orphan*/  clk_pll_configure_sr (int /*<<< orphan*/ *,struct regmap*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lcc_ipq806x_desc ; 
 int /*<<< orphan*/  pll4 ; 
 int /*<<< orphan*/  pll4_config ; 
 struct regmap* qcom_cc_map (struct platform_device*,int /*<<< orphan*/ *) ; 
 int qcom_cc_really_probe (struct platform_device*,int /*<<< orphan*/ *,struct regmap*) ; 
 int /*<<< orphan*/  regmap_read (struct regmap*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regmap_write (struct regmap*,int,int) ; 

__attribute__((used)) static int lcc_ipq806x_probe(struct platform_device *pdev)
{
	u32 val;
	struct regmap *regmap;

	regmap = qcom_cc_map(pdev, &lcc_ipq806x_desc);
	if (IS_ERR(regmap))
		return PTR_ERR(regmap);

	/* Configure the rate of PLL4 if the bootloader hasn't already */
	regmap_read(regmap, 0x0, &val);
	if (!val)
		clk_pll_configure_sr(&pll4, regmap, &pll4_config, true);
	/* Enable PLL4 source on the LPASS Primary PLL Mux */
	regmap_write(regmap, 0xc4, 0x1);

	return qcom_cc_really_probe(pdev, &lcc_ipq806x_desc, regmap);
}