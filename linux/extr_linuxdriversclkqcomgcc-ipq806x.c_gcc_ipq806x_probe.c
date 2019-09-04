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
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;

/* Variables and functions */
 int ENODEV ; 
 struct regmap* dev_get_regmap (struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gcc_ipq806x_desc ; 
 int qcom_cc_probe (struct platform_device*,int /*<<< orphan*/ *) ; 
 int qcom_cc_register_board_clk (struct device*,char*,char*,int) ; 
 int /*<<< orphan*/  regmap_update_bits (struct regmap*,int,int,int) ; 
 int /*<<< orphan*/  regmap_write (struct regmap*,int,int) ; 

__attribute__((used)) static int gcc_ipq806x_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct regmap *regmap;
	int ret;

	ret = qcom_cc_register_board_clk(dev, "cxo_board", "cxo", 25000000);
	if (ret)
		return ret;

	ret = qcom_cc_register_board_clk(dev, "pxo_board", "pxo", 25000000);
	if (ret)
		return ret;

	ret = qcom_cc_probe(pdev, &gcc_ipq806x_desc);
	if (ret)
		return ret;

	regmap = dev_get_regmap(dev, NULL);
	if (!regmap)
		return -ENODEV;

	/* Setup PLL18 static bits */
	regmap_update_bits(regmap, 0x31a4, 0xffffffc0, 0x40000400);
	regmap_write(regmap, 0x31b0, 0x3080);

	/* Set GMAC footswitch sleep/wakeup values */
	regmap_write(regmap, 0x3cb8, 8);
	regmap_write(regmap, 0x3cd8, 8);
	regmap_write(regmap, 0x3cf8, 8);
	regmap_write(regmap, 0x3d18, 8);

	return 0;
}