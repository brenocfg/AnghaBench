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
struct adxl372_state {scalar_t__ odr; unsigned int inact_time_ms; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 scalar_t__ ADXL372_ODR_6400HZ ; 
 int /*<<< orphan*/  ADXL372_TIME_INACT_H ; 
 int /*<<< orphan*/  ADXL372_TIME_INACT_L ; 
 unsigned int DIV_ROUND_CLOSEST (unsigned int,unsigned int) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int adxl372_set_inactivity_time_ms(struct adxl372_state *st,
					  unsigned int inact_time_ms)
{
	unsigned int reg_val_h, reg_val_l, res, scale_factor;
	int ret;

	/*
	 * 13 ms per code is the scale factor of the TIME_INACT register for
	 * ODR = 6400 Hz. It is 26 ms per code for ODR = 3200 Hz and below.
	 */
	if (st->odr == ADXL372_ODR_6400HZ)
		scale_factor = 13;
	else
		scale_factor = 26;

	res = DIV_ROUND_CLOSEST(inact_time_ms, scale_factor);
	reg_val_h = (res >> 8) & 0xFF;
	reg_val_l = res & 0xFF;

	ret = regmap_write(st->regmap, ADXL372_TIME_INACT_H, reg_val_h);
	if (ret < 0)
		return ret;

	ret = regmap_write(st->regmap, ADXL372_TIME_INACT_L, reg_val_l);
	if (ret < 0)
		return ret;

	st->inact_time_ms = inact_time_ms;

	return ret;
}