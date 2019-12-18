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
struct asus_wmi {int battery_rsoc_available; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASUS_WMI_DEVID_RSOC ; 
 scalar_t__ asus_wmi_dev_is_present (struct asus_wmi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  battery_hook ; 
 int /*<<< orphan*/  battery_hook_register (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void asus_wmi_battery_init(struct asus_wmi *asus)
{
	asus->battery_rsoc_available = false;
	if (asus_wmi_dev_is_present(asus, ASUS_WMI_DEVID_RSOC)) {
		asus->battery_rsoc_available = true;
		battery_hook_register(&battery_hook);
	}
}