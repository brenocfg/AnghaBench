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

/* Variables and functions */
 int CHARGE_MODE_AC ; 
 int CHARGE_MODE_AUTO ; 
 int CHARGE_MODE_CUSTOM ; 
 int CHARGE_MODE_EXP ; 
 int CHARGE_MODE_STD ; 
 int EINVAL ; 
#define  POWER_SUPPLY_CHARGE_TYPE_ADAPTIVE 132 
#define  POWER_SUPPLY_CHARGE_TYPE_CUSTOM 131 
#define  POWER_SUPPLY_CHARGE_TYPE_FAST 130 
#define  POWER_SUPPLY_CHARGE_TYPE_STANDARD 129 
#define  POWER_SUPPLY_CHARGE_TYPE_TRICKLE 128 

__attribute__((used)) static int psp_val_to_charge_mode(int psp_val)
{
	switch (psp_val) {
	case POWER_SUPPLY_CHARGE_TYPE_TRICKLE:
		return CHARGE_MODE_AC;
	case POWER_SUPPLY_CHARGE_TYPE_FAST:
		return CHARGE_MODE_EXP;
	case POWER_SUPPLY_CHARGE_TYPE_STANDARD:
		return CHARGE_MODE_STD;
	case POWER_SUPPLY_CHARGE_TYPE_ADAPTIVE:
		return CHARGE_MODE_AUTO;
	case POWER_SUPPLY_CHARGE_TYPE_CUSTOM:
		return CHARGE_MODE_CUSTOM;
	default:
		return -EINVAL;
	}
}