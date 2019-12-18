#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  notifier_call; } ;
struct sc2731_charger_info {TYPE_1__ usb_notify; int /*<<< orphan*/  usb_phy; int /*<<< orphan*/  psy_usb; int /*<<< orphan*/  base; int /*<<< orphan*/  regmap; int /*<<< orphan*/  work; TYPE_2__* dev; int /*<<< orphan*/  lock; } ;
struct power_supply_config {struct device_node* of_node; struct sc2731_charger_info* drv_data; } ;
struct TYPE_7__ {int /*<<< orphan*/  parent; struct device_node* of_node; } ;
struct platform_device {TYPE_2__ dev; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*,...) ; 
 int /*<<< orphan*/  dev_get_regmap (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct sc2731_charger_info* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_power_supply_register (TYPE_2__*,int /*<<< orphan*/ *,struct power_supply_config*) ; 
 int /*<<< orphan*/  devm_usb_get_phy_by_phandle (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int of_property_read_u32 (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sc2731_charger_desc ; 
 int /*<<< orphan*/  sc2731_charger_detect_status (struct sc2731_charger_info*) ; 
 int sc2731_charger_hw_init (struct sc2731_charger_info*) ; 
 int /*<<< orphan*/  sc2731_charger_usb_change ; 
 int /*<<< orphan*/  sc2731_charger_work ; 
 int usb_register_notifier (int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static int sc2731_charger_probe(struct platform_device *pdev)
{
	struct device_node *np = pdev->dev.of_node;
	struct sc2731_charger_info *info;
	struct power_supply_config charger_cfg = { };
	int ret;

	info = devm_kzalloc(&pdev->dev, sizeof(*info), GFP_KERNEL);
	if (!info)
		return -ENOMEM;

	mutex_init(&info->lock);
	info->dev = &pdev->dev;
	INIT_WORK(&info->work, sc2731_charger_work);

	info->regmap = dev_get_regmap(pdev->dev.parent, NULL);
	if (!info->regmap) {
		dev_err(&pdev->dev, "failed to get charger regmap\n");
		return -ENODEV;
	}

	ret = of_property_read_u32(np, "reg", &info->base);
	if (ret) {
		dev_err(&pdev->dev, "failed to get register address\n");
		return -ENODEV;
	}

	charger_cfg.drv_data = info;
	charger_cfg.of_node = np;
	info->psy_usb = devm_power_supply_register(&pdev->dev,
						   &sc2731_charger_desc,
						   &charger_cfg);
	if (IS_ERR(info->psy_usb)) {
		dev_err(&pdev->dev, "failed to register power supply\n");
		return PTR_ERR(info->psy_usb);
	}

	ret = sc2731_charger_hw_init(info);
	if (ret)
		return ret;

	info->usb_phy = devm_usb_get_phy_by_phandle(&pdev->dev, "phys", 0);
	if (IS_ERR(info->usb_phy)) {
		dev_err(&pdev->dev, "failed to find USB phy\n");
		return PTR_ERR(info->usb_phy);
	}

	info->usb_notify.notifier_call = sc2731_charger_usb_change;
	ret = usb_register_notifier(info->usb_phy, &info->usb_notify);
	if (ret) {
		dev_err(&pdev->dev, "failed to register notifier: %d\n", ret);
		return ret;
	}

	sc2731_charger_detect_status(info);

	return 0;
}