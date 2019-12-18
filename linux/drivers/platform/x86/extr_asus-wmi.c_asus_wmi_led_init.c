#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {char* name; int max_brightness; char* default_trigger; int /*<<< orphan*/  brightness_get; int /*<<< orphan*/  brightness_set; int /*<<< orphan*/  flags; } ;
struct asus_wmi {int kbd_led_wk; TYPE_4__ lightbar_led; TYPE_3__* platform_device; int /*<<< orphan*/  lightbar_led_work; TYPE_4__ wlan_led; int /*<<< orphan*/  wlan_led_work; TYPE_2__* driver; TYPE_4__ kbd_led; TYPE_4__ tpd_led; int /*<<< orphan*/  tpd_led_work; int /*<<< orphan*/  led_workqueue; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev; } ;
struct TYPE_6__ {TYPE_1__* quirks; } ;
struct TYPE_5__ {scalar_t__ wapf; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASUS_WMI_DEVID_LIGHTBAR ; 
 int /*<<< orphan*/  ASUS_WMI_DEVID_WIRELESS_LED ; 
 int ENOMEM ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LED_BRIGHT_HW_CHANGED ; 
 int /*<<< orphan*/  LED_CORE_SUSPENDRESUME ; 
 scalar_t__ asus_wmi_dev_is_present (struct asus_wmi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  asus_wmi_led_exit (struct asus_wmi*) ; 
 int /*<<< orphan*/  create_singlethread_workqueue (char*) ; 
 int /*<<< orphan*/  kbd_led_get ; 
 int /*<<< orphan*/  kbd_led_read (struct asus_wmi*,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kbd_led_set ; 
 int led_classdev_register (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  lightbar_led_get ; 
 int /*<<< orphan*/  lightbar_led_set ; 
 int /*<<< orphan*/  lightbar_led_update ; 
 scalar_t__ read_tpd_led_state (struct asus_wmi*) ; 
 int /*<<< orphan*/  tpd_led_get ; 
 int /*<<< orphan*/  tpd_led_set ; 
 int /*<<< orphan*/  tpd_led_update ; 
 int /*<<< orphan*/  wlan_led_get ; 
 int /*<<< orphan*/  wlan_led_set ; 
 int /*<<< orphan*/  wlan_led_unknown_state (struct asus_wmi*) ; 
 int /*<<< orphan*/  wlan_led_update ; 

__attribute__((used)) static int asus_wmi_led_init(struct asus_wmi *asus)
{
	int rv = 0, led_val;

	asus->led_workqueue = create_singlethread_workqueue("led_workqueue");
	if (!asus->led_workqueue)
		return -ENOMEM;

	if (read_tpd_led_state(asus) >= 0) {
		INIT_WORK(&asus->tpd_led_work, tpd_led_update);

		asus->tpd_led.name = "asus::touchpad";
		asus->tpd_led.brightness_set = tpd_led_set;
		asus->tpd_led.brightness_get = tpd_led_get;
		asus->tpd_led.max_brightness = 1;

		rv = led_classdev_register(&asus->platform_device->dev,
					   &asus->tpd_led);
		if (rv)
			goto error;
	}

	if (!kbd_led_read(asus, &led_val, NULL)) {
		asus->kbd_led_wk = led_val;
		asus->kbd_led.name = "asus::kbd_backlight";
		asus->kbd_led.flags = LED_BRIGHT_HW_CHANGED;
		asus->kbd_led.brightness_set = kbd_led_set;
		asus->kbd_led.brightness_get = kbd_led_get;
		asus->kbd_led.max_brightness = 3;

		rv = led_classdev_register(&asus->platform_device->dev,
					   &asus->kbd_led);
		if (rv)
			goto error;
	}

	if (asus_wmi_dev_is_present(asus, ASUS_WMI_DEVID_WIRELESS_LED)
			&& (asus->driver->quirks->wapf > 0)) {
		INIT_WORK(&asus->wlan_led_work, wlan_led_update);

		asus->wlan_led.name = "asus::wlan";
		asus->wlan_led.brightness_set = wlan_led_set;
		if (!wlan_led_unknown_state(asus))
			asus->wlan_led.brightness_get = wlan_led_get;
		asus->wlan_led.flags = LED_CORE_SUSPENDRESUME;
		asus->wlan_led.max_brightness = 1;
		asus->wlan_led.default_trigger = "asus-wlan";

		rv = led_classdev_register(&asus->platform_device->dev,
					   &asus->wlan_led);
		if (rv)
			goto error;
	}

	if (asus_wmi_dev_is_present(asus, ASUS_WMI_DEVID_LIGHTBAR)) {
		INIT_WORK(&asus->lightbar_led_work, lightbar_led_update);

		asus->lightbar_led.name = "asus::lightbar";
		asus->lightbar_led.brightness_set = lightbar_led_set;
		asus->lightbar_led.brightness_get = lightbar_led_get;
		asus->lightbar_led.max_brightness = 1;

		rv = led_classdev_register(&asus->platform_device->dev,
					   &asus->lightbar_led);
	}

error:
	if (rv)
		asus_wmi_led_exit(asus);

	return rv;
}