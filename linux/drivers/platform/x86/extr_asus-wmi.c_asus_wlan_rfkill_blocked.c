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
struct asus_wmi {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASUS_WMI_DEVID_WLAN ; 
 int asus_wmi_get_devstate_simple (struct asus_wmi*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool asus_wlan_rfkill_blocked(struct asus_wmi *asus)
{
	int result = asus_wmi_get_devstate_simple(asus, ASUS_WMI_DEVID_WLAN);

	if (result < 0)
		return false;
	return !result;
}