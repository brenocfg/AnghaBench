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
struct max77693_muic_info {int /*<<< orphan*/  edev; int /*<<< orphan*/  dev; int /*<<< orphan*/  path_usb; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int EXTCON_CHG_USB_SDP ; 
 unsigned int EXTCON_DISP_MHL ; 
 unsigned int EXTCON_DOCK ; 
 unsigned int EXTCON_USB ; 
 int /*<<< orphan*/  MAX77693_CABLE_GROUP_VBVOLT ; 
 int /*<<< orphan*/  MAX77693_CONTROL1_SW_AUDIO ; 
#define  MAX77693_MUIC_ADC_AUDIO_MODE_REMOTE 130 
#define  MAX77693_MUIC_ADC_AV_CABLE_NOLOAD 129 
#define  MAX77693_MUIC_ADC_RESERVED_ACC_3 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,char*,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  extcon_set_state_sync (int /*<<< orphan*/ ,unsigned int,int) ; 
 int max77693_muic_get_cable_type (struct max77693_muic_info*,int /*<<< orphan*/ ,int*) ; 
 int max77693_muic_set_path (struct max77693_muic_info*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int max77693_muic_dock_handler(struct max77693_muic_info *info,
		int cable_type, bool attached)
{
	int ret = 0;
	int vbvolt;
	bool cable_attached;
	unsigned int dock_id;

	dev_info(info->dev,
		"external connector is %s (adc:0x%02x)\n",
		attached ? "attached" : "detached", cable_type);

	switch (cable_type) {
	case MAX77693_MUIC_ADC_RESERVED_ACC_3:		/* Dock-Smart */
		/*
		 * Check power cable whether attached or detached state.
		 * The Dock-Smart device need surely external power supply.
		 * If power cable(USB/TA) isn't connected to Dock device,
		 * user can't use Dock-Smart for desktop mode.
		 */
		vbvolt = max77693_muic_get_cable_type(info,
				MAX77693_CABLE_GROUP_VBVOLT, &cable_attached);
		if (attached && !vbvolt) {
			dev_warn(info->dev,
				"Cannot detect external power supply\n");
			return 0;
		}

		/*
		 * Notify Dock/MHL state.
		 * - Dock device include three type of cable which
		 * are HDMI, USB for mouse/keyboard and micro-usb port
		 * for USB/TA cable. Dock device need always exteranl
		 * power supply(USB/TA cable through micro-usb cable). Dock
		 * device support screen output of target to separate
		 * monitor and mouse/keyboard for desktop mode.
		 *
		 * Features of 'USB/TA cable with Dock device'
		 * - Support MHL
		 * - Support external output feature of audio
		 * - Support charging through micro-usb port without data
		 *	     connection if TA cable is connected to target.
		 * - Support charging and data connection through micro-usb port
		 *           if USB cable is connected between target and host
		 *	     device.
		 * - Support OTG(On-The-Go) device (Ex: Mouse/Keyboard)
		 */
		ret = max77693_muic_set_path(info, info->path_usb, attached);
		if (ret < 0)
			return ret;

		extcon_set_state_sync(info->edev, EXTCON_DOCK, attached);
		extcon_set_state_sync(info->edev, EXTCON_DISP_MHL, attached);
		goto out;
	case MAX77693_MUIC_ADC_AUDIO_MODE_REMOTE:	/* Dock-Desk */
		dock_id = EXTCON_DOCK;
		break;
	case MAX77693_MUIC_ADC_AV_CABLE_NOLOAD:		/* Dock-Audio */
		dock_id = EXTCON_DOCK;
		if (!attached) {
			extcon_set_state_sync(info->edev, EXTCON_USB, false);
			extcon_set_state_sync(info->edev, EXTCON_CHG_USB_SDP,
						false);
		}
		break;
	default:
		dev_err(info->dev, "failed to detect %s dock device\n",
			attached ? "attached" : "detached");
		return -EINVAL;
	}

	/* Dock-Car/Desk/Audio, PATH:AUDIO */
	ret = max77693_muic_set_path(info, MAX77693_CONTROL1_SW_AUDIO,
					attached);
	if (ret < 0)
		return ret;
	extcon_set_state_sync(info->edev, dock_id, attached);

out:
	return 0;
}