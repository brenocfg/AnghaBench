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
struct asus_wmi {int fan_boost_mode_available; int fan_boost_mode_mask; } ;

/* Variables and functions */
 int ASUS_FAN_BOOST_MODES_MASK ; 
 int /*<<< orphan*/  ASUS_WMI_DEVID_FAN_BOOST_MODE ; 
 int ASUS_WMI_DSTS_PRESENCE_BIT ; 
 int ENODEV ; 
 int asus_wmi_get_devstate (struct asus_wmi*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int fan_boost_mode_check_present(struct asus_wmi *asus)
{
	u32 result;
	int err;

	asus->fan_boost_mode_available = false;

	err = asus_wmi_get_devstate(asus, ASUS_WMI_DEVID_FAN_BOOST_MODE,
				    &result);
	if (err) {
		if (err == -ENODEV)
			return 0;
		else
			return err;
	}

	if ((result & ASUS_WMI_DSTS_PRESENCE_BIT) &&
			(result & ASUS_FAN_BOOST_MODES_MASK)) {
		asus->fan_boost_mode_available = true;
		asus->fan_boost_mode_mask = result & ASUS_FAN_BOOST_MODES_MASK;
	}

	return 0;
}