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
typedef  scalar_t__ u32 ;
struct asus_rfkill {scalar_t__ dev_id; TYPE_2__* asus; } ;
struct TYPE_4__ {TYPE_1__* driver; } ;
struct TYPE_3__ {scalar_t__ wlan_ctrl_by_user; } ;

/* Variables and functions */
 scalar_t__ ASUS_WMI_DEVID_WLAN ; 
 scalar_t__ ASUS_WMI_DEVID_WLAN_LED ; 
 int asus_wmi_set_devstate (scalar_t__,scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int asus_rfkill_set(void *data, bool blocked)
{
	struct asus_rfkill *priv = data;
	u32 ctrl_param = !blocked;
	u32 dev_id = priv->dev_id;

	/*
	 * If the user bit is set, BIOS can't set and record the wlan status,
	 * it will report the value read from id ASUS_WMI_DEVID_WLAN_LED
	 * while we query the wlan status through WMI(ASUS_WMI_DEVID_WLAN).
	 * So, we have to record wlan status in id ASUS_WMI_DEVID_WLAN_LED
	 * while setting the wlan status through WMI.
	 * This is also the behavior that windows app will do.
	 */
	if ((dev_id == ASUS_WMI_DEVID_WLAN) &&
	     priv->asus->driver->wlan_ctrl_by_user)
		dev_id = ASUS_WMI_DEVID_WLAN_LED;

	return asus_wmi_set_devstate(dev_id, ctrl_param, NULL);
}