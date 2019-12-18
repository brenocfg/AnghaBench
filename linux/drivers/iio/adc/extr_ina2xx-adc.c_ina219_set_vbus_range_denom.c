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
struct ina2xx_chip_info {int range_vbus; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int INA219_BRNG_MASK ; 
 unsigned int INA219_SHIFT_BRNG (int) ; 

__attribute__((used)) static int ina219_set_vbus_range_denom(struct ina2xx_chip_info *chip,
				       unsigned int range,
				       unsigned int *config)
{
	if (range == 1)
		chip->range_vbus = 32;
	else if (range == 2)
		chip->range_vbus = 16;
	else
		return -EINVAL;

	*config &= ~INA219_BRNG_MASK;
	*config |= INA219_SHIFT_BRNG(range == 1 ? 1 : 0) & INA219_BRNG_MASK;

	return 0;
}