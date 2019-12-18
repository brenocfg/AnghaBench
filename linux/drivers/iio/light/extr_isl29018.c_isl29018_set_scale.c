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
struct isl29018_scale {int scale; int uscale; } ;
struct isl29018_chip {size_t int_time; struct isl29018_scale scale; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (struct isl29018_scale*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  ISL29018_CMD2_RANGE_MASK ; 
 unsigned int ISL29018_CMD2_RANGE_SHIFT ; 
 int /*<<< orphan*/  ISL29018_REG_ADD_COMMAND2 ; 
 struct isl29018_scale** isl29018_scales ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int isl29018_set_scale(struct isl29018_chip *chip, int scale, int uscale)
{
	unsigned int i;
	int ret;
	struct isl29018_scale new_scale;

	for (i = 0; i < ARRAY_SIZE(isl29018_scales[chip->int_time]); ++i) {
		if (scale == isl29018_scales[chip->int_time][i].scale &&
		    uscale == isl29018_scales[chip->int_time][i].uscale) {
			new_scale = isl29018_scales[chip->int_time][i];
			break;
		}
	}

	if (i >= ARRAY_SIZE(isl29018_scales[chip->int_time]))
		return -EINVAL;

	ret = regmap_update_bits(chip->regmap, ISL29018_REG_ADD_COMMAND2,
				 ISL29018_CMD2_RANGE_MASK,
				 i << ISL29018_CMD2_RANGE_SHIFT);
	if (ret < 0)
		return ret;

	chip->scale = new_scale;

	return 0;
}