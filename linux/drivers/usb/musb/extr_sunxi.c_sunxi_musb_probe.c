#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  notifier_call; } ;
struct sunxi_glue {int /*<<< orphan*/  usb_phy; int /*<<< orphan*/  musb_pdev; int /*<<< orphan*/  xceiv; int /*<<< orphan*/  phy; int /*<<< orphan*/  extcon; int /*<<< orphan*/  rst; int /*<<< orphan*/  flags; int /*<<< orphan*/  clk; TYPE_1__ host_nb; int /*<<< orphan*/  work; TYPE_2__* dev; int /*<<< orphan*/  phy_mode; } ;
struct platform_device_info {char* name; int size_data; struct platform_device_info* data; int /*<<< orphan*/  num_res; int /*<<< orphan*/  res; TYPE_2__* parent; int /*<<< orphan*/  id; int /*<<< orphan*/ * config; int /*<<< orphan*/ * platform_ops; int /*<<< orphan*/  mode; } ;
struct TYPE_11__ {struct device_node* of_node; } ;
struct platform_device {TYPE_2__ dev; int /*<<< orphan*/  num_resources; int /*<<< orphan*/  resource; } ;
struct musb_hdrc_platform_data {char* name; int size_data; struct musb_hdrc_platform_data* data; int /*<<< orphan*/  num_res; int /*<<< orphan*/  res; TYPE_2__* parent; int /*<<< orphan*/  id; int /*<<< orphan*/ * config; int /*<<< orphan*/ * platform_ops; int /*<<< orphan*/  mode; } ;
struct device_node {int dummy; } ;
typedef  int /*<<< orphan*/  pinfo ;
typedef  int /*<<< orphan*/  pdata ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MUSB_HOST ; 
 int /*<<< orphan*/  MUSB_OTG ; 
 int /*<<< orphan*/  MUSB_PERIPHERAL ; 
 int /*<<< orphan*/  PHY_MODE_USB_DEVICE ; 
 int /*<<< orphan*/  PHY_MODE_USB_HOST ; 
 int /*<<< orphan*/  PHY_MODE_USB_OTG ; 
 int /*<<< orphan*/  PLATFORM_DEVID_AUTO ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SUNXI_MUSB_FL_HAS_RESET ; 
 int /*<<< orphan*/  SUNXI_MUSB_FL_HAS_SRAM ; 
 int /*<<< orphan*/  SUNXI_MUSB_FL_NO_CONFIGDATA ; 
#define  USB_DR_MODE_HOST 130 
#define  USB_DR_MODE_OTG 129 
#define  USB_DR_MODE_PERIPHERAL 128 
 int /*<<< orphan*/  USB_PHY_TYPE_USB2 ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*,...) ; 
 int /*<<< orphan*/  devm_clk_get (TYPE_2__*,int /*<<< orphan*/ *) ; 
 struct sunxi_glue* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_phy_get (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  devm_reset_control_get (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_usb_get_phy (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  extcon_get_edev_by_phandle (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct platform_device_info*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ of_device_is_compatible (struct device_node*,char*) ; 
 int /*<<< orphan*/  platform_device_register_full (struct platform_device_info*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct sunxi_glue*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sunxi_musb_hdrc_config ; 
 int /*<<< orphan*/  sunxi_musb_hdrc_config_h3 ; 
 int /*<<< orphan*/  sunxi_musb_host_notifier ; 
 int /*<<< orphan*/  sunxi_musb_ops ; 
 int /*<<< orphan*/  sunxi_musb_work ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int usb_get_dr_mode (TYPE_2__*) ; 
 int /*<<< orphan*/  usb_phy_generic_register () ; 
 int /*<<< orphan*/  usb_phy_generic_unregister (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sunxi_musb_probe(struct platform_device *pdev)
{
	struct musb_hdrc_platform_data	pdata;
	struct platform_device_info	pinfo;
	struct sunxi_glue		*glue;
	struct device_node		*np = pdev->dev.of_node;
	int ret;

	if (!np) {
		dev_err(&pdev->dev, "Error no device tree node found\n");
		return -EINVAL;
	}

	glue = devm_kzalloc(&pdev->dev, sizeof(*glue), GFP_KERNEL);
	if (!glue)
		return -ENOMEM;

	memset(&pdata, 0, sizeof(pdata));
	switch (usb_get_dr_mode(&pdev->dev)) {
#if defined CONFIG_USB_MUSB_DUAL_ROLE || defined CONFIG_USB_MUSB_HOST
	case USB_DR_MODE_HOST:
		pdata.mode = MUSB_HOST;
		glue->phy_mode = PHY_MODE_USB_HOST;
		break;
#endif
#if defined CONFIG_USB_MUSB_DUAL_ROLE || defined CONFIG_USB_MUSB_GADGET
	case USB_DR_MODE_PERIPHERAL:
		pdata.mode = MUSB_PERIPHERAL;
		glue->phy_mode = PHY_MODE_USB_DEVICE;
		break;
#endif
#ifdef CONFIG_USB_MUSB_DUAL_ROLE
	case USB_DR_MODE_OTG:
		pdata.mode = MUSB_OTG;
		glue->phy_mode = PHY_MODE_USB_OTG;
		break;
#endif
	default:
		dev_err(&pdev->dev, "Invalid or missing 'dr_mode' property\n");
		return -EINVAL;
	}
	pdata.platform_ops	= &sunxi_musb_ops;
	if (!of_device_is_compatible(np, "allwinner,sun8i-h3-musb"))
		pdata.config = &sunxi_musb_hdrc_config;
	else
		pdata.config = &sunxi_musb_hdrc_config_h3;

	glue->dev = &pdev->dev;
	INIT_WORK(&glue->work, sunxi_musb_work);
	glue->host_nb.notifier_call = sunxi_musb_host_notifier;

	if (of_device_is_compatible(np, "allwinner,sun4i-a10-musb"))
		set_bit(SUNXI_MUSB_FL_HAS_SRAM, &glue->flags);

	if (of_device_is_compatible(np, "allwinner,sun6i-a31-musb"))
		set_bit(SUNXI_MUSB_FL_HAS_RESET, &glue->flags);

	if (of_device_is_compatible(np, "allwinner,sun8i-a33-musb") ||
	    of_device_is_compatible(np, "allwinner,sun8i-h3-musb")) {
		set_bit(SUNXI_MUSB_FL_HAS_RESET, &glue->flags);
		set_bit(SUNXI_MUSB_FL_NO_CONFIGDATA, &glue->flags);
	}

	glue->clk = devm_clk_get(&pdev->dev, NULL);
	if (IS_ERR(glue->clk)) {
		dev_err(&pdev->dev, "Error getting clock: %ld\n",
			PTR_ERR(glue->clk));
		return PTR_ERR(glue->clk);
	}

	if (test_bit(SUNXI_MUSB_FL_HAS_RESET, &glue->flags)) {
		glue->rst = devm_reset_control_get(&pdev->dev, NULL);
		if (IS_ERR(glue->rst)) {
			if (PTR_ERR(glue->rst) == -EPROBE_DEFER)
				return -EPROBE_DEFER;
			dev_err(&pdev->dev, "Error getting reset %ld\n",
				PTR_ERR(glue->rst));
			return PTR_ERR(glue->rst);
		}
	}

	glue->extcon = extcon_get_edev_by_phandle(&pdev->dev, 0);
	if (IS_ERR(glue->extcon)) {
		if (PTR_ERR(glue->extcon) == -EPROBE_DEFER)
			return -EPROBE_DEFER;
		dev_err(&pdev->dev, "Invalid or missing extcon\n");
		return PTR_ERR(glue->extcon);
	}

	glue->phy = devm_phy_get(&pdev->dev, "usb");
	if (IS_ERR(glue->phy)) {
		if (PTR_ERR(glue->phy) == -EPROBE_DEFER)
			return -EPROBE_DEFER;
		dev_err(&pdev->dev, "Error getting phy %ld\n",
			PTR_ERR(glue->phy));
		return PTR_ERR(glue->phy);
	}

	glue->usb_phy = usb_phy_generic_register();
	if (IS_ERR(glue->usb_phy)) {
		dev_err(&pdev->dev, "Error registering usb-phy %ld\n",
			PTR_ERR(glue->usb_phy));
		return PTR_ERR(glue->usb_phy);
	}

	glue->xceiv = devm_usb_get_phy(&pdev->dev, USB_PHY_TYPE_USB2);
	if (IS_ERR(glue->xceiv)) {
		ret = PTR_ERR(glue->xceiv);
		dev_err(&pdev->dev, "Error getting usb-phy %d\n", ret);
		goto err_unregister_usb_phy;
	}

	platform_set_drvdata(pdev, glue);

	memset(&pinfo, 0, sizeof(pinfo));
	pinfo.name	 = "musb-hdrc";
	pinfo.id	= PLATFORM_DEVID_AUTO;
	pinfo.parent	= &pdev->dev;
	pinfo.res	= pdev->resource;
	pinfo.num_res	= pdev->num_resources;
	pinfo.data	= &pdata;
	pinfo.size_data = sizeof(pdata);

	glue->musb_pdev = platform_device_register_full(&pinfo);
	if (IS_ERR(glue->musb_pdev)) {
		ret = PTR_ERR(glue->musb_pdev);
		dev_err(&pdev->dev, "Error registering musb dev: %d\n", ret);
		goto err_unregister_usb_phy;
	}

	return 0;

err_unregister_usb_phy:
	usb_phy_generic_unregister(glue->usb_phy);
	return ret;
}