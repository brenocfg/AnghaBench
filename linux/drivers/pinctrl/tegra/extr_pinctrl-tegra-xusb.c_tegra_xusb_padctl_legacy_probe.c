#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  owner; int /*<<< orphan*/ * confops; int /*<<< orphan*/ * pmxops; int /*<<< orphan*/ * pctlops; int /*<<< orphan*/  npins; int /*<<< orphan*/  pins; int /*<<< orphan*/  name; } ;
struct tegra_xusb_padctl {struct phy* rst; struct phy* provider; struct phy** phys; struct phy* pinctrl; TYPE_1__ desc; TYPE_2__* dev; struct phy* regs; int /*<<< orphan*/  soc; int /*<<< orphan*/  lock; } ;
struct resource {int dummy; } ;
struct TYPE_12__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_2__ dev; } ;
struct phy {int dummy; } ;
struct of_device_id {int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (struct phy*) ; 
 int PTR_ERR (struct phy*) ; 
 size_t TEGRA_XUSB_PADCTL_PCIE ; 
 size_t TEGRA_XUSB_PADCTL_SATA ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*,...) ; 
 int /*<<< orphan*/  dev_name (TYPE_2__*) ; 
 struct phy* devm_ioremap_resource (TYPE_2__*,struct resource*) ; 
 struct tegra_xusb_padctl* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 struct phy* devm_of_phy_provider_register (TYPE_2__*,int /*<<< orphan*/ ) ; 
 struct phy* devm_phy_create (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct phy* devm_pinctrl_register (TYPE_2__*,TYPE_1__*,struct tegra_xusb_padctl*) ; 
 struct phy* devm_reset_control_get_exclusive (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 struct of_device_id* of_match_node (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcie_phy_ops ; 
 int /*<<< orphan*/  phy_set_drvdata (struct phy*,struct tegra_xusb_padctl*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct tegra_xusb_padctl*) ; 
 int /*<<< orphan*/  reset_control_assert (struct phy*) ; 
 int reset_control_deassert (struct phy*) ; 
 int /*<<< orphan*/  sata_phy_ops ; 
 int /*<<< orphan*/  tegra124_pins ; 
 int /*<<< orphan*/  tegra_xusb_padctl_of_match ; 
 int /*<<< orphan*/  tegra_xusb_padctl_pinconf_ops ; 
 int /*<<< orphan*/  tegra_xusb_padctl_pinctrl_ops ; 
 int /*<<< orphan*/  tegra_xusb_padctl_pinmux_ops ; 
 int /*<<< orphan*/  tegra_xusb_padctl_xlate ; 

int tegra_xusb_padctl_legacy_probe(struct platform_device *pdev)
{
	struct tegra_xusb_padctl *padctl;
	const struct of_device_id *match;
	struct resource *res;
	struct phy *phy;
	int err;

	padctl = devm_kzalloc(&pdev->dev, sizeof(*padctl), GFP_KERNEL);
	if (!padctl)
		return -ENOMEM;

	platform_set_drvdata(pdev, padctl);
	mutex_init(&padctl->lock);
	padctl->dev = &pdev->dev;

	match = of_match_node(tegra_xusb_padctl_of_match, pdev->dev.of_node);
	padctl->soc = match->data;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	padctl->regs = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(padctl->regs))
		return PTR_ERR(padctl->regs);

	padctl->rst = devm_reset_control_get_exclusive(&pdev->dev, NULL);
	if (IS_ERR(padctl->rst))
		return PTR_ERR(padctl->rst);

	err = reset_control_deassert(padctl->rst);
	if (err < 0)
		return err;

	memset(&padctl->desc, 0, sizeof(padctl->desc));
	padctl->desc.name = dev_name(padctl->dev);
	padctl->desc.pins = tegra124_pins;
	padctl->desc.npins = ARRAY_SIZE(tegra124_pins);
	padctl->desc.pctlops = &tegra_xusb_padctl_pinctrl_ops;
	padctl->desc.pmxops = &tegra_xusb_padctl_pinmux_ops;
	padctl->desc.confops = &tegra_xusb_padctl_pinconf_ops;
	padctl->desc.owner = THIS_MODULE;

	padctl->pinctrl = devm_pinctrl_register(&pdev->dev, &padctl->desc,
						padctl);
	if (IS_ERR(padctl->pinctrl)) {
		dev_err(&pdev->dev, "failed to register pincontrol\n");
		err = PTR_ERR(padctl->pinctrl);
		goto reset;
	}

	phy = devm_phy_create(&pdev->dev, NULL, &pcie_phy_ops);
	if (IS_ERR(phy)) {
		err = PTR_ERR(phy);
		goto reset;
	}

	padctl->phys[TEGRA_XUSB_PADCTL_PCIE] = phy;
	phy_set_drvdata(phy, padctl);

	phy = devm_phy_create(&pdev->dev, NULL, &sata_phy_ops);
	if (IS_ERR(phy)) {
		err = PTR_ERR(phy);
		goto reset;
	}

	padctl->phys[TEGRA_XUSB_PADCTL_SATA] = phy;
	phy_set_drvdata(phy, padctl);

	padctl->provider = devm_of_phy_provider_register(&pdev->dev,
							 tegra_xusb_padctl_xlate);
	if (IS_ERR(padctl->provider)) {
		err = PTR_ERR(padctl->provider);
		dev_err(&pdev->dev, "failed to register PHYs: %d\n", err);
		goto reset;
	}

	return 0;

reset:
	reset_control_assert(padctl->rst);
	return err;
}