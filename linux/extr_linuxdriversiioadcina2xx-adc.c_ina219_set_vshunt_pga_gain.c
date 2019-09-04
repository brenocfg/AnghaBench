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
struct ina2xx_chip_info {int /*<<< orphan*/  pga_gain_vshunt; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int EINVAL ; 
 unsigned int INA219_PGA_MASK ; 
 unsigned int INA219_SHIFT_PGA (int) ; 
 int find_closest (unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ina219_vshunt_gain_tab ; 

__attribute__((used)) static int ina219_set_vshunt_pga_gain(struct ina2xx_chip_info *chip,
				      unsigned int gain,
				      unsigned int *config)
{
	int bits;

	if (gain < 125 || gain > 1000)
		return -EINVAL;

	bits = find_closest(gain, ina219_vshunt_gain_tab,
			    ARRAY_SIZE(ina219_vshunt_gain_tab));

	chip->pga_gain_vshunt = ina219_vshunt_gain_tab[bits];
	bits = 3 - bits;

	*config &= ~INA219_PGA_MASK;
	*config |= INA219_SHIFT_PGA(bits) & INA219_PGA_MASK;

	return 0;
}