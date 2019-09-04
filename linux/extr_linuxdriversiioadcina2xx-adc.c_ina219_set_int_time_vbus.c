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
struct ina2xx_chip_info {unsigned int int_time_vbus; } ;

/* Variables and functions */
 unsigned int INA219_ITB_MASK ; 
 unsigned int INA219_SHIFT_ITB (int) ; 
 int ina219_lookup_int_time (unsigned int*,int*) ; 

__attribute__((used)) static int ina219_set_int_time_vbus(struct ina2xx_chip_info *chip,
				    unsigned int val_us, unsigned int *config)
{
	int bits, ret;
	unsigned int val_us_best = val_us;

	ret = ina219_lookup_int_time(&val_us_best, &bits);
	if (ret)
		return ret;

	chip->int_time_vbus = val_us_best;

	*config &= ~INA219_ITB_MASK;
	*config |= INA219_SHIFT_ITB(bits) & INA219_ITB_MASK;

	return 0;
}