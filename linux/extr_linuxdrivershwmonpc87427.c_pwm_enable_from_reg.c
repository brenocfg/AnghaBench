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
 int EPROTO ; 
 int PWM_ENABLE_MODE_MASK ; 
#define  PWM_MODE_AUTO 131 
#define  PWM_MODE_MANUAL 130 
#define  PWM_MODE_OFF 129 
#define  PWM_MODE_ON 128 

__attribute__((used)) static inline int pwm_enable_from_reg(u8 reg)
{
	switch (reg & PWM_ENABLE_MODE_MASK) {
	case PWM_MODE_ON:
		return 0;
	case PWM_MODE_MANUAL:
	case PWM_MODE_OFF:
		return 1;
	case PWM_MODE_AUTO:
		return 2;
	default:
		return -EPROTO;
	}
}