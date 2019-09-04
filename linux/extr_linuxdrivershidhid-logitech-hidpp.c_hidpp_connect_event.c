#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct input_dev {int dummy; } ;
struct TYPE_2__ {int online; scalar_t__ ps; int /*<<< orphan*/  level; int /*<<< orphan*/  status; } ;
struct hidpp_device {int quirks; int protocol_major; char* name; int capabilities; struct input_dev* delayed_input; TYPE_1__ battery; int /*<<< orphan*/  protocol_minor; int /*<<< orphan*/  connected; struct hid_device* hid_dev; } ;
struct hid_device {char* name; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HIDPP_CAPABILITY_BATTERY_MILEAGE ; 
 int HIDPP_CAPABILITY_HIDPP10_BATTERY ; 
 int HIDPP_CAPABILITY_HIDPP20_BATTERY ; 
 int HIDPP_QUIRK_CLASS_K400 ; 
 int HIDPP_QUIRK_CLASS_M560 ; 
 int HIDPP_QUIRK_CLASS_WTP ; 
 int HIDPP_QUIRK_NO_HIDINPUT ; 
 int /*<<< orphan*/  POWER_SUPPLY_CAPACITY_LEVEL_UNKNOWN ; 
 int /*<<< orphan*/  POWER_SUPPLY_STATUS_UNKNOWN ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 char* devm_kasprintf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  hid_err (struct hid_device*,char*,...) ; 
 int /*<<< orphan*/  hid_info (struct hid_device*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hidpp10_enable_battery_reporting (struct hidpp_device*) ; 
 int /*<<< orphan*/  hidpp10_query_battery_mileage (struct hidpp_device*) ; 
 int /*<<< orphan*/  hidpp10_query_battery_status (struct hidpp_device*) ; 
 int /*<<< orphan*/  hidpp20_query_battery_info (struct hidpp_device*) ; 
 struct input_dev* hidpp_allocate_input (struct hid_device*) ; 
 char* hidpp_get_device_name (struct hidpp_device*) ; 
 int /*<<< orphan*/  hidpp_initialize_battery (struct hidpp_device*) ; 
 int /*<<< orphan*/  hidpp_is_connected (struct hidpp_device*) ; 
 int /*<<< orphan*/  hidpp_populate_input (struct hidpp_device*,struct input_dev*,int) ; 
 int /*<<< orphan*/  input_free_device (struct input_dev*) ; 
 int input_register_device (struct input_dev*) ; 
 int k400_connect (struct hid_device*,int) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 int m560_send_config_command (struct hid_device*,int) ; 
 int /*<<< orphan*/  power_supply_changed (scalar_t__) ; 
 int wtp_connect (struct hid_device*,int) ; 

__attribute__((used)) static void hidpp_connect_event(struct hidpp_device *hidpp)
{
	struct hid_device *hdev = hidpp->hid_dev;
	int ret = 0;
	bool connected = atomic_read(&hidpp->connected);
	struct input_dev *input;
	char *name, *devm_name;

	if (!connected) {
		if (hidpp->battery.ps) {
			hidpp->battery.online = false;
			hidpp->battery.status = POWER_SUPPLY_STATUS_UNKNOWN;
			hidpp->battery.level = POWER_SUPPLY_CAPACITY_LEVEL_UNKNOWN;
			power_supply_changed(hidpp->battery.ps);
		}
		return;
	}

	if (hidpp->quirks & HIDPP_QUIRK_CLASS_WTP) {
		ret = wtp_connect(hdev, connected);
		if (ret)
			return;
	} else if (hidpp->quirks & HIDPP_QUIRK_CLASS_M560) {
		ret = m560_send_config_command(hdev, connected);
		if (ret)
			return;
	} else if (hidpp->quirks & HIDPP_QUIRK_CLASS_K400) {
		ret = k400_connect(hdev, connected);
		if (ret)
			return;
	}

	/* the device is already connected, we can ask for its name and
	 * protocol */
	if (!hidpp->protocol_major) {
		ret = !hidpp_is_connected(hidpp);
		if (ret) {
			hid_err(hdev, "Can not get the protocol version.\n");
			return;
		}
		hid_info(hdev, "HID++ %u.%u device connected.\n",
			 hidpp->protocol_major, hidpp->protocol_minor);
	}

	if (hidpp->name == hdev->name && hidpp->protocol_major >= 2) {
		name = hidpp_get_device_name(hidpp);
		if (!name) {
			hid_err(hdev,
				"unable to retrieve the name of the device");
			return;
		}

		devm_name = devm_kasprintf(&hdev->dev, GFP_KERNEL, "%s", name);
		kfree(name);
		if (!devm_name)
			return;

		hidpp->name = devm_name;
	}

	hidpp_initialize_battery(hidpp);

	/* forward current battery state */
	if (hidpp->capabilities & HIDPP_CAPABILITY_HIDPP10_BATTERY) {
		hidpp10_enable_battery_reporting(hidpp);
		if (hidpp->capabilities & HIDPP_CAPABILITY_BATTERY_MILEAGE)
			hidpp10_query_battery_mileage(hidpp);
		else
			hidpp10_query_battery_status(hidpp);
	} else if (hidpp->capabilities & HIDPP_CAPABILITY_HIDPP20_BATTERY) {
		hidpp20_query_battery_info(hidpp);
	}
	if (hidpp->battery.ps)
		power_supply_changed(hidpp->battery.ps);

	if (!(hidpp->quirks & HIDPP_QUIRK_NO_HIDINPUT) || hidpp->delayed_input)
		/* if the input nodes are already created, we can stop now */
		return;

	input = hidpp_allocate_input(hdev);
	if (!input) {
		hid_err(hdev, "cannot allocate new input device: %d\n", ret);
		return;
	}

	hidpp_populate_input(hidpp, input, false);

	ret = input_register_device(input);
	if (ret)
		input_free_device(input);

	hidpp->delayed_input = input;
}