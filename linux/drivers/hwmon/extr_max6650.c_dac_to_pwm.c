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
 int DAC_LIMIT (int) ; 
 int clamp_val (int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int dac_to_pwm(int dac, bool v12)
{
	/*
	 * Useful range for dac is 0-180 for 12V fans and 0-76 for 5V fans.
	 * Lower DAC values mean higher speeds.
	 */
	return clamp_val(255 - (255 * dac) / DAC_LIMIT(v12), 0, 255);
}