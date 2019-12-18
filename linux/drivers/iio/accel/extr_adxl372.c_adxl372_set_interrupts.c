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
struct adxl372_state {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADXL372_INT1_MAP ; 
 int /*<<< orphan*/  ADXL372_INT2_MAP ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char) ; 

__attribute__((used)) static int adxl372_set_interrupts(struct adxl372_state *st,
				  unsigned char int1_bitmask,
				  unsigned char int2_bitmask)
{
	int ret;

	ret = regmap_write(st->regmap, ADXL372_INT1_MAP, int1_bitmask);
	if (ret < 0)
		return ret;

	return regmap_write(st->regmap, ADXL372_INT2_MAP, int2_bitmask);
}