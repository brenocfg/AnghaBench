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
struct tps65910 {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ TPS65910 ; 
 unsigned int TPS65910_VDAC ; 
 unsigned int TPS65910_VIO ; 
 unsigned int TPS65911_VDDCTRL_OP ; 
 unsigned int TPS65911_VDDCTRL_SR ; 
 struct tps65910* dev_get_drvdata (struct device*) ; 
 scalar_t__ tps65910_chip_id (struct tps65910*) ; 

__attribute__((used)) static bool is_volatile_reg(struct device *dev, unsigned int reg)
{
	struct tps65910 *tps65910 = dev_get_drvdata(dev);

	/*
	 * Caching all regulator registers.
	 * All regualator register address range is same for
	 * TPS65910 and TPS65911
	 */
	if ((reg >= TPS65910_VIO) && (reg <= TPS65910_VDAC)) {
		/* Check for non-existing register */
		if (tps65910_chip_id(tps65910) == TPS65910)
			if ((reg == TPS65911_VDDCTRL_OP) ||
				(reg == TPS65911_VDDCTRL_SR))
				return true;
		return false;
	}
	return true;
}