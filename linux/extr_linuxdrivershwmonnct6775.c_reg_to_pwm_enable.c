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
typedef  enum pwm_enable { ____Placeholder_pwm_enable } pwm_enable ;

/* Variables and functions */
 int off ; 

__attribute__((used)) static enum pwm_enable reg_to_pwm_enable(int pwm, int mode)
{
	if (mode == 0 && pwm == 255)
		return off;
	return mode + 1;
}