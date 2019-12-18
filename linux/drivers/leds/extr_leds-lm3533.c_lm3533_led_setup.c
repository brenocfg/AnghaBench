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
struct lm3533_led_platform_data {int /*<<< orphan*/  pwm; int /*<<< orphan*/  max_current; } ;
struct lm3533_led {int /*<<< orphan*/  cb; } ;

/* Variables and functions */
 int lm3533_ctrlbank_set_max_current (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int lm3533_ctrlbank_set_pwm (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lm3533_led_setup(struct lm3533_led *led,
					struct lm3533_led_platform_data *pdata)
{
	int ret;

	ret = lm3533_ctrlbank_set_max_current(&led->cb, pdata->max_current);
	if (ret)
		return ret;

	return lm3533_ctrlbank_set_pwm(&led->cb, pdata->pwm);
}