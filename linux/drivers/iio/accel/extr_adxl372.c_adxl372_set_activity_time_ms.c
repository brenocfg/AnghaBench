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
struct adxl372_state {scalar_t__ odr; unsigned int act_time_ms; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 scalar_t__ ADXL372_ODR_6400HZ ; 
 int /*<<< orphan*/  ADXL372_TIME_ACT ; 
 unsigned int DIV_ROUND_CLOSEST (unsigned int,unsigned int) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int adxl372_set_activity_time_ms(struct adxl372_state *st,
					unsigned int act_time_ms)
{
	unsigned int reg_val, scale_factor;
	int ret;

	/*
	 * 3.3 ms per code is the scale factor of the TIME_ACT register for
	 * ODR = 6400 Hz. It is 6.6 ms per code for ODR = 3200 Hz and below.
	 */
	if (st->odr == ADXL372_ODR_6400HZ)
		scale_factor = 3300;
	else
		scale_factor = 6600;

	reg_val = DIV_ROUND_CLOSEST(act_time_ms * 1000, scale_factor);

	/* TIME_ACT register is 8 bits wide */
	if (reg_val > 0xFF)
		reg_val = 0xFF;

	ret = regmap_write(st->regmap, ADXL372_TIME_ACT, reg_val);
	if (ret < 0)
		return ret;

	st->act_time_ms = act_time_ms;

	return ret;
}