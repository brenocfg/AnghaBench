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
typedef  int /*<<< orphan*/  u8 ;

/* Variables and functions */
 int LM3533_LED_DELAY1_TMAX ; 
 int LM3533_LED_DELAY1_TMIN ; 
 int /*<<< orphan*/  LM3533_LED_DELAY1_TSTEP ; 
 int /*<<< orphan*/  LM3533_LED_DELAY1_VMAX ; 
 int /*<<< orphan*/  LM3533_LED_DELAY1_VMIN ; 
 int LM3533_LED_DELAY2_TMAX ; 
 int LM3533_LED_DELAY2_TMIN ; 
 int /*<<< orphan*/  LM3533_LED_DELAY2_TSTEP ; 
 int /*<<< orphan*/  LM3533_LED_DELAY2_VMAX ; 
 int /*<<< orphan*/  LM3533_LED_DELAY2_VMIN ; 
 int LM3533_LED_DELAY3_TMAX ; 
 int LM3533_LED_DELAY3_TMIN ; 
 int /*<<< orphan*/  LM3533_LED_DELAY3_TSTEP ; 
 int /*<<< orphan*/  LM3533_LED_DELAY3_VMAX ; 
 int /*<<< orphan*/  LM3533_LED_DELAY3_VMIN ; 
 unsigned int clamp (unsigned int,int,int) ; 
 int /*<<< orphan*/  time_to_val (unsigned int*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u8 lm3533_led_get_hw_delay(unsigned *delay)
{
	unsigned t;
	u8 val;

	t = *delay * 1000;

	if (t >= (LM3533_LED_DELAY2_TMAX + LM3533_LED_DELAY3_TMIN) / 2) {
		t = clamp(t, LM3533_LED_DELAY3_TMIN, LM3533_LED_DELAY3_TMAX);
		val = time_to_val(&t,	LM3533_LED_DELAY3_TMIN,
					LM3533_LED_DELAY3_TSTEP,
					LM3533_LED_DELAY3_VMIN,
					LM3533_LED_DELAY3_VMAX);
	} else if (t >= (LM3533_LED_DELAY1_TMAX + LM3533_LED_DELAY2_TMIN) / 2) {
		t = clamp(t, LM3533_LED_DELAY2_TMIN, LM3533_LED_DELAY2_TMAX);
		val = time_to_val(&t,	LM3533_LED_DELAY2_TMIN,
					LM3533_LED_DELAY2_TSTEP,
					LM3533_LED_DELAY2_VMIN,
					LM3533_LED_DELAY2_VMAX);
	} else {
		t = clamp(t, LM3533_LED_DELAY1_TMIN, LM3533_LED_DELAY1_TMAX);
		val = time_to_val(&t,	LM3533_LED_DELAY1_TMIN,
					LM3533_LED_DELAY1_TSTEP,
					LM3533_LED_DELAY1_VMIN,
					LM3533_LED_DELAY1_VMAX);
	}

	*delay = (t + 500) / 1000;

	return val;
}