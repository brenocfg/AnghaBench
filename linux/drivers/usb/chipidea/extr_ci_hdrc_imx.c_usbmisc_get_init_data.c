#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct platform_device {int /*<<< orphan*/  dev; } ;
struct of_phandle_args {int /*<<< orphan*/  np; int /*<<< orphan*/ * args; } ;
struct imx_usbmisc_data {int disable_oc; int oc_pol_active_low; int oc_pol_configured; int ulpi; void* evdo; void* pwr_pol; int /*<<< orphan*/ * dev; int /*<<< orphan*/  index; } ;
struct device_node {int dummy; } ;
struct device {struct device_node* of_node; } ;

/* Variables and functions */
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 struct imx_usbmisc_data* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ USBPHY_INTERFACE_MODE_ULPI ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*) ; 
 struct imx_usbmisc_data* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 struct platform_device* of_find_device_by_node (int /*<<< orphan*/ ) ; 
 scalar_t__ of_find_property (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_get_property (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_node_put (int /*<<< orphan*/ ) ; 
 int of_parse_phandle_with_args (struct device_node*,char*,char*,int /*<<< orphan*/ ,struct of_phandle_args*) ; 
 void* of_property_read_bool (struct device_node*,char*) ; 
 scalar_t__ of_usb_get_phy_mode (struct device_node*) ; 
 int /*<<< orphan*/  platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static struct imx_usbmisc_data *usbmisc_get_init_data(struct device *dev)
{
	struct platform_device *misc_pdev;
	struct device_node *np = dev->of_node;
	struct of_phandle_args args;
	struct imx_usbmisc_data *data;
	int ret;

	/*
	 * In case the fsl,usbmisc property is not present this device doesn't
	 * need usbmisc. Return NULL (which is no error here)
	 */
	if (!of_get_property(np, "fsl,usbmisc", NULL))
		return NULL;

	data = devm_kzalloc(dev, sizeof(*data), GFP_KERNEL);
	if (!data)
		return ERR_PTR(-ENOMEM);

	ret = of_parse_phandle_with_args(np, "fsl,usbmisc", "#index-cells",
					0, &args);
	if (ret) {
		dev_err(dev, "Failed to parse property fsl,usbmisc, errno %d\n",
			ret);
		return ERR_PTR(ret);
	}

	data->index = args.args[0];

	misc_pdev = of_find_device_by_node(args.np);
	of_node_put(args.np);

	if (!misc_pdev || !platform_get_drvdata(misc_pdev))
		return ERR_PTR(-EPROBE_DEFER);

	data->dev = &misc_pdev->dev;

	/*
	 * Check the various over current related properties. If over current
	 * detection is disabled we're not interested in the polarity.
	 */
	if (of_find_property(np, "disable-over-current", NULL)) {
		data->disable_oc = 1;
	} else if (of_find_property(np, "over-current-active-high", NULL)) {
		data->oc_pol_active_low = 0;
		data->oc_pol_configured = 1;
	} else if (of_find_property(np, "over-current-active-low", NULL)) {
		data->oc_pol_active_low = 1;
		data->oc_pol_configured = 1;
	} else {
		dev_warn(dev, "No over current polarity defined\n");
	}

	data->pwr_pol = of_property_read_bool(np, "power-active-high");
	data->evdo = of_property_read_bool(np, "external-vbus-divider");

	if (of_usb_get_phy_mode(np) == USBPHY_INTERFACE_MODE_ULPI)
		data->ulpi = 1;

	return data;
}