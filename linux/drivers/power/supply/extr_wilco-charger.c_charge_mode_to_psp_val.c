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
typedef  enum charge_mode { ____Placeholder_charge_mode } charge_mode ;

/* Variables and functions */
#define  CHARGE_MODE_AC 132 
#define  CHARGE_MODE_AUTO 131 
#define  CHARGE_MODE_CUSTOM 130 
#define  CHARGE_MODE_EXP 129 
#define  CHARGE_MODE_STD 128 
 int EINVAL ; 
 int POWER_SUPPLY_CHARGE_TYPE_ADAPTIVE ; 
 int POWER_SUPPLY_CHARGE_TYPE_CUSTOM ; 
 int POWER_SUPPLY_CHARGE_TYPE_FAST ; 
 int POWER_SUPPLY_CHARGE_TYPE_STANDARD ; 
 int POWER_SUPPLY_CHARGE_TYPE_TRICKLE ; 

__attribute__((used)) static int charge_mode_to_psp_val(enum charge_mode mode)
{
	switch (mode) {
	case CHARGE_MODE_AC:
		return POWER_SUPPLY_CHARGE_TYPE_TRICKLE;
	case CHARGE_MODE_EXP:
		return POWER_SUPPLY_CHARGE_TYPE_FAST;
	case CHARGE_MODE_STD:
		return POWER_SUPPLY_CHARGE_TYPE_STANDARD;
	case CHARGE_MODE_AUTO:
		return POWER_SUPPLY_CHARGE_TYPE_ADAPTIVE;
	case CHARGE_MODE_CUSTOM:
		return POWER_SUPPLY_CHARGE_TYPE_CUSTOM;
	default:
		return -EINVAL;
	}
}