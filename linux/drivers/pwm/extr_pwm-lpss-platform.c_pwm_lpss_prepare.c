#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pwm_lpss_chip {TYPE_1__* info; } ;
struct device {int dummy; } ;
struct TYPE_2__ {scalar_t__ other_devices_aml_touches_pwm_regs; } ;

/* Variables and functions */
 struct pwm_lpss_chip* dev_get_drvdata (struct device*) ; 

__attribute__((used)) static int pwm_lpss_prepare(struct device *dev)
{
	struct pwm_lpss_chip *lpwm = dev_get_drvdata(dev);

	/*
	 * If other device's AML code touches the PWM regs on suspend/resume
	 * force runtime-resume the PWM controller to allow this.
	 */
	if (lpwm->info->other_devices_aml_touches_pwm_regs)
		return 0; /* Force runtime-resume */

	return 1; /* If runtime-suspended leave as is */
}