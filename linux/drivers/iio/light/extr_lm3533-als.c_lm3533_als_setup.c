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
struct lm3533_als_platform_data {int /*<<< orphan*/  r_select; int /*<<< orphan*/  pwm_mode; } ;
struct lm3533_als {int dummy; } ;

/* Variables and functions */
 int lm3533_als_set_input_mode (struct lm3533_als*,int /*<<< orphan*/ ) ; 
 int lm3533_als_set_resistor (struct lm3533_als*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lm3533_als_setup(struct lm3533_als *als,
			    struct lm3533_als_platform_data *pdata)
{
	int ret;

	ret = lm3533_als_set_input_mode(als, pdata->pwm_mode);
	if (ret)
		return ret;

	/* ALS input is always high impedance in PWM-mode. */
	if (!pdata->pwm_mode) {
		ret = lm3533_als_set_resistor(als, pdata->r_select);
		if (ret)
			return ret;
	}

	return 0;
}