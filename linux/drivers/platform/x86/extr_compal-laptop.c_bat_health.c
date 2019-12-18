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

/* Variables and functions */
 int /*<<< orphan*/  BAT_STOP_CHARGE1 ; 
 int BAT_STOP_CHRG1_BAD_CELL ; 
 int BAT_STOP_CHRG1_COMM_FAIL ; 
 int BAT_STOP_CHRG1_OVERTEMPERATURE ; 
 int BAT_STOP_CHRG1_OVERVOLTAGE ; 
 int POWER_SUPPLY_HEALTH_DEAD ; 
 int POWER_SUPPLY_HEALTH_GOOD ; 
 int POWER_SUPPLY_HEALTH_OVERHEAT ; 
 int POWER_SUPPLY_HEALTH_OVERVOLTAGE ; 
 int POWER_SUPPLY_HEALTH_UNKNOWN ; 
 int ec_read_u8 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bat_health(void)
{
	u8 status = ec_read_u8(BAT_STOP_CHARGE1);

	if (status & BAT_STOP_CHRG1_OVERTEMPERATURE)
		return POWER_SUPPLY_HEALTH_OVERHEAT;
	if (status & BAT_STOP_CHRG1_OVERVOLTAGE)
		return POWER_SUPPLY_HEALTH_OVERVOLTAGE;
	if (status & BAT_STOP_CHRG1_BAD_CELL)
		return POWER_SUPPLY_HEALTH_DEAD;
	if (status & BAT_STOP_CHRG1_COMM_FAIL)
		return POWER_SUPPLY_HEALTH_UNKNOWN;
	return POWER_SUPPLY_HEALTH_GOOD;
}