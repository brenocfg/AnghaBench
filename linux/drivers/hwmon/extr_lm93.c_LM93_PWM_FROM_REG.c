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
typedef  enum pwm_freq { ____Placeholder_pwm_freq } pwm_freq ;

/* Variables and functions */
 int** lm93_pwm_map ; 

__attribute__((used)) static int LM93_PWM_FROM_REG(u8 reg, enum pwm_freq freq)
{
	return lm93_pwm_map[freq][reg & 0x0f];
}