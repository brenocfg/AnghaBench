#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct mfd_cell {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  reset; } ;
struct madera {int num_core_supplies; int type; unsigned int rev; int /*<<< orphan*/  dcvdd; TYPE_1__* core_supplies; struct device* dev; int /*<<< orphan*/  regmap; int /*<<< orphan*/  type_name; TYPE_3__ pdata; int /*<<< orphan*/  regmap_32bit; int /*<<< orphan*/  dapm_ptr_lock; int /*<<< orphan*/  notifier; } ;
struct device {int dummy; } ;
struct TYPE_5__ {struct mfd_cell supply; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct mfd_cell const*) ; 
 int /*<<< orphan*/  BLOCKING_INIT_NOTIFIER_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CONFIG_MFD_CS47L15 ; 
 int /*<<< orphan*/  CONFIG_MFD_CS47L35 ; 
 int /*<<< orphan*/  CONFIG_MFD_CS47L85 ; 
 int /*<<< orphan*/  CONFIG_MFD_CS47L90 ; 
 int /*<<< orphan*/  CONFIG_MFD_CS47L92 ; 
#define  CS42L92 141 
#define  CS47L15 140 
#define  CS47L15_SILICON_ID 139 
#define  CS47L35 138 
#define  CS47L35_SILICON_ID 137 
#define  CS47L85 136 
#define  CS47L85_SILICON_ID 135 
#define  CS47L90 134 
#define  CS47L90_SILICON_ID 133 
#define  CS47L91 132 
#define  CS47L92 131 
#define  CS47L92_SILICON_ID 130 
#define  CS47L93 129 
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  IS_ENABLED (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int MADERA_32KZ_MCLK2 ; 
 int MADERA_CLK_32K_ENA ; 
 int MADERA_CLK_32K_ENA_MASK ; 
 int MADERA_CLK_32K_SRC_MASK ; 
 int /*<<< orphan*/  MADERA_CLOCK_32K_1 ; 
 int /*<<< orphan*/  MADERA_HARDWARE_REVISION ; 
 unsigned int MADERA_HW_REVISION_MASK ; 
 int /*<<< orphan*/  MADERA_SOFTWARE_RESET ; 
 int /*<<< orphan*/  PLATFORM_DEVID_NONE ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
#define  WM1840 128 
 struct mfd_cell const* cs47l15_devs ; 
 int cs47l15_patch (struct madera*) ; 
 struct mfd_cell const* cs47l35_devs ; 
 int cs47l35_patch (struct madera*) ; 
 struct mfd_cell const* cs47l85_devs ; 
 int cs47l85_patch (struct madera*) ; 
 struct mfd_cell const* cs47l90_devs ; 
 int cs47l90_patch (struct madera*) ; 
 struct mfd_cell const* cs47l92_devs ; 
 int cs47l92_patch (struct madera*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int,...) ; 
 scalar_t__ dev_get_platdata (struct device*) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct madera*) ; 
 int devm_regulator_bulk_get (struct device*,int,TYPE_1__*) ; 
 struct mfd_cell const* madera_core_supplies ; 
 int /*<<< orphan*/  madera_disable_hard_reset (struct madera*) ; 
 int /*<<< orphan*/  madera_enable_hard_reset (struct madera*) ; 
 int madera_get_reset_gpio (struct madera*) ; 
 struct mfd_cell const* madera_ldo1_devs ; 
 int /*<<< orphan*/  madera_set_micbias_info (struct madera*) ; 
 int madera_soft_reset (struct madera*) ; 
 int madera_wait_for_boot (struct madera*) ; 
 int /*<<< orphan*/  memcpy (TYPE_3__*,scalar_t__,int) ; 
 int mfd_add_devices (struct device*,int /*<<< orphan*/ ,struct mfd_cell const*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mfd_remove_devices (struct device*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_disable (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_enable (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_set_active (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_set_autosuspend_delay (struct device*,int) ; 
 int /*<<< orphan*/  pm_runtime_use_autosuspend (struct device*) ; 
 int /*<<< orphan*/  regcache_cache_only (int /*<<< orphan*/ ,int) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  regulator_bulk_disable (int,TYPE_1__*) ; 
 int regulator_bulk_enable (int,TYPE_1__*) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 
 int regulator_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regulator_get (struct device*,char*) ; 
 int /*<<< orphan*/  regulator_put (int /*<<< orphan*/ ) ; 

int madera_dev_init(struct madera *madera)
{
	struct device *dev = madera->dev;
	unsigned int hwid;
	int (*patch_fn)(struct madera *) = NULL;
	const struct mfd_cell *mfd_devs;
	int n_devs = 0;
	int i, ret;

	dev_set_drvdata(madera->dev, madera);
	BLOCKING_INIT_NOTIFIER_HEAD(&madera->notifier);
	mutex_init(&madera->dapm_ptr_lock);

	madera_set_micbias_info(madera);

	/*
	 * We need writable hw config info that all children can share.
	 * Simplest to take one shared copy of pdata struct.
	 */
	if (dev_get_platdata(madera->dev)) {
		memcpy(&madera->pdata, dev_get_platdata(madera->dev),
		       sizeof(madera->pdata));
	}

	ret = madera_get_reset_gpio(madera);
	if (ret)
		return ret;

	regcache_cache_only(madera->regmap, true);
	regcache_cache_only(madera->regmap_32bit, true);

	for (i = 0; i < ARRAY_SIZE(madera_core_supplies); i++)
		madera->core_supplies[i].supply = madera_core_supplies[i];

	madera->num_core_supplies = ARRAY_SIZE(madera_core_supplies);

	/*
	 * On some codecs DCVDD could be supplied by the internal LDO1.
	 * For those we must add the LDO1 driver before requesting DCVDD
	 * No devm_ because we need to control shutdown order of children.
	 */
	switch (madera->type) {
	case CS47L15:
	case CS47L35:
	case CS47L90:
	case CS47L91:
	case CS42L92:
	case CS47L92:
	case CS47L93:
		break;
	case CS47L85:
	case WM1840:
		ret = mfd_add_devices(madera->dev, PLATFORM_DEVID_NONE,
				      madera_ldo1_devs,
				      ARRAY_SIZE(madera_ldo1_devs),
				      NULL, 0, NULL);
		if (ret) {
			dev_err(dev, "Failed to add LDO1 child: %d\n", ret);
			return ret;
		}
		break;
	default:
		/* No point continuing if the type is unknown */
		dev_err(madera->dev, "Unknown device type %d\n", madera->type);
		return -ENODEV;
	}

	ret = devm_regulator_bulk_get(dev, madera->num_core_supplies,
				      madera->core_supplies);
	if (ret) {
		dev_err(dev, "Failed to request core supplies: %d\n", ret);
		goto err_devs;
	}

	/*
	 * Don't use devres here. If the regulator is one of our children it
	 * will already have been removed before devres cleanup on this mfd
	 * driver tries to call put() on it. We need control of shutdown order.
	 */
	madera->dcvdd = regulator_get(madera->dev, "DCVDD");
	if (IS_ERR(madera->dcvdd)) {
		ret = PTR_ERR(madera->dcvdd);
		dev_err(dev, "Failed to request DCVDD: %d\n", ret);
		goto err_devs;
	}

	ret = regulator_bulk_enable(madera->num_core_supplies,
				    madera->core_supplies);
	if (ret) {
		dev_err(dev, "Failed to enable core supplies: %d\n", ret);
		goto err_dcvdd;
	}

	ret = regulator_enable(madera->dcvdd);
	if (ret) {
		dev_err(dev, "Failed to enable DCVDD: %d\n", ret);
		goto err_enable;
	}

	madera_disable_hard_reset(madera);

	regcache_cache_only(madera->regmap, false);
	regcache_cache_only(madera->regmap_32bit, false);

	/*
	 * Now we can power up and verify that this is a chip we know about
	 * before we start doing any writes to its registers.
	 */
	ret = regmap_read(madera->regmap, MADERA_SOFTWARE_RESET, &hwid);
	if (ret) {
		dev_err(dev, "Failed to read ID register: %d\n", ret);
		goto err_reset;
	}

	switch (hwid) {
	case CS47L15_SILICON_ID:
		if (IS_ENABLED(CONFIG_MFD_CS47L15)) {
			switch (madera->type) {
			case CS47L15:
				patch_fn = &cs47l15_patch;
				mfd_devs = cs47l15_devs;
				n_devs = ARRAY_SIZE(cs47l15_devs);
				break;
			default:
				break;
			}
		}
		break;
	case CS47L35_SILICON_ID:
		if (IS_ENABLED(CONFIG_MFD_CS47L35)) {
			switch (madera->type) {
			case CS47L35:
				patch_fn = cs47l35_patch;
				mfd_devs = cs47l35_devs;
				n_devs = ARRAY_SIZE(cs47l35_devs);
				break;
			default:
				break;
			}
		}
		break;
	case CS47L85_SILICON_ID:
		if (IS_ENABLED(CONFIG_MFD_CS47L85)) {
			switch (madera->type) {
			case CS47L85:
			case WM1840:
				patch_fn = cs47l85_patch;
				mfd_devs = cs47l85_devs;
				n_devs = ARRAY_SIZE(cs47l85_devs);
				break;
			default:
				break;
			}
		}
		break;
	case CS47L90_SILICON_ID:
		if (IS_ENABLED(CONFIG_MFD_CS47L90)) {
			switch (madera->type) {
			case CS47L90:
			case CS47L91:
				patch_fn = cs47l90_patch;
				mfd_devs = cs47l90_devs;
				n_devs = ARRAY_SIZE(cs47l90_devs);
				break;
			default:
				break;
			}
		}
		break;
	case CS47L92_SILICON_ID:
		if (IS_ENABLED(CONFIG_MFD_CS47L92)) {
			switch (madera->type) {
			case CS42L92:
			case CS47L92:
			case CS47L93:
				patch_fn = cs47l92_patch;
				mfd_devs = cs47l92_devs;
				n_devs = ARRAY_SIZE(cs47l92_devs);
				break;
			default:
				break;
			}
		}
		break;
	default:
		dev_err(madera->dev, "Unknown device ID: %x\n", hwid);
		ret = -EINVAL;
		goto err_reset;
	}

	if (!n_devs) {
		dev_err(madera->dev, "Device ID 0x%x not a %s\n", hwid,
			madera->type_name);
		ret = -ENODEV;
		goto err_reset;
	}

	/*
	 * It looks like a device we support. If we don't have a hard reset
	 * we can now attempt a soft reset.
	 */
	if (!madera->pdata.reset) {
		ret = madera_soft_reset(madera);
		if (ret)
			goto err_reset;
	}

	ret = madera_wait_for_boot(madera);
	if (ret) {
		dev_err(madera->dev, "Device failed initial boot: %d\n", ret);
		goto err_reset;
	}

	ret = regmap_read(madera->regmap, MADERA_HARDWARE_REVISION,
			  &madera->rev);
	if (ret) {
		dev_err(dev, "Failed to read revision register: %d\n", ret);
		goto err_reset;
	}
	madera->rev &= MADERA_HW_REVISION_MASK;

	dev_info(dev, "%s silicon revision %d\n", madera->type_name,
		 madera->rev);

	/* Apply hardware patch */
	if (patch_fn) {
		ret = patch_fn(madera);
		if (ret) {
			dev_err(madera->dev, "Failed to apply patch %d\n", ret);
			goto err_reset;
		}
	}

	/* Init 32k clock sourced from MCLK2 */
	ret = regmap_update_bits(madera->regmap,
			MADERA_CLOCK_32K_1,
			MADERA_CLK_32K_ENA_MASK | MADERA_CLK_32K_SRC_MASK,
			MADERA_CLK_32K_ENA | MADERA_32KZ_MCLK2);
	if (ret) {
		dev_err(madera->dev, "Failed to init 32k clock: %d\n", ret);
		goto err_reset;
	}

	pm_runtime_set_active(madera->dev);
	pm_runtime_enable(madera->dev);
	pm_runtime_set_autosuspend_delay(madera->dev, 100);
	pm_runtime_use_autosuspend(madera->dev);

	/* No devm_ because we need to control shutdown order of children */
	ret = mfd_add_devices(madera->dev, PLATFORM_DEVID_NONE,
			      mfd_devs, n_devs,
			      NULL, 0, NULL);
	if (ret) {
		dev_err(madera->dev, "Failed to add subdevices: %d\n", ret);
		goto err_pm_runtime;
	}

	return 0;

err_pm_runtime:
	pm_runtime_disable(madera->dev);
err_reset:
	madera_enable_hard_reset(madera);
	regulator_disable(madera->dcvdd);
err_enable:
	regulator_bulk_disable(madera->num_core_supplies,
			       madera->core_supplies);
err_dcvdd:
	regulator_put(madera->dcvdd);
err_devs:
	mfd_remove_devices(dev);

	return ret;
}