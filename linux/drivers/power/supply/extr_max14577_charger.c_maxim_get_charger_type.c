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
typedef  enum maxim_device_type { ____Placeholder_maxim_device_type } maxim_device_type ;
typedef  enum max14577_muic_charger_type { ____Placeholder_max14577_muic_charger_type } max14577_muic_charger_type ;

/* Variables and functions */
#define  MAX14577_CHARGER_TYPE_DEAD_BATTERY 135 
#define  MAX14577_CHARGER_TYPE_DEDICATED_CHG 134 
#define  MAX14577_CHARGER_TYPE_DOWNSTREAM_PORT 133 
#define  MAX14577_CHARGER_TYPE_NONE 132 
#define  MAX14577_CHARGER_TYPE_RESERVED 131 
#define  MAX14577_CHARGER_TYPE_SPECIAL_1A 130 
#define  MAX14577_CHARGER_TYPE_SPECIAL_500MA 129 
#define  MAX14577_CHARGER_TYPE_USB 128 
 int MAXIM_DEVICE_TYPE_MAX77836 ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*,int) ; 

__attribute__((used)) static enum max14577_muic_charger_type maxim_get_charger_type(
		enum maxim_device_type dev_type, u8 val) {
	switch (val) {
	case MAX14577_CHARGER_TYPE_NONE:
	case MAX14577_CHARGER_TYPE_USB:
	case MAX14577_CHARGER_TYPE_DOWNSTREAM_PORT:
	case MAX14577_CHARGER_TYPE_DEDICATED_CHG:
	case MAX14577_CHARGER_TYPE_SPECIAL_500MA:
	case MAX14577_CHARGER_TYPE_SPECIAL_1A:
		return val;
	case MAX14577_CHARGER_TYPE_DEAD_BATTERY:
	case MAX14577_CHARGER_TYPE_RESERVED:
		if (dev_type == MAXIM_DEVICE_TYPE_MAX77836)
			val |= 0x8;
		return val;
	default:
		WARN_ONCE(1, "max14577: Unsupported chgtyp register value 0x%02x", val);
		return val;
	}
}