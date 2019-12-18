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
struct sky81452_bl_platform_data {int boost_current_limit; int short_detection_threshold; scalar_t__ phase_shift; scalar_t__ dpwm_mode; scalar_t__ ignore_pwm; } ;
struct regmap {int dummy; } ;

/* Variables and functions */
 int CTZ (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 unsigned int SKY81452_IGPW ; 
 unsigned int SKY81452_ILIM ; 
 unsigned int SKY81452_PHASE ; 
 unsigned int SKY81452_PWMMD ; 
 int /*<<< orphan*/  SKY81452_REG2 ; 
 int /*<<< orphan*/  SKY81452_VSHRT ; 
 int regmap_write (struct regmap*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int sky81452_bl_init_device(struct regmap *regmap,
		struct sky81452_bl_platform_data *pdata)
{
	unsigned int value;

	value = pdata->ignore_pwm ? SKY81452_IGPW : 0;
	value |= pdata->dpwm_mode ? SKY81452_PWMMD : 0;
	value |= pdata->phase_shift ? 0 : SKY81452_PHASE;

	if (pdata->boost_current_limit == 2300)
		value |= SKY81452_ILIM;
	else if (pdata->boost_current_limit != 2750)
		return -EINVAL;

	if (pdata->short_detection_threshold < 4 ||
				pdata->short_detection_threshold > 7)
		return -EINVAL;
	value |= (7 - pdata->short_detection_threshold) << CTZ(SKY81452_VSHRT);

	return regmap_write(regmap, SKY81452_REG2, value);
}