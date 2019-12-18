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
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct pinctrl_state {int dummy; } ;
typedef  struct pinctrl_state extcon_dev ;
struct device {int /*<<< orphan*/  fwnode; int /*<<< orphan*/  of_node; } ;
struct TYPE_4__ {void* notifier_call; } ;
struct ci_hdrc_cable {int connected; struct pinctrl_state* edev; TYPE_1__ nb; } ;
struct TYPE_5__ {int otg_rev; int hnp_support; int srp_support; } ;
struct ci_hdrc_platform_data {scalar_t__ dr_mode; int phy_clkgate_delay_us; int itc_setting; int ahb_burst_config; int tx_burst_size; int rx_burst_size; struct pinctrl_state* pins_device; struct pinctrl_state* pctl; struct pinctrl_state* pins_host; struct pinctrl_state* pins_default; struct ci_hdrc_cable id_extcon; struct ci_hdrc_cable vbus_extcon; int /*<<< orphan*/  flags; TYPE_2__ ci_otg_caps; scalar_t__ tpl_support; struct pinctrl_state* reg_vbus; scalar_t__ phy_mode; } ;
struct TYPE_6__ {int /*<<< orphan*/  fwnode; } ;

/* Variables and functions */
 int /*<<< orphan*/  CI_HDRC_FORCE_FULLSPEED ; 
 int /*<<< orphan*/  CI_HDRC_OVERRIDE_AHB_BURST ; 
 int /*<<< orphan*/  CI_HDRC_OVERRIDE_RX_BURST ; 
 int /*<<< orphan*/  CI_HDRC_OVERRIDE_TX_BURST ; 
 int /*<<< orphan*/  CI_HDRC_SET_NON_ZERO_TTHA ; 
 int EINVAL ; 
 int ENODEV ; 
 int EPROBE_DEFER ; 
 struct pinctrl_state* ERR_PTR (int) ; 
 int /*<<< orphan*/  EXTCON_USB ; 
 int /*<<< orphan*/  EXTCON_USB_HOST ; 
 scalar_t__ IS_ERR (struct pinctrl_state*) ; 
 int PTR_ERR (struct pinctrl_state*) ; 
 scalar_t__ USB_DR_MODE_OTG ; 
 scalar_t__ USB_DR_MODE_PERIPHERAL ; 
 scalar_t__ USB_DR_MODE_UNKNOWN ; 
 scalar_t__ USB_SPEED_FULL ; 
 void* ci_cable_notifier ; 
 TYPE_3__ ci_role_switch ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 scalar_t__ device_property_read_bool (struct device*,char*) ; 
 struct pinctrl_state* devm_pinctrl_get (struct device*) ; 
 struct pinctrl_state* devm_regulator_get (struct device*,char*) ; 
 struct pinctrl_state* extcon_get_edev_by_phandle (struct device*,int) ; 
 int extcon_get_state (struct pinctrl_state*,int /*<<< orphan*/ ) ; 
 scalar_t__ of_find_property (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ of_property_read_bool (int /*<<< orphan*/ ,char*) ; 
 int of_property_read_u32 (int /*<<< orphan*/ ,char*,int*) ; 
 scalar_t__ of_usb_get_phy_mode (int /*<<< orphan*/ ) ; 
 scalar_t__ of_usb_host_tpl_support (int /*<<< orphan*/ ) ; 
 int of_usb_update_otg_caps (int /*<<< orphan*/ ,TYPE_2__*) ; 
 struct pinctrl_state* pinctrl_lookup_state (struct pinctrl_state*,char*) ; 
 scalar_t__ usb_get_dr_mode (struct device*) ; 
 scalar_t__ usb_get_maximum_speed (struct device*) ; 

__attribute__((used)) static int ci_get_platdata(struct device *dev,
		struct ci_hdrc_platform_data *platdata)
{
	struct extcon_dev *ext_vbus, *ext_id;
	struct ci_hdrc_cable *cable;
	int ret;

	if (!platdata->phy_mode)
		platdata->phy_mode = of_usb_get_phy_mode(dev->of_node);

	if (!platdata->dr_mode)
		platdata->dr_mode = usb_get_dr_mode(dev);

	if (platdata->dr_mode == USB_DR_MODE_UNKNOWN)
		platdata->dr_mode = USB_DR_MODE_OTG;

	if (platdata->dr_mode != USB_DR_MODE_PERIPHERAL) {
		/* Get the vbus regulator */
		platdata->reg_vbus = devm_regulator_get(dev, "vbus");
		if (PTR_ERR(platdata->reg_vbus) == -EPROBE_DEFER) {
			return -EPROBE_DEFER;
		} else if (PTR_ERR(platdata->reg_vbus) == -ENODEV) {
			/* no vbus regulator is needed */
			platdata->reg_vbus = NULL;
		} else if (IS_ERR(platdata->reg_vbus)) {
			dev_err(dev, "Getting regulator error: %ld\n",
				PTR_ERR(platdata->reg_vbus));
			return PTR_ERR(platdata->reg_vbus);
		}
		/* Get TPL support */
		if (!platdata->tpl_support)
			platdata->tpl_support =
				of_usb_host_tpl_support(dev->of_node);
	}

	if (platdata->dr_mode == USB_DR_MODE_OTG) {
		/* We can support HNP and SRP of OTG 2.0 */
		platdata->ci_otg_caps.otg_rev = 0x0200;
		platdata->ci_otg_caps.hnp_support = true;
		platdata->ci_otg_caps.srp_support = true;

		/* Update otg capabilities by DT properties */
		ret = of_usb_update_otg_caps(dev->of_node,
					&platdata->ci_otg_caps);
		if (ret)
			return ret;
	}

	if (usb_get_maximum_speed(dev) == USB_SPEED_FULL)
		platdata->flags |= CI_HDRC_FORCE_FULLSPEED;

	of_property_read_u32(dev->of_node, "phy-clkgate-delay-us",
				     &platdata->phy_clkgate_delay_us);

	platdata->itc_setting = 1;

	of_property_read_u32(dev->of_node, "itc-setting",
					&platdata->itc_setting);

	ret = of_property_read_u32(dev->of_node, "ahb-burst-config",
				&platdata->ahb_burst_config);
	if (!ret) {
		platdata->flags |= CI_HDRC_OVERRIDE_AHB_BURST;
	} else if (ret != -EINVAL) {
		dev_err(dev, "failed to get ahb-burst-config\n");
		return ret;
	}

	ret = of_property_read_u32(dev->of_node, "tx-burst-size-dword",
				&platdata->tx_burst_size);
	if (!ret) {
		platdata->flags |= CI_HDRC_OVERRIDE_TX_BURST;
	} else if (ret != -EINVAL) {
		dev_err(dev, "failed to get tx-burst-size-dword\n");
		return ret;
	}

	ret = of_property_read_u32(dev->of_node, "rx-burst-size-dword",
				&platdata->rx_burst_size);
	if (!ret) {
		platdata->flags |= CI_HDRC_OVERRIDE_RX_BURST;
	} else if (ret != -EINVAL) {
		dev_err(dev, "failed to get rx-burst-size-dword\n");
		return ret;
	}

	if (of_find_property(dev->of_node, "non-zero-ttctrl-ttha", NULL))
		platdata->flags |= CI_HDRC_SET_NON_ZERO_TTHA;

	ext_id = ERR_PTR(-ENODEV);
	ext_vbus = ERR_PTR(-ENODEV);
	if (of_property_read_bool(dev->of_node, "extcon")) {
		/* Each one of them is not mandatory */
		ext_vbus = extcon_get_edev_by_phandle(dev, 0);
		if (IS_ERR(ext_vbus) && PTR_ERR(ext_vbus) != -ENODEV)
			return PTR_ERR(ext_vbus);

		ext_id = extcon_get_edev_by_phandle(dev, 1);
		if (IS_ERR(ext_id) && PTR_ERR(ext_id) != -ENODEV)
			return PTR_ERR(ext_id);
	}

	cable = &platdata->vbus_extcon;
	cable->nb.notifier_call = ci_cable_notifier;
	cable->edev = ext_vbus;

	if (!IS_ERR(ext_vbus)) {
		ret = extcon_get_state(cable->edev, EXTCON_USB);
		if (ret)
			cable->connected = true;
		else
			cable->connected = false;
	}

	cable = &platdata->id_extcon;
	cable->nb.notifier_call = ci_cable_notifier;
	cable->edev = ext_id;

	if (!IS_ERR(ext_id)) {
		ret = extcon_get_state(cable->edev, EXTCON_USB_HOST);
		if (ret)
			cable->connected = true;
		else
			cable->connected = false;
	}

	if (device_property_read_bool(dev, "usb-role-switch"))
		ci_role_switch.fwnode = dev->fwnode;

	platdata->pctl = devm_pinctrl_get(dev);
	if (!IS_ERR(platdata->pctl)) {
		struct pinctrl_state *p;

		p = pinctrl_lookup_state(platdata->pctl, "default");
		if (!IS_ERR(p))
			platdata->pins_default = p;

		p = pinctrl_lookup_state(platdata->pctl, "host");
		if (!IS_ERR(p))
			platdata->pins_host = p;

		p = pinctrl_lookup_state(platdata->pctl, "device");
		if (!IS_ERR(p))
			platdata->pins_device = p;
	}

	return 0;
}