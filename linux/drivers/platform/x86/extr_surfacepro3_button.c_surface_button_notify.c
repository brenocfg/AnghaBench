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
typedef  int u32 ;
struct surface_button {scalar_t__ suspended; struct input_dev* input; } ;
struct input_dev {int dummy; } ;
struct acpi_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int KEY_LEFTMETA ; 
 int KEY_POWER ; 
 int KEY_RESERVED ; 
 int KEY_VOLUMEDOWN ; 
 int KEY_VOLUMEUP ; 
#define  SURFACE_BUTTON_NOTIFY_PRESS_HOME 136 
#define  SURFACE_BUTTON_NOTIFY_PRESS_POWER 135 
#define  SURFACE_BUTTON_NOTIFY_PRESS_VOLUME_DOWN 134 
#define  SURFACE_BUTTON_NOTIFY_PRESS_VOLUME_UP 133 
#define  SURFACE_BUTTON_NOTIFY_RELEASE_HOME 132 
#define  SURFACE_BUTTON_NOTIFY_RELEASE_POWER 131 
#define  SURFACE_BUTTON_NOTIFY_RELEASE_VOLUME_DOWN 130 
#define  SURFACE_BUTTON_NOTIFY_RELEASE_VOLUME_UP 129 
#define  SURFACE_BUTTON_NOTIFY_TABLET_MODE 128 
 struct surface_button* acpi_driver_data (struct acpi_device*) ; 
 int /*<<< orphan*/  dev_info_ratelimited (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_warn_once (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  input_report_key (struct input_dev*,int,int) ; 
 int /*<<< orphan*/  input_sync (struct input_dev*) ; 
 int /*<<< orphan*/  pm_wakeup_dev_event (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void surface_button_notify(struct acpi_device *device, u32 event)
{
	struct surface_button *button = acpi_driver_data(device);
	struct input_dev *input;
	int key_code = KEY_RESERVED;
	bool pressed = false;

	switch (event) {
	/* Power button press,release handle */
	case SURFACE_BUTTON_NOTIFY_PRESS_POWER:
		pressed = true;
		/*fall through*/
	case SURFACE_BUTTON_NOTIFY_RELEASE_POWER:
		key_code = KEY_POWER;
		break;
	/* Home button press,release handle */
	case SURFACE_BUTTON_NOTIFY_PRESS_HOME:
		pressed = true;
		/*fall through*/
	case SURFACE_BUTTON_NOTIFY_RELEASE_HOME:
		key_code = KEY_LEFTMETA;
		break;
	/* Volume up button press,release handle */
	case SURFACE_BUTTON_NOTIFY_PRESS_VOLUME_UP:
		pressed = true;
		/*fall through*/
	case SURFACE_BUTTON_NOTIFY_RELEASE_VOLUME_UP:
		key_code = KEY_VOLUMEUP;
		break;
	/* Volume down button press,release handle */
	case SURFACE_BUTTON_NOTIFY_PRESS_VOLUME_DOWN:
		pressed = true;
		/*fall through*/
	case SURFACE_BUTTON_NOTIFY_RELEASE_VOLUME_DOWN:
		key_code = KEY_VOLUMEDOWN;
		break;
	case SURFACE_BUTTON_NOTIFY_TABLET_MODE:
		dev_warn_once(&device->dev, "Tablet mode is not supported\n");
		break;
	default:
		dev_info_ratelimited(&device->dev,
				     "Unsupported event [0x%x]\n", event);
		break;
	}
	input = button->input;
	if (key_code == KEY_RESERVED)
		return;
	if (pressed)
		pm_wakeup_dev_event(&device->dev, 0, button->suspended);
	if (button->suspended)
		return;
	input_report_key(input, key_code, pressed?1:0);
	input_sync(input);
}