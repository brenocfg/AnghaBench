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
struct ina2xx_chip_info {int /*<<< orphan*/  avg; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int EINVAL ; 
 unsigned int INA226_AVG_MASK ; 
 unsigned int INA226_SHIFT_AVG (int) ; 
 int find_closest (unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ina226_avg_tab ; 

__attribute__((used)) static int ina226_set_average(struct ina2xx_chip_info *chip, unsigned int val,
			      unsigned int *config)
{
	int bits;

	if (val > 1024 || val < 1)
		return -EINVAL;

	bits = find_closest(val, ina226_avg_tab,
			    ARRAY_SIZE(ina226_avg_tab));

	chip->avg = ina226_avg_tab[bits];

	*config &= ~INA226_AVG_MASK;
	*config |= INA226_SHIFT_AVG(bits) & INA226_AVG_MASK;

	return 0;
}