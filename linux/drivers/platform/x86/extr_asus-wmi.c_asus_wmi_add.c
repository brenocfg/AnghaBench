#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct platform_driver {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  driver; } ;
struct platform_device {TYPE_1__ dev; } ;
struct asus_wmi_driver {int wlan_ctrl_by_user; int /*<<< orphan*/  event_guid; TYPE_2__* quirks; int /*<<< orphan*/  (* detect_quirks ) (struct asus_wmi_driver*) ;struct platform_device* platform_device; } ;
struct asus_wmi {int fnlock_locked; struct platform_device* platform_device; struct asus_wmi_driver* driver; } ;
typedef  int /*<<< orphan*/  acpi_status ;
struct TYPE_4__ {scalar_t__ wmi_backlight_set_devstate; scalar_t__ xusb2pr; scalar_t__ wmi_backlight_native; scalar_t__ wmi_backlight_power; scalar_t__ wmi_force_als_set; } ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ASUS_WMI_DEVID_BACKLIGHT ; 
 int /*<<< orphan*/  ASUS_WMI_DEVID_WLAN ; 
 int ASUS_WMI_DSTS_PRESENCE_BIT ; 
 int ASUS_WMI_DSTS_USER_BIT ; 
 int /*<<< orphan*/  DMI_CHASSIS_TYPE ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ acpi_backlight_native ; 
 scalar_t__ acpi_backlight_vendor ; 
 scalar_t__ acpi_video_get_backlight_type () ; 
 int /*<<< orphan*/  acpi_video_set_dmi_backlight_type (scalar_t__) ; 
 scalar_t__ ashs_present () ; 
 int /*<<< orphan*/  asus_wmi_backlight_exit (struct asus_wmi*) ; 
 int asus_wmi_backlight_init (struct asus_wmi*) ; 
 int /*<<< orphan*/  asus_wmi_battery_init (struct asus_wmi*) ; 
 int /*<<< orphan*/  asus_wmi_debugfs_init (struct asus_wmi*) ; 
 int asus_wmi_fan_init (struct asus_wmi*) ; 
 int /*<<< orphan*/  asus_wmi_fnlock_update (struct asus_wmi*) ; 
 int /*<<< orphan*/  asus_wmi_get_devstate (struct asus_wmi*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ asus_wmi_has_fnlock_key (struct asus_wmi*) ; 
 int asus_wmi_hwmon_init (struct asus_wmi*) ; 
 int /*<<< orphan*/  asus_wmi_input_exit (struct asus_wmi*) ; 
 int asus_wmi_input_init (struct asus_wmi*) ; 
 int /*<<< orphan*/  asus_wmi_led_exit (struct asus_wmi*) ; 
 int asus_wmi_led_init (struct asus_wmi*) ; 
 int /*<<< orphan*/  asus_wmi_notify ; 
 int asus_wmi_platform_init (struct asus_wmi*) ; 
 int /*<<< orphan*/  asus_wmi_rfkill_exit (struct asus_wmi*) ; 
 int asus_wmi_rfkill_init (struct asus_wmi*) ; 
 int /*<<< orphan*/  asus_wmi_set_als () ; 
 int asus_wmi_set_devstate (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  asus_wmi_set_xusb2pr (struct asus_wmi*) ; 
 int /*<<< orphan*/  asus_wmi_sysfs_exit (struct platform_device*) ; 
 int asus_wmi_sysfs_init (struct platform_device*) ; 
 char* dmi_get_system_info (int /*<<< orphan*/ ) ; 
 int fan_boost_mode_check_present (struct asus_wmi*) ; 
 int /*<<< orphan*/  kfree (struct asus_wmi*) ; 
 struct asus_wmi* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct asus_wmi*) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  stub1 (struct asus_wmi_driver*) ; 
 struct asus_wmi_driver* to_asus_wmi_driver (struct platform_driver*) ; 
 struct platform_driver* to_platform_driver (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmi_install_notify_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct asus_wmi*) ; 

__attribute__((used)) static int asus_wmi_add(struct platform_device *pdev)
{
	struct platform_driver *pdrv = to_platform_driver(pdev->dev.driver);
	struct asus_wmi_driver *wdrv = to_asus_wmi_driver(pdrv);
	struct asus_wmi *asus;
	const char *chassis_type;
	acpi_status status;
	int err;
	u32 result;

	asus = kzalloc(sizeof(struct asus_wmi), GFP_KERNEL);
	if (!asus)
		return -ENOMEM;

	asus->driver = wdrv;
	asus->platform_device = pdev;
	wdrv->platform_device = pdev;
	platform_set_drvdata(asus->platform_device, asus);

	if (wdrv->detect_quirks)
		wdrv->detect_quirks(asus->driver);

	err = asus_wmi_platform_init(asus);
	if (err)
		goto fail_platform;

	err = fan_boost_mode_check_present(asus);
	if (err)
		goto fail_fan_boost_mode;

	err = asus_wmi_sysfs_init(asus->platform_device);
	if (err)
		goto fail_sysfs;

	err = asus_wmi_input_init(asus);
	if (err)
		goto fail_input;

	err = asus_wmi_fan_init(asus); /* probably no problems on error */

	err = asus_wmi_hwmon_init(asus);
	if (err)
		goto fail_hwmon;

	err = asus_wmi_led_init(asus);
	if (err)
		goto fail_leds;

	asus_wmi_get_devstate(asus, ASUS_WMI_DEVID_WLAN, &result);
	if (result & (ASUS_WMI_DSTS_PRESENCE_BIT | ASUS_WMI_DSTS_USER_BIT))
		asus->driver->wlan_ctrl_by_user = 1;

	if (!(asus->driver->wlan_ctrl_by_user && ashs_present())) {
		err = asus_wmi_rfkill_init(asus);
		if (err)
			goto fail_rfkill;
	}

	if (asus->driver->quirks->wmi_force_als_set)
		asus_wmi_set_als();

	/* Some Asus desktop boards export an acpi-video backlight interface,
	   stop this from showing up */
	chassis_type = dmi_get_system_info(DMI_CHASSIS_TYPE);
	if (chassis_type && !strcmp(chassis_type, "3"))
		acpi_video_set_dmi_backlight_type(acpi_backlight_vendor);

	if (asus->driver->quirks->wmi_backlight_power)
		acpi_video_set_dmi_backlight_type(acpi_backlight_vendor);

	if (asus->driver->quirks->wmi_backlight_native)
		acpi_video_set_dmi_backlight_type(acpi_backlight_native);

	if (asus->driver->quirks->xusb2pr)
		asus_wmi_set_xusb2pr(asus);

	if (acpi_video_get_backlight_type() == acpi_backlight_vendor) {
		err = asus_wmi_backlight_init(asus);
		if (err && err != -ENODEV)
			goto fail_backlight;
	} else if (asus->driver->quirks->wmi_backlight_set_devstate)
		err = asus_wmi_set_devstate(ASUS_WMI_DEVID_BACKLIGHT, 2, NULL);

	if (asus_wmi_has_fnlock_key(asus)) {
		asus->fnlock_locked = true;
		asus_wmi_fnlock_update(asus);
	}

	status = wmi_install_notify_handler(asus->driver->event_guid,
					    asus_wmi_notify, asus);
	if (ACPI_FAILURE(status)) {
		pr_err("Unable to register notify handler - %d\n", status);
		err = -ENODEV;
		goto fail_wmi_handler;
	}

	asus_wmi_battery_init(asus);

	asus_wmi_debugfs_init(asus);

	return 0;

fail_wmi_handler:
	asus_wmi_backlight_exit(asus);
fail_backlight:
	asus_wmi_rfkill_exit(asus);
fail_rfkill:
	asus_wmi_led_exit(asus);
fail_leds:
fail_hwmon:
	asus_wmi_input_exit(asus);
fail_input:
	asus_wmi_sysfs_exit(asus->platform_device);
fail_sysfs:
fail_fan_boost_mode:
fail_platform:
	kfree(asus);
	return err;
}