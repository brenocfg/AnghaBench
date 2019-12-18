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
struct resource {int dummy; } ;
struct device {int /*<<< orphan*/  kobj; struct device_node* of_node; } ;
struct platform_device {struct device dev; } ;
struct phy_provider {int dummy; } ;
struct device_node {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  mode; int /*<<< orphan*/  ioc; int /*<<< orphan*/  ipp; void* xhci_ec_regs; void* ctrl_regs; int /*<<< orphan*/  family_name; int /*<<< orphan*/  product_id; int /*<<< orphan*/  family_id; } ;
struct brcm_usb_phy_data {int has_xhci; int has_eohci; int /*<<< orphan*/  usb_30_clk; int /*<<< orphan*/  usb_20_clk; TYPE_1__ ini; int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR_OR_ZERO (struct phy_provider*) ; 
 int /*<<< orphan*/  USB_CTLR_MODE_DRD ; 
 int /*<<< orphan*/  USB_CTLR_MODE_HOST ; 
 int /*<<< orphan*/ * brcm_dr_mode_to_name ; 
 int /*<<< orphan*/  brcm_usb_init_ipp (TYPE_1__*) ; 
 int /*<<< orphan*/ ** brcm_usb_phy_attrs ; 
 int brcm_usb_phy_dvr_init (struct device*,struct brcm_usb_phy_data*,struct device_node*) ; 
 int /*<<< orphan*/  brcm_usb_phy_group ; 
 int /*<<< orphan*/  brcm_usb_phy_xlate ; 
 int /*<<< orphan*/  brcm_usb_set_family_map (TYPE_1__*) ; 
 int /*<<< orphan*/  brcm_usb_uninit_common (TYPE_1__*) ; 
 int /*<<< orphan*/  brcm_usb_uninit_eohci (TYPE_1__*) ; 
 int /*<<< orphan*/  brcm_usb_uninit_xhci (TYPE_1__*) ; 
 int /*<<< orphan*/  brcmstb_get_family_id () ; 
 int /*<<< orphan*/  brcmstb_get_product_id () ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*) ; 
 void* devm_ioremap_resource (struct device*,struct resource*) ; 
 struct brcm_usb_phy_data* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 struct phy_provider* devm_of_phy_provider_register (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  name_to_value (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ of_property_read_bool (struct device_node*,char*) ; 
 int of_property_read_string (struct device_node*,char*,char const**) ; 
 int /*<<< orphan*/  of_property_read_u32 (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct brcm_usb_phy_data*) ; 
 int sysfs_create_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int brcm_usb_phy_probe(struct platform_device *pdev)
{
	struct resource *res;
	struct device *dev = &pdev->dev;
	struct brcm_usb_phy_data *priv;
	struct phy_provider *phy_provider;
	struct device_node *dn = pdev->dev.of_node;
	int err;
	const char *mode;

	priv = devm_kzalloc(dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;
	platform_set_drvdata(pdev, priv);

	priv->ini.family_id = brcmstb_get_family_id();
	priv->ini.product_id = brcmstb_get_product_id();
	brcm_usb_set_family_map(&priv->ini);
	dev_dbg(dev, "Best mapping table is for %s\n",
		priv->ini.family_name);
	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!res) {
		dev_err(dev, "can't get USB_CTRL base address\n");
		return -EINVAL;
	}
	priv->ini.ctrl_regs = devm_ioremap_resource(dev, res);
	if (IS_ERR(priv->ini.ctrl_regs)) {
		dev_err(dev, "can't map CTRL register space\n");
		return -EINVAL;
	}

	/* The XHCI EC registers are optional */
	res = platform_get_resource(pdev, IORESOURCE_MEM, 1);
	if (res) {
		priv->ini.xhci_ec_regs =
			devm_ioremap_resource(dev, res);
		if (IS_ERR(priv->ini.xhci_ec_regs)) {
			dev_err(dev, "can't map XHCI EC register space\n");
			return -EINVAL;
		}
	}

	of_property_read_u32(dn, "brcm,ipp", &priv->ini.ipp);
	of_property_read_u32(dn, "brcm,ioc", &priv->ini.ioc);

	priv->ini.mode = USB_CTLR_MODE_HOST;
	err = of_property_read_string(dn, "dr_mode", &mode);
	if (err == 0) {
		name_to_value(&brcm_dr_mode_to_name[0],
			      ARRAY_SIZE(brcm_dr_mode_to_name),
			mode, &priv->ini.mode);
	}
	if (of_property_read_bool(dn, "brcm,has-xhci"))
		priv->has_xhci = true;
	if (of_property_read_bool(dn, "brcm,has-eohci"))
		priv->has_eohci = true;

	err = brcm_usb_phy_dvr_init(dev, priv, dn);
	if (err)
		return err;

	mutex_init(&priv->mutex);

	/* make sure invert settings are correct */
	brcm_usb_init_ipp(&priv->ini);

	/*
	 * Create sysfs entries for mode.
	 * Remove "dual_select" attribute if not in dual mode
	 */
	if (priv->ini.mode != USB_CTLR_MODE_DRD)
		brcm_usb_phy_attrs[1] = NULL;
	err = sysfs_create_group(&dev->kobj, &brcm_usb_phy_group);
	if (err)
		dev_warn(dev, "Error creating sysfs attributes\n");

	/* start with everything off */
	if (priv->has_xhci)
		brcm_usb_uninit_xhci(&priv->ini);
	if (priv->has_eohci)
		brcm_usb_uninit_eohci(&priv->ini);
	brcm_usb_uninit_common(&priv->ini);
	clk_disable(priv->usb_20_clk);
	clk_disable(priv->usb_30_clk);

	phy_provider = devm_of_phy_provider_register(dev, brcm_usb_phy_xlate);

	return PTR_ERR_OR_ZERO(phy_provider);
}