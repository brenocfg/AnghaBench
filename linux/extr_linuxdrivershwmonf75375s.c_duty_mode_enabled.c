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
 int /*<<< orphan*/  WARN (int,char*,int) ; 

__attribute__((used)) static bool duty_mode_enabled(u8 pwm_enable)
{
	switch (pwm_enable) {
	case 0: /* Manual, duty mode (full speed) */
	case 1: /* Manual, duty mode */
	case 4: /* Auto, duty mode */
		return true;
	case 2: /* Auto, speed mode */
	case 3: /* Manual, speed mode */
		return false;
	default:
		WARN(1, "Unexpected pwm_enable value %d\n", pwm_enable);
		return true;
	}
}