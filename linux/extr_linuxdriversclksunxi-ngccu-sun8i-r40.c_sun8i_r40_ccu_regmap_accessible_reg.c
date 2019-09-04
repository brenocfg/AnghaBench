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
struct device {int dummy; } ;

/* Variables and functions */
 unsigned int SUN8I_R40_GMAC_CFG_REG ; 

__attribute__((used)) static bool sun8i_r40_ccu_regmap_accessible_reg(struct device *dev,
						unsigned int reg)
{
	if (reg == SUN8I_R40_GMAC_CFG_REG)
		return true;
	return false;
}