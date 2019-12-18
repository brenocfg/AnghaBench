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
struct pwm_device {int dummy; } ;

/* Variables and functions */
 int PWM_ENABLE ; 
 int pwm_lpss_read (struct pwm_device*) ; 
 int /*<<< orphan*/  pwm_lpss_write (struct pwm_device*,int) ; 

__attribute__((used)) static inline void pwm_lpss_cond_enable(struct pwm_device *pwm, bool cond)
{
	if (cond)
		pwm_lpss_write(pwm, pwm_lpss_read(pwm) | PWM_ENABLE);
}