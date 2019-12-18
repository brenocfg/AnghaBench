#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct usb_phy_data {int flags; int /*<<< orphan*/  power_off; int /*<<< orphan*/  power_on; int /*<<< orphan*/  mask; int /*<<< orphan*/  label; } ;
struct usb_otg {TYPE_1__* usb_phy; int /*<<< orphan*/  start_srp; int /*<<< orphan*/  set_vbus; int /*<<< orphan*/  set_peripheral; int /*<<< orphan*/  set_host; } ;
struct resource {int dummy; } ;
struct TYPE_14__ {struct device_node* of_node; } ;
struct platform_device {TYPE_2__ dev; } ;
struct phy_provider {int dummy; } ;
typedef  struct phy_provider phy ;
struct TYPE_13__ {int /*<<< orphan*/  type; struct usb_otg* otg; int /*<<< orphan*/  label; TYPE_2__* dev; } ;
struct omap_usb {int flags; TYPE_1__ phy; TYPE_2__* dev; struct phy_provider* optclk; struct phy_provider* wkupclk; int /*<<< orphan*/  power_reg; TYPE_2__* control_dev; struct phy_provider* syscon_phy_power; struct phy_provider* phy_base; int /*<<< orphan*/  power_off; int /*<<< orphan*/  power_on; int /*<<< orphan*/  mask; } ;
struct of_device_id {scalar_t__ data; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (struct phy_provider*) ; 
 int OMAP_USB2_CALIBRATE_FALSE_DISCONNECT ; 
 int OMAP_USB2_HAS_SET_VBUS ; 
 int OMAP_USB2_HAS_START_SRP ; 
 int PTR_ERR (struct phy_provider*) ; 
 int /*<<< orphan*/  USB_PHY_TYPE_USB2 ; 
 int /*<<< orphan*/  dev_dbg (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  dev_warn (TYPE_2__*,char*,...) ; 
 void* devm_clk_get (TYPE_2__*,char*) ; 
 struct phy_provider* devm_ioremap_resource (TYPE_2__*,struct resource*) ; 
 void* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 struct phy_provider* devm_of_phy_provider_register (TYPE_2__*,int /*<<< orphan*/ ) ; 
 struct phy_provider* devm_phy_create (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct platform_device* of_find_device_by_node (struct device_node*) ; 
 struct of_device_id* of_match_device (int /*<<< orphan*/ ,TYPE_2__*) ; 
 struct device_node* of_parse_phandle (struct device_node*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_phy_simple_xlate ; 
 scalar_t__ of_property_read_u32_index (struct device_node*,char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  omap_usb2_id_table ; 
 int /*<<< orphan*/  omap_usb_power_off (struct phy_provider*) ; 
 int /*<<< orphan*/  omap_usb_set_host ; 
 int /*<<< orphan*/  omap_usb_set_peripheral ; 
 int /*<<< orphan*/  omap_usb_set_vbus ; 
 int /*<<< orphan*/  omap_usb_start_srp ; 
 int /*<<< orphan*/  ops ; 
 int /*<<< orphan*/  phy_set_drvdata (struct phy_provider*,struct omap_usb*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct omap_usb*) ; 
 int /*<<< orphan*/  pm_runtime_disable (TYPE_2__*) ; 
 int /*<<< orphan*/  pm_runtime_enable (TYPE_2__*) ; 
 struct phy_provider* syscon_regmap_lookup_by_phandle (struct device_node*,char*) ; 
 int /*<<< orphan*/  usb_add_phy_dev (TYPE_1__*) ; 

__attribute__((used)) static int omap_usb2_probe(struct platform_device *pdev)
{
	struct omap_usb	*phy;
	struct phy *generic_phy;
	struct resource *res;
	struct phy_provider *phy_provider;
	struct usb_otg *otg;
	struct device_node *node = pdev->dev.of_node;
	struct device_node *control_node;
	struct platform_device *control_pdev;
	const struct of_device_id *of_id;
	struct usb_phy_data *phy_data;

	of_id = of_match_device(omap_usb2_id_table, &pdev->dev);

	if (!of_id)
		return -EINVAL;

	phy_data = (struct usb_phy_data *)of_id->data;

	phy = devm_kzalloc(&pdev->dev, sizeof(*phy), GFP_KERNEL);
	if (!phy)
		return -ENOMEM;

	otg = devm_kzalloc(&pdev->dev, sizeof(*otg), GFP_KERNEL);
	if (!otg)
		return -ENOMEM;

	phy->dev		= &pdev->dev;

	phy->phy.dev		= phy->dev;
	phy->phy.label		= phy_data->label;
	phy->phy.otg		= otg;
	phy->phy.type		= USB_PHY_TYPE_USB2;
	phy->mask		= phy_data->mask;
	phy->power_on		= phy_data->power_on;
	phy->power_off		= phy_data->power_off;

	if (phy_data->flags & OMAP_USB2_CALIBRATE_FALSE_DISCONNECT) {
		res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
		phy->phy_base = devm_ioremap_resource(&pdev->dev, res);
		if (IS_ERR(phy->phy_base))
			return PTR_ERR(phy->phy_base);
		phy->flags |= OMAP_USB2_CALIBRATE_FALSE_DISCONNECT;
	}

	phy->syscon_phy_power = syscon_regmap_lookup_by_phandle(node,
							"syscon-phy-power");
	if (IS_ERR(phy->syscon_phy_power)) {
		dev_dbg(&pdev->dev,
			"can't get syscon-phy-power, using control device\n");
		phy->syscon_phy_power = NULL;

		control_node = of_parse_phandle(node, "ctrl-module", 0);
		if (!control_node) {
			dev_err(&pdev->dev,
				"Failed to get control device phandle\n");
			return -EINVAL;
		}

		control_pdev = of_find_device_by_node(control_node);
		if (!control_pdev) {
			dev_err(&pdev->dev, "Failed to get control device\n");
			return -EINVAL;
		}
		phy->control_dev = &control_pdev->dev;
	} else {
		if (of_property_read_u32_index(node,
					       "syscon-phy-power", 1,
					       &phy->power_reg)) {
			dev_err(&pdev->dev,
				"couldn't get power reg. offset\n");
			return -EINVAL;
		}
	}


	phy->wkupclk = devm_clk_get(phy->dev, "wkupclk");
	if (IS_ERR(phy->wkupclk)) {
		if (PTR_ERR(phy->wkupclk) == -EPROBE_DEFER)
			return -EPROBE_DEFER;

		dev_warn(&pdev->dev, "unable to get wkupclk %ld, trying old name\n",
			 PTR_ERR(phy->wkupclk));
		phy->wkupclk = devm_clk_get(phy->dev, "usb_phy_cm_clk32k");

		if (IS_ERR(phy->wkupclk)) {
			if (PTR_ERR(phy->wkupclk) != -EPROBE_DEFER)
				dev_err(&pdev->dev, "unable to get usb_phy_cm_clk32k\n");
			return PTR_ERR(phy->wkupclk);
		} else {
			dev_warn(&pdev->dev,
				 "found usb_phy_cm_clk32k, please fix DTS\n");
		}
	}

	phy->optclk = devm_clk_get(phy->dev, "refclk");
	if (IS_ERR(phy->optclk)) {
		if (PTR_ERR(phy->optclk) == -EPROBE_DEFER)
			return -EPROBE_DEFER;

		dev_dbg(&pdev->dev, "unable to get refclk, trying old name\n");
		phy->optclk = devm_clk_get(phy->dev, "usb_otg_ss_refclk960m");

		if (IS_ERR(phy->optclk)) {
			if (PTR_ERR(phy->optclk) != -EPROBE_DEFER) {
				dev_dbg(&pdev->dev,
					"unable to get usb_otg_ss_refclk960m\n");
			}
		} else {
			dev_warn(&pdev->dev,
				 "found usb_otg_ss_refclk960m, please fix DTS\n");
		}
	}

	otg->set_host = omap_usb_set_host;
	otg->set_peripheral = omap_usb_set_peripheral;
	if (phy_data->flags & OMAP_USB2_HAS_SET_VBUS)
		otg->set_vbus = omap_usb_set_vbus;
	if (phy_data->flags & OMAP_USB2_HAS_START_SRP)
		otg->start_srp = omap_usb_start_srp;
	otg->usb_phy = &phy->phy;

	platform_set_drvdata(pdev, phy);
	pm_runtime_enable(phy->dev);

	generic_phy = devm_phy_create(phy->dev, NULL, &ops);
	if (IS_ERR(generic_phy)) {
		pm_runtime_disable(phy->dev);
		return PTR_ERR(generic_phy);
	}

	phy_set_drvdata(generic_phy, phy);
	omap_usb_power_off(generic_phy);

	phy_provider = devm_of_phy_provider_register(phy->dev,
						     of_phy_simple_xlate);
	if (IS_ERR(phy_provider)) {
		pm_runtime_disable(phy->dev);
		return PTR_ERR(phy_provider);
	}


	usb_add_phy_dev(&phy->phy);

	return 0;
}