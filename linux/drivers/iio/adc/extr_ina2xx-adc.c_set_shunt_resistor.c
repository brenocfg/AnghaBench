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
struct ina2xx_chip_info {unsigned int shunt_resistor_uohm; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int INT_MAX ; 

__attribute__((used)) static int set_shunt_resistor(struct ina2xx_chip_info *chip, unsigned int val)
{
	if (val == 0 || val > INT_MAX)
		return -EINVAL;

	chip->shunt_resistor_uohm = val;

	return 0;
}