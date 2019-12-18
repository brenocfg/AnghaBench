#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ notifier_call; } ;
struct usb_phy {TYPE_3__ type_nb; TYPE_1__* dev; TYPE_3__ id_nb; struct extcon_dev* edev; struct extcon_dev* id_edev; TYPE_3__ vbus_nb; } ;
struct extcon_dev {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXTCON_CHG_USB_ACA ; 
 int /*<<< orphan*/  EXTCON_CHG_USB_CDP ; 
 int /*<<< orphan*/  EXTCON_CHG_USB_DCP ; 
 int /*<<< orphan*/  EXTCON_CHG_USB_SDP ; 
 int /*<<< orphan*/  EXTCON_USB ; 
 int /*<<< orphan*/  EXTCON_USB_HOST ; 
 scalar_t__ IS_ERR (struct extcon_dev*) ; 
 int PTR_ERR (struct extcon_dev*) ; 
 int /*<<< orphan*/  __usb_phy_get_charger_type (struct usb_phy*) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  dev_info (TYPE_1__*,char*) ; 
 int devm_extcon_register_notifier (TYPE_1__*,struct extcon_dev*,int /*<<< orphan*/ ,TYPE_3__*) ; 
 void* extcon_get_edev_by_phandle (TYPE_1__*,int) ; 
 scalar_t__ of_property_read_bool (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ usb_phy_get_charger_type ; 

__attribute__((used)) static int usb_add_extcon(struct usb_phy *x)
{
	int ret;

	if (of_property_read_bool(x->dev->of_node, "extcon")) {
		x->edev = extcon_get_edev_by_phandle(x->dev, 0);
		if (IS_ERR(x->edev))
			return PTR_ERR(x->edev);

		x->id_edev = extcon_get_edev_by_phandle(x->dev, 1);
		if (IS_ERR(x->id_edev)) {
			x->id_edev = NULL;
			dev_info(x->dev, "No separate ID extcon device\n");
		}

		if (x->vbus_nb.notifier_call) {
			ret = devm_extcon_register_notifier(x->dev, x->edev,
							    EXTCON_USB,
							    &x->vbus_nb);
			if (ret < 0) {
				dev_err(x->dev,
					"register VBUS notifier failed\n");
				return ret;
			}
		} else {
			x->type_nb.notifier_call = usb_phy_get_charger_type;

			ret = devm_extcon_register_notifier(x->dev, x->edev,
							    EXTCON_CHG_USB_SDP,
							    &x->type_nb);
			if (ret) {
				dev_err(x->dev,
					"register extcon USB SDP failed.\n");
				return ret;
			}

			ret = devm_extcon_register_notifier(x->dev, x->edev,
							    EXTCON_CHG_USB_CDP,
							    &x->type_nb);
			if (ret) {
				dev_err(x->dev,
					"register extcon USB CDP failed.\n");
				return ret;
			}

			ret = devm_extcon_register_notifier(x->dev, x->edev,
							    EXTCON_CHG_USB_DCP,
							    &x->type_nb);
			if (ret) {
				dev_err(x->dev,
					"register extcon USB DCP failed.\n");
				return ret;
			}

			ret = devm_extcon_register_notifier(x->dev, x->edev,
							    EXTCON_CHG_USB_ACA,
							    &x->type_nb);
			if (ret) {
				dev_err(x->dev,
					"register extcon USB ACA failed.\n");
				return ret;
			}
		}

		if (x->id_nb.notifier_call) {
			struct extcon_dev *id_ext;

			if (x->id_edev)
				id_ext = x->id_edev;
			else
				id_ext = x->edev;

			ret = devm_extcon_register_notifier(x->dev, id_ext,
							    EXTCON_USB_HOST,
							    &x->id_nb);
			if (ret < 0) {
				dev_err(x->dev,
					"register ID notifier failed\n");
				return ret;
			}
		}
	}

	if (x->type_nb.notifier_call)
		__usb_phy_get_charger_type(x);

	return 0;
}