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
struct adxl372_state {int odr; int /*<<< orphan*/  regmap; } ;
typedef  enum adxl372_odr { ____Placeholder_adxl372_odr } adxl372_odr ;

/* Variables and functions */
 int /*<<< orphan*/  ADXL372_TIMING ; 
 int /*<<< orphan*/  ADXL372_TIMING_ODR_MODE (int) ; 
 int /*<<< orphan*/  ADXL372_TIMING_ODR_MSK ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int adxl372_set_odr(struct adxl372_state *st,
			   enum adxl372_odr odr)
{
	int ret;

	ret = regmap_update_bits(st->regmap, ADXL372_TIMING,
				 ADXL372_TIMING_ODR_MSK,
				 ADXL372_TIMING_ODR_MODE(odr));
	if (ret < 0)
		return ret;

	st->odr = odr;

	return ret;
}