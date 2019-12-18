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
struct asus_wmi {int /*<<< orphan*/  sfun; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASUS_WMI_DEVID_FAN_CTRL ; 
 int ASUS_WMI_DSTS_PRESENCE_BIT ; 
 int ASUS_WMI_UNSUPPORTED_METHOD ; 
 int asus_agfn_fan_speed_read (struct asus_wmi*,int,int*) ; 
 int asus_wmi_get_devstate (struct asus_wmi*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static bool asus_wmi_has_agfn_fan(struct asus_wmi *asus)
{
	int status;
	int speed;
	u32 value;

	status = asus_agfn_fan_speed_read(asus, 1, &speed);
	if (status != 0)
		return false;

	status = asus_wmi_get_devstate(asus, ASUS_WMI_DEVID_FAN_CTRL, &value);
	if (status != 0)
		return false;

	/*
	 * We need to find a better way, probably using sfun,
	 * bits or spec ...
	 * Currently we disable it if:
	 * - ASUS_WMI_UNSUPPORTED_METHOD is returned
	 * - reverved bits are non-zero
	 * - sfun and presence bit are not set
	 */
	return !(value == ASUS_WMI_UNSUPPORTED_METHOD || value & 0xFFF80000
		 || (!asus->sfun && !(value & ASUS_WMI_DSTS_PRESENCE_BIT)));
}