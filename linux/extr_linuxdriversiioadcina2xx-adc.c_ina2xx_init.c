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
struct ina2xx_chip_info {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  INA2XX_CONFIG ; 
 int ina2xx_set_calibration (struct ina2xx_chip_info*) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int ina2xx_init(struct ina2xx_chip_info *chip, unsigned int config)
{
	int ret = regmap_write(chip->regmap, INA2XX_CONFIG, config);
	if (ret)
		return ret;

	return ina2xx_set_calibration(chip);
}