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
struct asus_wmi {TYPE_2__* driver; int /*<<< orphan*/  uwb; int /*<<< orphan*/  gps; int /*<<< orphan*/  wwan3g; int /*<<< orphan*/  wimax; int /*<<< orphan*/  bluetooth; int /*<<< orphan*/  wlan; int /*<<< orphan*/  wmi_lock; int /*<<< orphan*/  hotplug_lock; } ;
struct TYPE_4__ {TYPE_1__* quirks; } ;
struct TYPE_3__ {int /*<<< orphan*/  hotplug_wireless; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASUS_WMI_DEVID_BLUETOOTH ; 
 int /*<<< orphan*/  ASUS_WMI_DEVID_GPS ; 
 int /*<<< orphan*/  ASUS_WMI_DEVID_UWB ; 
 int /*<<< orphan*/  ASUS_WMI_DEVID_WIMAX ; 
 int /*<<< orphan*/  ASUS_WMI_DEVID_WLAN ; 
 int /*<<< orphan*/  ASUS_WMI_DEVID_WWAN3G ; 
 int EBUSY ; 
 int ENODEV ; 
 int /*<<< orphan*/  RFKILL_TYPE_BLUETOOTH ; 
 int /*<<< orphan*/  RFKILL_TYPE_GPS ; 
 int /*<<< orphan*/  RFKILL_TYPE_UWB ; 
 int /*<<< orphan*/  RFKILL_TYPE_WIMAX ; 
 int /*<<< orphan*/  RFKILL_TYPE_WLAN ; 
 int /*<<< orphan*/  RFKILL_TYPE_WWAN ; 
 int asus_new_rfkill (struct asus_wmi*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  asus_register_rfkill_notifier (struct asus_wmi*,char*) ; 
 int /*<<< orphan*/  asus_rfkill_hotplug (struct asus_wmi*) ; 
 int asus_setup_pci_hotplug (struct asus_wmi*) ; 
 int /*<<< orphan*/  asus_wmi_rfkill_exit (struct asus_wmi*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int asus_wmi_rfkill_init(struct asus_wmi *asus)
{
	int result = 0;

	mutex_init(&asus->hotplug_lock);
	mutex_init(&asus->wmi_lock);

	result = asus_new_rfkill(asus, &asus->wlan, "asus-wlan",
				 RFKILL_TYPE_WLAN, ASUS_WMI_DEVID_WLAN);

	if (result && result != -ENODEV)
		goto exit;

	result = asus_new_rfkill(asus, &asus->bluetooth,
				 "asus-bluetooth", RFKILL_TYPE_BLUETOOTH,
				 ASUS_WMI_DEVID_BLUETOOTH);

	if (result && result != -ENODEV)
		goto exit;

	result = asus_new_rfkill(asus, &asus->wimax, "asus-wimax",
				 RFKILL_TYPE_WIMAX, ASUS_WMI_DEVID_WIMAX);

	if (result && result != -ENODEV)
		goto exit;

	result = asus_new_rfkill(asus, &asus->wwan3g, "asus-wwan3g",
				 RFKILL_TYPE_WWAN, ASUS_WMI_DEVID_WWAN3G);

	if (result && result != -ENODEV)
		goto exit;

	result = asus_new_rfkill(asus, &asus->gps, "asus-gps",
				 RFKILL_TYPE_GPS, ASUS_WMI_DEVID_GPS);

	if (result && result != -ENODEV)
		goto exit;

	result = asus_new_rfkill(asus, &asus->uwb, "asus-uwb",
				 RFKILL_TYPE_UWB, ASUS_WMI_DEVID_UWB);

	if (result && result != -ENODEV)
		goto exit;

	if (!asus->driver->quirks->hotplug_wireless)
		goto exit;

	result = asus_setup_pci_hotplug(asus);
	/*
	 * If we get -EBUSY then something else is handling the PCI hotplug -
	 * don't fail in this case
	 */
	if (result == -EBUSY)
		result = 0;

	asus_register_rfkill_notifier(asus, "\\_SB.PCI0.P0P5");
	asus_register_rfkill_notifier(asus, "\\_SB.PCI0.P0P6");
	asus_register_rfkill_notifier(asus, "\\_SB.PCI0.P0P7");
	/*
	 * Refresh pci hotplug in case the rfkill state was changed during
	 * setup.
	 */
	asus_rfkill_hotplug(asus);

exit:
	if (result && result != -ENODEV)
		asus_wmi_rfkill_exit(asus);

	if (result == -ENODEV)
		result = 0;

	return result;
}