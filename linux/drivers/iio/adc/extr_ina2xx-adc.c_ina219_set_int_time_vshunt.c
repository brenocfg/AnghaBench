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
struct ina2xx_chip_info {unsigned int int_time_vshunt; } ;

/* Variables and functions */
 unsigned int INA219_ITS_MASK ; 
 unsigned int INA219_SHIFT_ITS (int) ; 
 int ina219_lookup_int_time (unsigned int*,int*) ; 

__attribute__((used)) static int ina219_set_int_time_vshunt(struct ina2xx_chip_info *chip,
				      unsigned int val_us, unsigned int *config)
{
	int bits, ret;
	unsigned int val_us_best = val_us;

	ret = ina219_lookup_int_time(&val_us_best, &bits);
	if (ret)
		return ret;

	chip->int_time_vshunt = val_us_best;

	*config &= ~INA219_ITS_MASK;
	*config |= INA219_SHIFT_ITS(bits) & INA219_ITS_MASK;

	return 0;
}