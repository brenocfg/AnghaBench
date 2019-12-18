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
struct sun4i_usb_phy_data {int dr_mode; int id_det; int force_session_end; int /*<<< orphan*/  detect; } ;
struct sun4i_usb_phy {scalar_t__ index; } ;
struct phy {int /*<<< orphan*/  dev; } ;
typedef  enum phy_mode { ____Placeholder_phy_mode } phy_mode ;

/* Variables and functions */
 int EINVAL ; 
#define  PHY_MODE_USB_DEVICE 130 
#define  PHY_MODE_USB_HOST 129 
#define  PHY_MODE_USB_OTG 128 
 int USB_DR_MODE_HOST ; 
 int USB_DR_MODE_OTG ; 
 int USB_DR_MODE_PERIPHERAL ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int) ; 
 struct sun4i_usb_phy* phy_get_drvdata (struct phy*) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  system_wq ; 
 struct sun4i_usb_phy_data* to_sun4i_usb_phy_data (struct sun4i_usb_phy*) ; 

__attribute__((used)) static int sun4i_usb_phy_set_mode(struct phy *_phy,
				  enum phy_mode mode, int submode)
{
	struct sun4i_usb_phy *phy = phy_get_drvdata(_phy);
	struct sun4i_usb_phy_data *data = to_sun4i_usb_phy_data(phy);
	int new_mode;

	if (phy->index != 0) {
		if (mode == PHY_MODE_USB_HOST)
			return 0;
		return -EINVAL;
	}

	switch (mode) {
	case PHY_MODE_USB_HOST:
		new_mode = USB_DR_MODE_HOST;
		break;
	case PHY_MODE_USB_DEVICE:
		new_mode = USB_DR_MODE_PERIPHERAL;
		break;
	case PHY_MODE_USB_OTG:
		new_mode = USB_DR_MODE_OTG;
		break;
	default:
		return -EINVAL;
	}

	if (new_mode != data->dr_mode) {
		dev_info(&_phy->dev, "Changing dr_mode to %d\n", new_mode);
		data->dr_mode = new_mode;
	}

	data->id_det = -1; /* Force reprocessing of id */
	data->force_session_end = true;
	queue_delayed_work(system_wq, &data->detect, 0);

	return 0;
}