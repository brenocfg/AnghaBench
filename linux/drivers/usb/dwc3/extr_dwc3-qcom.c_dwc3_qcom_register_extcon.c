#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct extcon_dev {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* notifier_call ) (TYPE_1__*,int,struct extcon_dev*) ;} ;
struct dwc3_qcom {struct extcon_dev* edev; TYPE_1__ vbus_nb; TYPE_1__ host_nb; struct extcon_dev* host_edev; struct device* dev; } ;
struct device {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXTCON_USB ; 
 int /*<<< orphan*/  EXTCON_USB_HOST ; 
 scalar_t__ IS_ERR (struct extcon_dev*) ; 
 int PTR_ERR (struct extcon_dev*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int devm_extcon_register_notifier (struct device*,struct extcon_dev*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  dwc3_qcom_host_notifier (TYPE_1__*,int,struct extcon_dev*) ; 
 int /*<<< orphan*/  dwc3_qcom_vbus_notifier (TYPE_1__*,int,struct extcon_dev*) ; 
 void* extcon_get_edev_by_phandle (struct device*,int) ; 
 scalar_t__ extcon_get_state (struct extcon_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_property_read_bool (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int dwc3_qcom_register_extcon(struct dwc3_qcom *qcom)
{
	struct device		*dev = qcom->dev;
	struct extcon_dev	*host_edev;
	int			ret;

	if (!of_property_read_bool(dev->of_node, "extcon"))
		return 0;

	qcom->edev = extcon_get_edev_by_phandle(dev, 0);
	if (IS_ERR(qcom->edev))
		return PTR_ERR(qcom->edev);

	qcom->vbus_nb.notifier_call = dwc3_qcom_vbus_notifier;

	qcom->host_edev = extcon_get_edev_by_phandle(dev, 1);
	if (IS_ERR(qcom->host_edev))
		qcom->host_edev = NULL;

	ret = devm_extcon_register_notifier(dev, qcom->edev, EXTCON_USB,
					    &qcom->vbus_nb);
	if (ret < 0) {
		dev_err(dev, "VBUS notifier register failed\n");
		return ret;
	}

	if (qcom->host_edev)
		host_edev = qcom->host_edev;
	else
		host_edev = qcom->edev;

	qcom->host_nb.notifier_call = dwc3_qcom_host_notifier;
	ret = devm_extcon_register_notifier(dev, host_edev, EXTCON_USB_HOST,
					    &qcom->host_nb);
	if (ret < 0) {
		dev_err(dev, "Host notifier register failed\n");
		return ret;
	}

	/* Update initial VBUS override based on extcon state */
	if (extcon_get_state(qcom->edev, EXTCON_USB) ||
	    !extcon_get_state(host_edev, EXTCON_USB_HOST))
		dwc3_qcom_vbus_notifier(&qcom->vbus_nb, true, qcom->edev);
	else
		dwc3_qcom_vbus_notifier(&qcom->vbus_nb, false, qcom->edev);

	return 0;
}