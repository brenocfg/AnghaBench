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
struct wm8994_pdata {void** gpio_defaults; scalar_t__ csnaddr_pd; scalar_t__ spkmode_pu; int /*<<< orphan*/  ldo_ena_always_driven; int /*<<< orphan*/  gpio_base; int /*<<< orphan*/  irq_base; } ;
struct wm8994 {int type; int num_supplies; int revision; int cust_id; int /*<<< orphan*/  dev; TYPE_1__* supplies; int /*<<< orphan*/  ldo_ena_always_driven; int /*<<< orphan*/  gpio_base; int /*<<< orphan*/  irq_base; int /*<<< orphan*/  regmap; struct wm8994_pdata pdata; } ;
struct regulator_bulk_data {int dummy; } ;
struct regmap_config {int dummy; } ;
typedef  void* reg_sequence ;
struct TYPE_6__ {void* supply; } ;

/* Variables and functions */
 int ARRAY_SIZE (void**) ; 
 int /*<<< orphan*/  BUG () ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
#define  WM1811 130 
#define  WM8958 129 
#define  WM8994 128 
 int /*<<< orphan*/  WM8994_CHIP_REVISION ; 
 int WM8994_CHIP_REV_MASK ; 
 int WM8994_CSNADDR_PD ; 
 int WM8994_CUST_ID_MASK ; 
 int WM8994_CUST_ID_SHIFT ; 
 scalar_t__ WM8994_GPIO_1 ; 
 int WM8994_LDO1ENA_PD ; 
 int WM8994_LDO1_DISCH ; 
 int WM8994_LDO2ENA_PD ; 
 scalar_t__ WM8994_LDO_1 ; 
 int WM8994_NUM_LDO_REGS ; 
 scalar_t__ WM8994_PULL_CONTROL_2 ; 
 int /*<<< orphan*/  WM8994_SOFTWARE_RESET ; 
 int WM8994_SPKMODE_PU ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 struct wm8994_pdata* dev_get_platdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,char const*,char,int) ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ ,struct wm8994*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,char) ; 
 TYPE_1__* devm_kcalloc (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int mfd_add_devices (int /*<<< orphan*/ ,int,void**,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mfd_remove_devices (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_idle (int /*<<< orphan*/ ) ; 
 int regmap_register_patch (int /*<<< orphan*/ ,void* const*,int) ; 
 int regmap_reinit_cache (int /*<<< orphan*/ ,struct regmap_config*) ; 
 int /*<<< orphan*/  regulator_bulk_disable (int,TYPE_1__*) ; 
 int regulator_bulk_enable (int,TYPE_1__*) ; 
 int /*<<< orphan*/  regulator_bulk_free (int,TYPE_1__*) ; 
 int regulator_bulk_get (int /*<<< orphan*/ ,int,TYPE_1__*) ; 
 void** wm1811_main_supplies ; 
 struct regmap_config wm1811_regmap_config ; 
 void** wm1811_reva_patch ; 
 void** wm8958_main_supplies ; 
 struct regmap_config wm8958_regmap_config ; 
 void** wm8958_reva_patch ; 
 void** wm8994_devs ; 
 int /*<<< orphan*/  wm8994_irq_exit (struct wm8994*) ; 
 int /*<<< orphan*/  wm8994_irq_init (struct wm8994*) ; 
 scalar_t__ wm8994_ldo_in_use (struct wm8994_pdata*,int) ; 
 void** wm8994_main_supplies ; 
 int wm8994_reg_read (struct wm8994*,int /*<<< orphan*/ ) ; 
 int wm8994_reg_write (struct wm8994*,int /*<<< orphan*/ ,int) ; 
 struct regmap_config wm8994_regmap_config ; 
 void** wm8994_regulator_devs ; 
 void** wm8994_revc_patch ; 
 int /*<<< orphan*/  wm8994_set_bits (struct wm8994*,scalar_t__,int,int) ; 
 int wm8994_set_pdata_from_of (struct wm8994*) ; 

__attribute__((used)) static int wm8994_device_init(struct wm8994 *wm8994, int irq)
{
	struct wm8994_pdata *pdata;
	struct regmap_config *regmap_config;
	const struct reg_sequence *regmap_patch = NULL;
	const char *devname;
	int ret, i, patch_regs = 0;
	int pulls = 0;

	if (dev_get_platdata(wm8994->dev)) {
		pdata = dev_get_platdata(wm8994->dev);
		wm8994->pdata = *pdata;
	}
	pdata = &wm8994->pdata;

	ret = wm8994_set_pdata_from_of(wm8994);
	if (ret != 0)
		return ret;

	dev_set_drvdata(wm8994->dev, wm8994);

	/* Add the on-chip regulators first for bootstrapping */
	ret = mfd_add_devices(wm8994->dev, 0,
			      wm8994_regulator_devs,
			      ARRAY_SIZE(wm8994_regulator_devs),
			      NULL, 0, NULL);
	if (ret != 0) {
		dev_err(wm8994->dev, "Failed to add children: %d\n", ret);
		goto err;
	}

	switch (wm8994->type) {
	case WM1811:
		wm8994->num_supplies = ARRAY_SIZE(wm1811_main_supplies);
		break;
	case WM8994:
		wm8994->num_supplies = ARRAY_SIZE(wm8994_main_supplies);
		break;
	case WM8958:
		wm8994->num_supplies = ARRAY_SIZE(wm8958_main_supplies);
		break;
	default:
		BUG();
		goto err;
	}

	wm8994->supplies = devm_kcalloc(wm8994->dev,
					wm8994->num_supplies,
					sizeof(struct regulator_bulk_data),
					GFP_KERNEL);
	if (!wm8994->supplies) {
		ret = -ENOMEM;
		goto err;
	}

	switch (wm8994->type) {
	case WM1811:
		for (i = 0; i < ARRAY_SIZE(wm1811_main_supplies); i++)
			wm8994->supplies[i].supply = wm1811_main_supplies[i];
		break;
	case WM8994:
		for (i = 0; i < ARRAY_SIZE(wm8994_main_supplies); i++)
			wm8994->supplies[i].supply = wm8994_main_supplies[i];
		break;
	case WM8958:
		for (i = 0; i < ARRAY_SIZE(wm8958_main_supplies); i++)
			wm8994->supplies[i].supply = wm8958_main_supplies[i];
		break;
	default:
		BUG();
		goto err;
	}

	/*
	 * Can't use devres helper here as some of the supplies are provided by
	 * wm8994->dev's children (regulators) and those regulators are
	 * unregistered by the devres core before the supplies are freed.
	 */
	ret = regulator_bulk_get(wm8994->dev, wm8994->num_supplies,
				 wm8994->supplies);
	if (ret != 0) {
		dev_err(wm8994->dev, "Failed to get supplies: %d\n", ret);
		goto err;
	}

	ret = regulator_bulk_enable(wm8994->num_supplies, wm8994->supplies);
	if (ret != 0) {
		dev_err(wm8994->dev, "Failed to enable supplies: %d\n", ret);
		goto err_regulator_free;
	}

	ret = wm8994_reg_read(wm8994, WM8994_SOFTWARE_RESET);
	if (ret < 0) {
		dev_err(wm8994->dev, "Failed to read ID register\n");
		goto err_enable;
	}
	switch (ret) {
	case 0x1811:
		devname = "WM1811";
		if (wm8994->type != WM1811)
			dev_warn(wm8994->dev, "Device registered as type %d\n",
				 wm8994->type);
		wm8994->type = WM1811;
		break;
	case 0x8994:
		devname = "WM8994";
		if (wm8994->type != WM8994)
			dev_warn(wm8994->dev, "Device registered as type %d\n",
				 wm8994->type);
		wm8994->type = WM8994;
		break;
	case 0x8958:
		devname = "WM8958";
		if (wm8994->type != WM8958)
			dev_warn(wm8994->dev, "Device registered as type %d\n",
				 wm8994->type);
		wm8994->type = WM8958;
		break;
	default:
		dev_err(wm8994->dev, "Device is not a WM8994, ID is %x\n",
			ret);
		ret = -EINVAL;
		goto err_enable;
	}

	ret = wm8994_reg_read(wm8994, WM8994_CHIP_REVISION);
	if (ret < 0) {
		dev_err(wm8994->dev, "Failed to read revision register: %d\n",
			ret);
		goto err_enable;
	}
	wm8994->revision = ret & WM8994_CHIP_REV_MASK;
	wm8994->cust_id = (ret & WM8994_CUST_ID_MASK) >> WM8994_CUST_ID_SHIFT;

	switch (wm8994->type) {
	case WM8994:
		switch (wm8994->revision) {
		case 0:
		case 1:
			dev_warn(wm8994->dev,
				 "revision %c not fully supported\n",
				 'A' + wm8994->revision);
			break;
		case 2:
		case 3:
		default:
			regmap_patch = wm8994_revc_patch;
			patch_regs = ARRAY_SIZE(wm8994_revc_patch);
			break;
		}
		break;

	case WM8958:
		switch (wm8994->revision) {
		case 0:
			regmap_patch = wm8958_reva_patch;
			patch_regs = ARRAY_SIZE(wm8958_reva_patch);
			break;
		default:
			break;
		}
		break;

	case WM1811:
		/* Revision C did not change the relevant layer */
		if (wm8994->revision > 1)
			wm8994->revision++;

		regmap_patch = wm1811_reva_patch;
		patch_regs = ARRAY_SIZE(wm1811_reva_patch);
		break;

	default:
		break;
	}

	dev_info(wm8994->dev, "%s revision %c CUST_ID %02x\n", devname,
		 'A' + wm8994->revision, wm8994->cust_id);

	switch (wm8994->type) {
	case WM1811:
		regmap_config = &wm1811_regmap_config;
		break;
	case WM8994:
		regmap_config = &wm8994_regmap_config;
		break;
	case WM8958:
		regmap_config = &wm8958_regmap_config;
		break;
	default:
		dev_err(wm8994->dev, "Unknown device type %d\n", wm8994->type);
		ret = -EINVAL;
		goto err_enable;
	}

	ret = regmap_reinit_cache(wm8994->regmap, regmap_config);
	if (ret != 0) {
		dev_err(wm8994->dev, "Failed to reinit register cache: %d\n",
			ret);
		goto err_enable;
	}

	/* Explicitly put the device into reset in case regulators
	 * don't get disabled in order to ensure we know the device
	 * state.
	 */
	ret = wm8994_reg_write(wm8994, WM8994_SOFTWARE_RESET,
			       wm8994_reg_read(wm8994, WM8994_SOFTWARE_RESET));
	if (ret != 0) {
		dev_err(wm8994->dev, "Failed to reset device: %d\n", ret);
		goto err_enable;
	}

	if (regmap_patch) {
		ret = regmap_register_patch(wm8994->regmap, regmap_patch,
					    patch_regs);
		if (ret != 0) {
			dev_err(wm8994->dev, "Failed to register patch: %d\n",
				ret);
			goto err_enable;
		}
	}

	wm8994->irq_base = pdata->irq_base;
	wm8994->gpio_base = pdata->gpio_base;

	/* GPIO configuration is only applied if it's non-zero */
	for (i = 0; i < ARRAY_SIZE(pdata->gpio_defaults); i++) {
		if (pdata->gpio_defaults[i]) {
			wm8994_set_bits(wm8994, WM8994_GPIO_1 + i,
					0xffff, pdata->gpio_defaults[i]);
		}
	}

	wm8994->ldo_ena_always_driven = pdata->ldo_ena_always_driven;

	if (pdata->spkmode_pu)
		pulls |= WM8994_SPKMODE_PU;
	if (pdata->csnaddr_pd)
		pulls |= WM8994_CSNADDR_PD;

	/* Disable unneeded pulls */
	wm8994_set_bits(wm8994, WM8994_PULL_CONTROL_2,
			WM8994_LDO1ENA_PD | WM8994_LDO2ENA_PD |
			WM8994_SPKMODE_PU | WM8994_CSNADDR_PD,
			pulls);

	/* In some system designs where the regulators are not in use,
	 * we can achieve a small reduction in leakage currents by
	 * floating LDO outputs.  This bit makes no difference if the
	 * LDOs are enabled, it only affects cases where the LDOs were
	 * in operation and are then disabled.
	 */
	for (i = 0; i < WM8994_NUM_LDO_REGS; i++) {
		if (wm8994_ldo_in_use(pdata, i))
			wm8994_set_bits(wm8994, WM8994_LDO_1 + i,
					WM8994_LDO1_DISCH, WM8994_LDO1_DISCH);
		else
			wm8994_set_bits(wm8994, WM8994_LDO_1 + i,
					WM8994_LDO1_DISCH, 0);
	}

	wm8994_irq_init(wm8994);

	ret = mfd_add_devices(wm8994->dev, -1,
			      wm8994_devs, ARRAY_SIZE(wm8994_devs),
			      NULL, 0, NULL);
	if (ret != 0) {
		dev_err(wm8994->dev, "Failed to add children: %d\n", ret);
		goto err_irq;
	}

	pm_runtime_enable(wm8994->dev);
	pm_runtime_idle(wm8994->dev);

	return 0;

err_irq:
	wm8994_irq_exit(wm8994);
err_enable:
	regulator_bulk_disable(wm8994->num_supplies,
			       wm8994->supplies);
err_regulator_free:
	regulator_bulk_free(wm8994->num_supplies, wm8994->supplies);
err:
	mfd_remove_devices(wm8994->dev);
	return ret;
}