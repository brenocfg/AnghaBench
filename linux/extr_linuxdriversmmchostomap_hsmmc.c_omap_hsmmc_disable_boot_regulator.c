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
struct regulator {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct regulator*) ; 
 int regulator_disable (struct regulator*) ; 
 int regulator_enable (struct regulator*) ; 
 scalar_t__ regulator_is_enabled (struct regulator*) ; 

__attribute__((used)) static int omap_hsmmc_disable_boot_regulator(struct regulator *reg)
{
	int ret;

	if (IS_ERR(reg))
		return 0;

	if (regulator_is_enabled(reg)) {
		ret = regulator_enable(reg);
		if (ret)
			return ret;

		ret = regulator_disable(reg);
		if (ret)
			return ret;
	}

	return 0;
}