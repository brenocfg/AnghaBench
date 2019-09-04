#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct device {struct device_node* of_node; int /*<<< orphan*/  parent; } ;
struct platform_device {int id; struct device dev; } ;
struct device_node {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  notifier_call; } ;
struct cros_ec_extcon_info {int port_id; int pr; TYPE_1__ notifier; struct cros_ec_device* ec; int /*<<< orphan*/  dr; int /*<<< orphan*/  edev; struct device* dev; } ;
struct cros_ec_device {int /*<<< orphan*/  event_notifier; } ;

/* Variables and functions */
 int /*<<< orphan*/  DR_NONE ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  EXTCON_DISP_DP ; 
 int /*<<< orphan*/  EXTCON_PROP_DISP_HPD ; 
 int /*<<< orphan*/  EXTCON_PROP_USB_SS ; 
 int /*<<< orphan*/  EXTCON_PROP_USB_TYPEC_POLARITY ; 
 int /*<<< orphan*/  EXTCON_PROP_USB_VBUS ; 
 int /*<<< orphan*/  EXTCON_USB ; 
 int /*<<< orphan*/  EXTCON_USB_HOST ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int blocking_notifier_chain_register (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  blocking_notifier_chain_unregister (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int cros_ec_pd_get_num_ports (struct cros_ec_extcon_info*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 struct cros_ec_device* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_extcon_dev_allocate (struct device*,int /*<<< orphan*/ ) ; 
 int devm_extcon_dev_register (struct device*,int /*<<< orphan*/ ) ; 
 struct cros_ec_extcon_info* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int extcon_cros_ec_detect_cable (struct cros_ec_extcon_info*,int) ; 
 int /*<<< orphan*/  extcon_cros_ec_event ; 
 int /*<<< orphan*/  extcon_set_property_capability (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int of_property_read_u32 (struct device_node*,char*,int*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct cros_ec_extcon_info*) ; 
 int /*<<< orphan*/  usb_type_c_cable ; 

__attribute__((used)) static int extcon_cros_ec_probe(struct platform_device *pdev)
{
	struct cros_ec_extcon_info *info;
	struct cros_ec_device *ec = dev_get_drvdata(pdev->dev.parent);
	struct device *dev = &pdev->dev;
	struct device_node *np = dev->of_node;
	int numports, ret;

	info = devm_kzalloc(dev, sizeof(*info), GFP_KERNEL);
	if (!info)
		return -ENOMEM;

	info->dev = dev;
	info->ec = ec;

	if (np) {
		u32 port;

		ret = of_property_read_u32(np, "google,usb-port-id", &port);
		if (ret < 0) {
			dev_err(dev, "Missing google,usb-port-id property\n");
			return ret;
		}
		info->port_id = port;
	} else {
		info->port_id = pdev->id;
	}

	numports = cros_ec_pd_get_num_ports(info);
	if (numports < 0) {
		dev_err(dev, "failed getting number of ports! ret = %d\n",
			numports);
		return numports;
	}

	if (info->port_id >= numports) {
		dev_err(dev, "This system only supports %d ports\n", numports);
		return -ENODEV;
	}

	info->edev = devm_extcon_dev_allocate(dev, usb_type_c_cable);
	if (IS_ERR(info->edev)) {
		dev_err(dev, "failed to allocate extcon device\n");
		return -ENOMEM;
	}

	ret = devm_extcon_dev_register(dev, info->edev);
	if (ret < 0) {
		dev_err(dev, "failed to register extcon device\n");
		return ret;
	}

	extcon_set_property_capability(info->edev, EXTCON_USB,
				       EXTCON_PROP_USB_VBUS);
	extcon_set_property_capability(info->edev, EXTCON_USB_HOST,
				       EXTCON_PROP_USB_VBUS);
	extcon_set_property_capability(info->edev, EXTCON_USB,
				       EXTCON_PROP_USB_TYPEC_POLARITY);
	extcon_set_property_capability(info->edev, EXTCON_USB_HOST,
				       EXTCON_PROP_USB_TYPEC_POLARITY);
	extcon_set_property_capability(info->edev, EXTCON_DISP_DP,
				       EXTCON_PROP_USB_TYPEC_POLARITY);
	extcon_set_property_capability(info->edev, EXTCON_USB,
				       EXTCON_PROP_USB_SS);
	extcon_set_property_capability(info->edev, EXTCON_USB_HOST,
				       EXTCON_PROP_USB_SS);
	extcon_set_property_capability(info->edev, EXTCON_DISP_DP,
				       EXTCON_PROP_USB_SS);
	extcon_set_property_capability(info->edev, EXTCON_DISP_DP,
				       EXTCON_PROP_DISP_HPD);

	info->dr = DR_NONE;
	info->pr = false;

	platform_set_drvdata(pdev, info);

	/* Get PD events from the EC */
	info->notifier.notifier_call = extcon_cros_ec_event;
	ret = blocking_notifier_chain_register(&info->ec->event_notifier,
					       &info->notifier);
	if (ret < 0) {
		dev_err(dev, "failed to register notifier\n");
		return ret;
	}

	/* Perform initial detection */
	ret = extcon_cros_ec_detect_cable(info, true);
	if (ret < 0) {
		dev_err(dev, "failed to detect initial cable state\n");
		goto unregister_notifier;
	}

	return 0;

unregister_notifier:
	blocking_notifier_chain_unregister(&info->ec->event_notifier,
					   &info->notifier);
	return ret;
}