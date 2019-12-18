#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct power_supply_config {struct axp288_fg_info* drv_data; } ;
struct TYPE_5__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_1__ dev; } ;
struct axp288_fg_info {int max_volt; int /*<<< orphan*/ * iio_channel; int /*<<< orphan*/  bat; int /*<<< orphan*/  lock; int /*<<< orphan*/  status; int /*<<< orphan*/  regmap_irqc; int /*<<< orphan*/  regmap; struct platform_device* pdev; } ;
struct axp20x_dev {int /*<<< orphan*/  regmap_irqc; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  AXP20X_CC_CTRL ; 
 int /*<<< orphan*/  AXP20X_CHRG_CTRL1 ; 
 int /*<<< orphan*/  AXP288_FG_DES_CAP1_REG ; 
#define  BAT_CHRG_CURR 137 
#define  BAT_D_CURR 136 
#define  BAT_TEMP 135 
#define  BAT_VOLT 134 
#define  CHRG_CCCV_CV_4100MV 133 
#define  CHRG_CCCV_CV_4150MV 132 
#define  CHRG_CCCV_CV_4200MV 131 
#define  CHRG_CCCV_CV_4350MV 130 
 int CHRG_CCCV_CV_BIT_POS ; 
 int CHRG_CCCV_CV_MASK ; 
 int ENODEV ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int FG_DES_CAP1_VALID ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IIO_CHANNEL_NUM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_ERR_OR_NULL (int /*<<< orphan*/ ) ; 
#define  PMIC_TEMP 129 
 int /*<<< orphan*/  POWER_SUPPLY_STATUS_UNKNOWN ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
#define  SYSTEM_TEMP 128 
 int /*<<< orphan*/  axp288_fuel_gauge_blacklist ; 
 int /*<<< orphan*/  dev_dbg (TYPE_1__*,char*,char const* const,int) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,...) ; 
 struct axp20x_dev* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 struct axp288_fg_info* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ dmi_check_system (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fuel_gauge_create_debugfs (struct axp288_fg_info*) ; 
 int /*<<< orphan*/  fuel_gauge_desc ; 
 int /*<<< orphan*/  fuel_gauge_init_irq (struct axp288_fg_info*) ; 
 int fuel_gauge_reg_readb (struct axp288_fg_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iio_channel_get (int /*<<< orphan*/ *,char const* const) ; 
 int /*<<< orphan*/  iio_channel_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct axp288_fg_info*) ; 
 int /*<<< orphan*/  power_supply_register (TYPE_1__*,int /*<<< orphan*/ *,struct power_supply_config*) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static int axp288_fuel_gauge_probe(struct platform_device *pdev)
{
	int i, ret = 0;
	struct axp288_fg_info *info;
	struct axp20x_dev *axp20x = dev_get_drvdata(pdev->dev.parent);
	struct power_supply_config psy_cfg = {};
	static const char * const iio_chan_name[] = {
		[BAT_TEMP] = "axp288-batt-temp",
		[PMIC_TEMP] = "axp288-pmic-temp",
		[SYSTEM_TEMP] = "axp288-system-temp",
		[BAT_CHRG_CURR] = "axp288-chrg-curr",
		[BAT_D_CURR] = "axp288-chrg-d-curr",
		[BAT_VOLT] = "axp288-batt-volt",
	};
	unsigned int val;

	if (dmi_check_system(axp288_fuel_gauge_blacklist))
		return -ENODEV;

	/*
	 * On some devices the fuelgauge and charger parts of the axp288 are
	 * not used, check that the fuelgauge is enabled (CC_CTRL != 0).
	 */
	ret = regmap_read(axp20x->regmap, AXP20X_CC_CTRL, &val);
	if (ret < 0)
		return ret;
	if (val == 0)
		return -ENODEV;

	info = devm_kzalloc(&pdev->dev, sizeof(*info), GFP_KERNEL);
	if (!info)
		return -ENOMEM;

	info->pdev = pdev;
	info->regmap = axp20x->regmap;
	info->regmap_irqc = axp20x->regmap_irqc;
	info->status = POWER_SUPPLY_STATUS_UNKNOWN;

	platform_set_drvdata(pdev, info);

	mutex_init(&info->lock);

	for (i = 0; i < IIO_CHANNEL_NUM; i++) {
		/*
		 * Note cannot use devm_iio_channel_get because x86 systems
		 * lack the device<->channel maps which iio_channel_get will
		 * try to use when passed a non NULL device pointer.
		 */
		info->iio_channel[i] =
			iio_channel_get(NULL, iio_chan_name[i]);
		if (IS_ERR(info->iio_channel[i])) {
			ret = PTR_ERR(info->iio_channel[i]);
			dev_dbg(&pdev->dev, "error getting iiochan %s: %d\n",
				iio_chan_name[i], ret);
			/* Wait for axp288_adc to load */
			if (ret == -ENODEV)
				ret = -EPROBE_DEFER;

			goto out_free_iio_chan;
		}
	}

	ret = fuel_gauge_reg_readb(info, AXP288_FG_DES_CAP1_REG);
	if (ret < 0)
		goto out_free_iio_chan;

	if (!(ret & FG_DES_CAP1_VALID)) {
		dev_err(&pdev->dev, "axp288 not configured by firmware\n");
		ret = -ENODEV;
		goto out_free_iio_chan;
	}

	ret = fuel_gauge_reg_readb(info, AXP20X_CHRG_CTRL1);
	if (ret < 0)
		goto out_free_iio_chan;
	switch ((ret & CHRG_CCCV_CV_MASK) >> CHRG_CCCV_CV_BIT_POS) {
	case CHRG_CCCV_CV_4100MV:
		info->max_volt = 4100;
		break;
	case CHRG_CCCV_CV_4150MV:
		info->max_volt = 4150;
		break;
	case CHRG_CCCV_CV_4200MV:
		info->max_volt = 4200;
		break;
	case CHRG_CCCV_CV_4350MV:
		info->max_volt = 4350;
		break;
	}

	psy_cfg.drv_data = info;
	info->bat = power_supply_register(&pdev->dev, &fuel_gauge_desc, &psy_cfg);
	if (IS_ERR(info->bat)) {
		ret = PTR_ERR(info->bat);
		dev_err(&pdev->dev, "failed to register battery: %d\n", ret);
		goto out_free_iio_chan;
	}

	fuel_gauge_create_debugfs(info);
	fuel_gauge_init_irq(info);

	return 0;

out_free_iio_chan:
	for (i = 0; i < IIO_CHANNEL_NUM; i++)
		if (!IS_ERR_OR_NULL(info->iio_channel[i]))
			iio_channel_release(info->iio_channel[i]);

	return ret;
}