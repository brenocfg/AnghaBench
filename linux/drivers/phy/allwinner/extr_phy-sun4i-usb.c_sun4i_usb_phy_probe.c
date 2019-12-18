#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ priority; int /*<<< orphan*/  notifier_call; } ;
struct sun4i_usb_phy_data {scalar_t__ id_det_irq; scalar_t__ vbus_det_irq; int vbus_power_nb_registered; TYPE_1__ vbus_power_nb; struct phy_provider* vbus_power_supply; struct phy_provider* vbus_det_gpio; struct phy_provider* id_det_gpio; struct sun4i_usb_phy* phys; TYPE_2__* cfg; struct phy_provider* extcon; int /*<<< orphan*/  dr_mode; struct phy_provider* base; int /*<<< orphan*/  detect; int /*<<< orphan*/  reg_lock; } ;
struct sun4i_usb_phy {int index; struct phy_provider* phy; struct phy_provider* pmu; struct phy_provider* reset; struct phy_provider* clk2; struct phy_provider* clk; struct phy_provider* vbus; } ;
struct resource {int dummy; } ;
struct device {struct device_node* of_node; } ;
struct platform_device {struct device dev; } ;
struct phy_provider {int dummy; } ;
struct device_node {int dummy; } ;
typedef  int /*<<< orphan*/  name ;
struct TYPE_4__ {int num_phys; int missing_phys; int hsic_index; scalar_t__ phy0_dual_route; scalar_t__ dedicated_clocks; } ;

/* Variables and functions */
 int BIT (int) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOD_IN ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int IRQF_TRIGGER_FALLING ; 
 int IRQF_TRIGGER_RISING ; 
 scalar_t__ IS_ERR (struct phy_provider*) ; 
 int PTR_ERR (struct phy_provider*) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct sun4i_usb_phy_data*) ; 
 void* devm_clk_get (struct device*,char*) ; 
 struct phy_provider* devm_extcon_dev_allocate (struct device*,int /*<<< orphan*/ ) ; 
 int devm_extcon_dev_register (struct device*,struct phy_provider*) ; 
 void* devm_gpiod_get_optional (struct device*,char*,int /*<<< orphan*/ ) ; 
 void* devm_ioremap_resource (struct device*,struct resource*) ; 
 struct sun4i_usb_phy_data* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 struct phy_provider* devm_of_phy_provider_register (struct device*,int /*<<< orphan*/ ) ; 
 struct phy_provider* devm_phy_create (struct device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct phy_provider* devm_power_supply_get_by_phandle (struct device*,char*) ; 
 struct phy_provider* devm_regulator_get_optional (struct device*,char*) ; 
 int devm_request_irq (struct device*,scalar_t__,int /*<<< orphan*/ ,int,char*,struct sun4i_usb_phy_data*) ; 
 struct phy_provider* devm_reset_control_get (struct device*,char*) ; 
 void* gpiod_to_irq (struct phy_provider*) ; 
 TYPE_2__* of_device_get_match_data (struct device*) ; 
 scalar_t__ of_find_property (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_usb_get_dr_mode_by_phy (struct device_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_set_drvdata (struct phy_provider*,struct sun4i_usb_phy*) ; 
 struct resource* platform_get_resource_byname (struct platform_device*,int /*<<< orphan*/ ,char*) ; 
 int power_supply_reg_notifier (TYPE_1__*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 
 int /*<<< orphan*/  sun4i_usb_phy0_cable ; 
 int /*<<< orphan*/  sun4i_usb_phy0_id_vbus_det_irq ; 
 int /*<<< orphan*/  sun4i_usb_phy0_id_vbus_det_scan ; 
 int /*<<< orphan*/  sun4i_usb_phy0_vbus_notify ; 
 int /*<<< orphan*/  sun4i_usb_phy_ops ; 
 int /*<<< orphan*/  sun4i_usb_phy_remove (struct platform_device*) ; 
 int /*<<< orphan*/  sun4i_usb_phy_xlate ; 

__attribute__((used)) static int sun4i_usb_phy_probe(struct platform_device *pdev)
{
	struct sun4i_usb_phy_data *data;
	struct device *dev = &pdev->dev;
	struct device_node *np = dev->of_node;
	struct phy_provider *phy_provider;
	struct resource *res;
	int i, ret;

	data = devm_kzalloc(dev, sizeof(*data), GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	spin_lock_init(&data->reg_lock);
	INIT_DELAYED_WORK(&data->detect, sun4i_usb_phy0_id_vbus_det_scan);
	dev_set_drvdata(dev, data);
	data->cfg = of_device_get_match_data(dev);
	if (!data->cfg)
		return -EINVAL;

	res = platform_get_resource_byname(pdev, IORESOURCE_MEM, "phy_ctrl");
	data->base = devm_ioremap_resource(dev, res);
	if (IS_ERR(data->base))
		return PTR_ERR(data->base);

	data->id_det_gpio = devm_gpiod_get_optional(dev, "usb0_id_det",
						    GPIOD_IN);
	if (IS_ERR(data->id_det_gpio)) {
		dev_err(dev, "Couldn't request ID GPIO\n");
		return PTR_ERR(data->id_det_gpio);
	}

	data->vbus_det_gpio = devm_gpiod_get_optional(dev, "usb0_vbus_det",
						      GPIOD_IN);
	if (IS_ERR(data->vbus_det_gpio)) {
		dev_err(dev, "Couldn't request VBUS detect GPIO\n");
		return PTR_ERR(data->vbus_det_gpio);
	}

	if (of_find_property(np, "usb0_vbus_power-supply", NULL)) {
		data->vbus_power_supply = devm_power_supply_get_by_phandle(dev,
						     "usb0_vbus_power-supply");
		if (IS_ERR(data->vbus_power_supply)) {
			dev_err(dev, "Couldn't get the VBUS power supply\n");
			return PTR_ERR(data->vbus_power_supply);
		}

		if (!data->vbus_power_supply)
			return -EPROBE_DEFER;
	}

	data->dr_mode = of_usb_get_dr_mode_by_phy(np, 0);

	data->extcon = devm_extcon_dev_allocate(dev, sun4i_usb_phy0_cable);
	if (IS_ERR(data->extcon)) {
		dev_err(dev, "Couldn't allocate our extcon device\n");
		return PTR_ERR(data->extcon);
	}

	ret = devm_extcon_dev_register(dev, data->extcon);
	if (ret) {
		dev_err(dev, "failed to register extcon: %d\n", ret);
		return ret;
	}

	for (i = 0; i < data->cfg->num_phys; i++) {
		struct sun4i_usb_phy *phy = data->phys + i;
		char name[16];

		if (data->cfg->missing_phys & BIT(i))
			continue;

		snprintf(name, sizeof(name), "usb%d_vbus", i);
		phy->vbus = devm_regulator_get_optional(dev, name);
		if (IS_ERR(phy->vbus)) {
			if (PTR_ERR(phy->vbus) == -EPROBE_DEFER) {
				dev_err(dev,
					"Couldn't get regulator %s... Deferring probe\n",
					name);
				return -EPROBE_DEFER;
			}

			phy->vbus = NULL;
		}

		if (data->cfg->dedicated_clocks)
			snprintf(name, sizeof(name), "usb%d_phy", i);
		else
			strlcpy(name, "usb_phy", sizeof(name));

		phy->clk = devm_clk_get(dev, name);
		if (IS_ERR(phy->clk)) {
			dev_err(dev, "failed to get clock %s\n", name);
			return PTR_ERR(phy->clk);
		}

		/* The first PHY is always tied to OTG, and never HSIC */
		if (data->cfg->hsic_index && i == data->cfg->hsic_index) {
			/* HSIC needs secondary clock */
			snprintf(name, sizeof(name), "usb%d_hsic_12M", i);
			phy->clk2 = devm_clk_get(dev, name);
			if (IS_ERR(phy->clk2)) {
				dev_err(dev, "failed to get clock %s\n", name);
				return PTR_ERR(phy->clk2);
			}
		}

		snprintf(name, sizeof(name), "usb%d_reset", i);
		phy->reset = devm_reset_control_get(dev, name);
		if (IS_ERR(phy->reset)) {
			dev_err(dev, "failed to get reset %s\n", name);
			return PTR_ERR(phy->reset);
		}

		if (i || data->cfg->phy0_dual_route) { /* No pmu for musb */
			snprintf(name, sizeof(name), "pmu%d", i);
			res = platform_get_resource_byname(pdev,
							IORESOURCE_MEM, name);
			phy->pmu = devm_ioremap_resource(dev, res);
			if (IS_ERR(phy->pmu))
				return PTR_ERR(phy->pmu);
		}

		phy->phy = devm_phy_create(dev, NULL, &sun4i_usb_phy_ops);
		if (IS_ERR(phy->phy)) {
			dev_err(dev, "failed to create PHY %d\n", i);
			return PTR_ERR(phy->phy);
		}

		phy->index = i;
		phy_set_drvdata(phy->phy, &data->phys[i]);
	}

	data->id_det_irq = gpiod_to_irq(data->id_det_gpio);
	if (data->id_det_irq > 0) {
		ret = devm_request_irq(dev, data->id_det_irq,
				sun4i_usb_phy0_id_vbus_det_irq,
				IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING,
				"usb0-id-det", data);
		if (ret) {
			dev_err(dev, "Err requesting id-det-irq: %d\n", ret);
			return ret;
		}
	}

	data->vbus_det_irq = gpiod_to_irq(data->vbus_det_gpio);
	if (data->vbus_det_irq > 0) {
		ret = devm_request_irq(dev, data->vbus_det_irq,
				sun4i_usb_phy0_id_vbus_det_irq,
				IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING,
				"usb0-vbus-det", data);
		if (ret) {
			dev_err(dev, "Err requesting vbus-det-irq: %d\n", ret);
			data->vbus_det_irq = -1;
			sun4i_usb_phy_remove(pdev); /* Stop detect work */
			return ret;
		}
	}

	if (data->vbus_power_supply) {
		data->vbus_power_nb.notifier_call = sun4i_usb_phy0_vbus_notify;
		data->vbus_power_nb.priority = 0;
		ret = power_supply_reg_notifier(&data->vbus_power_nb);
		if (ret) {
			sun4i_usb_phy_remove(pdev); /* Stop detect work */
			return ret;
		}
		data->vbus_power_nb_registered = true;
	}

	phy_provider = devm_of_phy_provider_register(dev, sun4i_usb_phy_xlate);
	if (IS_ERR(phy_provider)) {
		sun4i_usb_phy_remove(pdev); /* Stop detect work */
		return PTR_ERR(phy_provider);
	}

	dev_dbg(dev, "successfully loaded\n");

	return 0;
}