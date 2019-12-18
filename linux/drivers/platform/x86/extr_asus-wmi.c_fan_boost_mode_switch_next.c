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
typedef  int u8 ;
struct asus_wmi {int fan_boost_mode_mask; scalar_t__ fan_boost_mode; } ;

/* Variables and functions */
 scalar_t__ ASUS_FAN_BOOST_MODE_NORMAL ; 
 scalar_t__ ASUS_FAN_BOOST_MODE_OVERBOOST ; 
 int ASUS_FAN_BOOST_MODE_OVERBOOST_MASK ; 
 void* ASUS_FAN_BOOST_MODE_SILENT ; 
 int ASUS_FAN_BOOST_MODE_SILENT_MASK ; 
 int fan_boost_mode_write (struct asus_wmi*) ; 

__attribute__((used)) static int fan_boost_mode_switch_next(struct asus_wmi *asus)
{
	u8 mask = asus->fan_boost_mode_mask;

	if (asus->fan_boost_mode == ASUS_FAN_BOOST_MODE_NORMAL) {
		if (mask & ASUS_FAN_BOOST_MODE_OVERBOOST_MASK)
			asus->fan_boost_mode = ASUS_FAN_BOOST_MODE_OVERBOOST;
		else if (mask & ASUS_FAN_BOOST_MODE_SILENT_MASK)
			asus->fan_boost_mode = ASUS_FAN_BOOST_MODE_SILENT;
	} else if (asus->fan_boost_mode == ASUS_FAN_BOOST_MODE_OVERBOOST) {
		if (mask & ASUS_FAN_BOOST_MODE_SILENT_MASK)
			asus->fan_boost_mode = ASUS_FAN_BOOST_MODE_SILENT;
		else
			asus->fan_boost_mode = ASUS_FAN_BOOST_MODE_NORMAL;
	} else {
		asus->fan_boost_mode = ASUS_FAN_BOOST_MODE_NORMAL;
	}

	return fan_boost_mode_write(asus);
}