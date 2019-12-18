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
 int /*<<< orphan*/  PWM_MODE_AUTO ; 
 int /*<<< orphan*/  PWM_MODE_MANUAL ; 
 int /*<<< orphan*/  PWM_MODE_OFF ; 
 int /*<<< orphan*/  PWM_MODE_ON ; 

__attribute__((used)) static inline u8 pwm_enable_to_reg(unsigned long val, u8 pwmval)
{
	switch (val) {
	default:
		return PWM_MODE_ON;
	case 1:
		return pwmval ? PWM_MODE_MANUAL : PWM_MODE_OFF;
	case 2:
		return PWM_MODE_AUTO;
	}
}