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
typedef  int u32 ;
struct TYPE_3__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_1__ dev; } ;
struct axp20x_dev {int variant; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
#define  AXP202_ID 135 
#define  AXP209_ID 134 
 unsigned int AXP20X_DCDC_FREQ ; 
 int /*<<< orphan*/  AXP20X_FREQ_DCDC_MASK ; 
#define  AXP221_ID 133 
#define  AXP223_ID 132 
 unsigned int AXP803_DCDC_FREQ_CTRL ; 
#define  AXP803_ID 131 
 unsigned int AXP806_DCDC_FREQ_CTRL ; 
#define  AXP806_ID 130 
#define  AXP809_ID 129 
#define  AXP813_ID 128 
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 struct axp20x_dev* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (TYPE_1__*,char*,int) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int axp20x_set_dcdc_freq(struct platform_device *pdev, u32 dcdcfreq)
{
	struct axp20x_dev *axp20x = dev_get_drvdata(pdev->dev.parent);
	unsigned int reg = AXP20X_DCDC_FREQ;
	u32 min, max, def, step;

	switch (axp20x->variant) {
	case AXP202_ID:
	case AXP209_ID:
		min = 750;
		max = 1875;
		def = 1500;
		step = 75;
		break;
	case AXP803_ID:
	case AXP813_ID:
		/*
		 * AXP803/AXP813 DCDC work frequency setting has the same
		 * range and step as AXP22X, but at a different register.
		 * (See include/linux/mfd/axp20x.h)
		 */
		reg = AXP803_DCDC_FREQ_CTRL;
		/* Fall through - to the check below.*/
	case AXP806_ID:
		/*
		 * AXP806 also have DCDC work frequency setting register at a
		 * different position.
		 */
		if (axp20x->variant == AXP806_ID)
			reg = AXP806_DCDC_FREQ_CTRL;
		/* Fall through */
	case AXP221_ID:
	case AXP223_ID:
	case AXP809_ID:
		min = 1800;
		max = 4050;
		def = 3000;
		step = 150;
		break;
	default:
		dev_err(&pdev->dev,
			"Setting DCDC frequency for unsupported AXP variant\n");
		return -EINVAL;
	}

	if (dcdcfreq == 0)
		dcdcfreq = def;

	if (dcdcfreq < min) {
		dcdcfreq = min;
		dev_warn(&pdev->dev, "DCDC frequency too low. Set to %ukHz\n",
			 min);
	}

	if (dcdcfreq > max) {
		dcdcfreq = max;
		dev_warn(&pdev->dev, "DCDC frequency too high. Set to %ukHz\n",
			 max);
	}

	dcdcfreq = (dcdcfreq - min) / step;

	return regmap_update_bits(axp20x->regmap, reg,
				  AXP20X_FREQ_DCDC_MASK, dcdcfreq);
}