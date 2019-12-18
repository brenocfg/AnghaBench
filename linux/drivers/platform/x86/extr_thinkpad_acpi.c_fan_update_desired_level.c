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
 int TP_EC_FAN_AUTO ; 
 int TP_EC_FAN_FULLSPEED ; 
 int fan_control_desired_level ; 

__attribute__((used)) static void fan_update_desired_level(u8 status)
{
	if ((status &
	     (TP_EC_FAN_AUTO | TP_EC_FAN_FULLSPEED)) == 0) {
		if (status > 7)
			fan_control_desired_level = 7;
		else
			fan_control_desired_level = status;
	}
}