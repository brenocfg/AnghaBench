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
 int BAT_S1_LiION_OR_NiMH ; 
 int /*<<< orphan*/  BAT_STATUS1 ; 
 int POWER_SUPPLY_TECHNOLOGY_LION ; 
 int POWER_SUPPLY_TECHNOLOGY_NiMH ; 
 int ec_read_u8 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bat_technology(void)
{
	u8 status = ec_read_u8(BAT_STATUS1);

	if (status & BAT_S1_LiION_OR_NiMH)
		return POWER_SUPPLY_TECHNOLOGY_LION;
	return POWER_SUPPLY_TECHNOLOGY_NiMH;
}