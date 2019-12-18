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
struct device {struct device_node* of_node; } ;
struct platform_device {int /*<<< orphan*/  num_resources; int /*<<< orphan*/  resource; struct device dev; } ;
struct pinctrl_state {int hsic; } ;
struct of_device_id {struct ci_hdrc_imx_platform_flag* data; } ;
struct device_node {int dummy; } ;
struct ci_hdrc_platform_data {int flags; struct pinctrl_state* usb_phy; int /*<<< orphan*/  notify_event; int /*<<< orphan*/  capoffset; int /*<<< orphan*/  name; } ;
struct ci_hdrc_imx_platform_flag {int flags; } ;
struct ci_hdrc_imx_data {int override_phy_control; int supports_runtime_pm; struct pinctrl_state* ci_pdev; int /*<<< orphan*/  pm_qos_req; struct pinctrl_state* hsic_pad_regulator; struct pinctrl_state* usbmisc_data; struct pinctrl_state* phy; struct pinctrl_state* pinctrl_hsic_active; struct pinctrl_state* pinctrl; struct ci_hdrc_imx_platform_flag const* plat_data; } ;

/* Variables and functions */
 int CI_HDRC_IMX_IS_HSIC ; 
 int CI_HDRC_OVERRIDE_PHY_CONTROL ; 
 int CI_HDRC_PMQOS ; 
 int CI_HDRC_SUPPORTS_RUNTIME_PM ; 
 int /*<<< orphan*/  DEF_CAPOFFSET ; 
 int ENODEV ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct pinctrl_state*) ; 
 int /*<<< orphan*/  PM_QOS_CPU_DMA_LATENCY ; 
 int PTR_ERR (struct pinctrl_state*) ; 
 scalar_t__ USBPHY_INTERFACE_MODE_HSIC ; 
 scalar_t__ USBPHY_INTERFACE_MODE_ULPI ; 
 struct pinctrl_state* ci_hdrc_add_device (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ci_hdrc_platform_data*) ; 
 int /*<<< orphan*/  ci_hdrc_imx_dt_ids ; 
 int /*<<< orphan*/  ci_hdrc_imx_notify_event ; 
 int /*<<< orphan*/  ci_hdrc_remove_device (struct pinctrl_state*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int /*<<< orphan*/  device_set_wakeup_capable (struct device*,int) ; 
 struct ci_hdrc_imx_data* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 struct pinctrl_state* devm_pinctrl_get (struct device*) ; 
 struct pinctrl_state* devm_regulator_get (struct device*,char*) ; 
 struct pinctrl_state* devm_usb_get_phy_by_phandle (struct device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imx_disable_unprepare_clks (struct device*) ; 
 int imx_get_clks (struct device*) ; 
 int imx_prepare_enable_clks (struct device*) ; 
 int imx_usbmisc_init (struct pinctrl_state*) ; 
 int imx_usbmisc_init_post (struct pinctrl_state*) ; 
 scalar_t__ of_device_is_compatible (struct device_node*,char*) ; 
 struct of_device_id* of_match_device (int /*<<< orphan*/ ,struct device*) ; 
 scalar_t__ of_usb_get_phy_mode (struct device_node*) ; 
 void* pinctrl_lookup_state (struct pinctrl_state*,char*) ; 
 int pinctrl_select_state (struct pinctrl_state*,struct pinctrl_state*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct ci_hdrc_imx_data*) ; 
 int /*<<< orphan*/  pm_qos_add_request (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_qos_remove_request (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_enable (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_set_active (struct device*) ; 
 int /*<<< orphan*/  regulator_disable (struct pinctrl_state*) ; 
 int regulator_enable (struct pinctrl_state*) ; 
 int /*<<< orphan*/  usb_phy_init (struct pinctrl_state*) ; 
 struct pinctrl_state* usbmisc_get_init_data (struct device*) ; 

__attribute__((used)) static int ci_hdrc_imx_probe(struct platform_device *pdev)
{
	struct ci_hdrc_imx_data *data;
	struct ci_hdrc_platform_data pdata = {
		.name		= dev_name(&pdev->dev),
		.capoffset	= DEF_CAPOFFSET,
		.notify_event	= ci_hdrc_imx_notify_event,
	};
	int ret;
	const struct of_device_id *of_id;
	const struct ci_hdrc_imx_platform_flag *imx_platform_flag;
	struct device_node *np = pdev->dev.of_node;
	struct device *dev = &pdev->dev;
	struct pinctrl_state *pinctrl_hsic_idle;

	of_id = of_match_device(ci_hdrc_imx_dt_ids, dev);
	if (!of_id)
		return -ENODEV;

	imx_platform_flag = of_id->data;

	data = devm_kzalloc(&pdev->dev, sizeof(*data), GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	data->plat_data = imx_platform_flag;
	pdata.flags |= imx_platform_flag->flags;
	platform_set_drvdata(pdev, data);
	data->usbmisc_data = usbmisc_get_init_data(dev);
	if (IS_ERR(data->usbmisc_data))
		return PTR_ERR(data->usbmisc_data);

	if ((of_usb_get_phy_mode(dev->of_node) == USBPHY_INTERFACE_MODE_HSIC)
		&& data->usbmisc_data) {
		pdata.flags |= CI_HDRC_IMX_IS_HSIC;
		data->usbmisc_data->hsic = 1;
		data->pinctrl = devm_pinctrl_get(dev);
		if (IS_ERR(data->pinctrl)) {
			dev_err(dev, "pinctrl get failed, err=%ld\n",
					PTR_ERR(data->pinctrl));
			return PTR_ERR(data->pinctrl);
		}

		pinctrl_hsic_idle = pinctrl_lookup_state(data->pinctrl, "idle");
		if (IS_ERR(pinctrl_hsic_idle)) {
			dev_err(dev,
				"pinctrl_hsic_idle lookup failed, err=%ld\n",
					PTR_ERR(pinctrl_hsic_idle));
			return PTR_ERR(pinctrl_hsic_idle);
		}

		ret = pinctrl_select_state(data->pinctrl, pinctrl_hsic_idle);
		if (ret) {
			dev_err(dev, "hsic_idle select failed, err=%d\n", ret);
			return ret;
		}

		data->pinctrl_hsic_active = pinctrl_lookup_state(data->pinctrl,
								"active");
		if (IS_ERR(data->pinctrl_hsic_active)) {
			dev_err(dev,
				"pinctrl_hsic_active lookup failed, err=%ld\n",
					PTR_ERR(data->pinctrl_hsic_active));
			return PTR_ERR(data->pinctrl_hsic_active);
		}

		data->hsic_pad_regulator = devm_regulator_get(dev, "hsic");
		if (PTR_ERR(data->hsic_pad_regulator) == -EPROBE_DEFER) {
			return -EPROBE_DEFER;
		} else if (PTR_ERR(data->hsic_pad_regulator) == -ENODEV) {
			/* no pad regualator is needed */
			data->hsic_pad_regulator = NULL;
		} else if (IS_ERR(data->hsic_pad_regulator)) {
			dev_err(dev, "Get HSIC pad regulator error: %ld\n",
					PTR_ERR(data->hsic_pad_regulator));
			return PTR_ERR(data->hsic_pad_regulator);
		}

		if (data->hsic_pad_regulator) {
			ret = regulator_enable(data->hsic_pad_regulator);
			if (ret) {
				dev_err(dev,
					"Failed to enable HSIC pad regulator\n");
				return ret;
			}
		}
	}

	if (pdata.flags & CI_HDRC_PMQOS)
		pm_qos_add_request(&data->pm_qos_req,
			PM_QOS_CPU_DMA_LATENCY, 0);

	ret = imx_get_clks(dev);
	if (ret)
		goto disable_hsic_regulator;

	ret = imx_prepare_enable_clks(dev);
	if (ret)
		goto disable_hsic_regulator;

	data->phy = devm_usb_get_phy_by_phandle(dev, "fsl,usbphy", 0);
	if (IS_ERR(data->phy)) {
		ret = PTR_ERR(data->phy);
		/* Return -EINVAL if no usbphy is available */
		if (ret == -ENODEV)
			data->phy = NULL;
		else
			goto err_clk;
	}

	pdata.usb_phy = data->phy;

	if ((of_device_is_compatible(np, "fsl,imx53-usb") ||
	     of_device_is_compatible(np, "fsl,imx51-usb")) && pdata.usb_phy &&
	    of_usb_get_phy_mode(np) == USBPHY_INTERFACE_MODE_ULPI) {
		pdata.flags |= CI_HDRC_OVERRIDE_PHY_CONTROL;
		data->override_phy_control = true;
		usb_phy_init(pdata.usb_phy);
	}

	if (pdata.flags & CI_HDRC_SUPPORTS_RUNTIME_PM)
		data->supports_runtime_pm = true;

	ret = imx_usbmisc_init(data->usbmisc_data);
	if (ret) {
		dev_err(dev, "usbmisc init failed, ret=%d\n", ret);
		goto err_clk;
	}

	data->ci_pdev = ci_hdrc_add_device(dev,
				pdev->resource, pdev->num_resources,
				&pdata);
	if (IS_ERR(data->ci_pdev)) {
		ret = PTR_ERR(data->ci_pdev);
		if (ret != -EPROBE_DEFER)
			dev_err(dev, "ci_hdrc_add_device failed, err=%d\n",
					ret);
		goto err_clk;
	}

	ret = imx_usbmisc_init_post(data->usbmisc_data);
	if (ret) {
		dev_err(dev, "usbmisc post failed, ret=%d\n", ret);
		goto disable_device;
	}

	if (data->supports_runtime_pm) {
		pm_runtime_set_active(dev);
		pm_runtime_enable(dev);
	}

	device_set_wakeup_capable(dev, true);

	return 0;

disable_device:
	ci_hdrc_remove_device(data->ci_pdev);
err_clk:
	imx_disable_unprepare_clks(dev);
disable_hsic_regulator:
	if (data->hsic_pad_regulator)
		/* don't overwrite original ret (cf. EPROBE_DEFER) */
		regulator_disable(data->hsic_pad_regulator);
	if (pdata.flags & CI_HDRC_PMQOS)
		pm_qos_remove_request(&data->pm_qos_req);
	data->ci_pdev = NULL;
	return ret;
}