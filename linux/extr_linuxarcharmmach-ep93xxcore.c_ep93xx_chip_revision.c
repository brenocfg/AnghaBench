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

/* Variables and functions */
 int /*<<< orphan*/  EP93XX_SYSCON_SYSCFG ; 
 unsigned int EP93XX_SYSCON_SYSCFG_REV_MASK ; 
 unsigned int EP93XX_SYSCON_SYSCFG_REV_SHIFT ; 
 unsigned int __raw_readl (int /*<<< orphan*/ ) ; 

unsigned int ep93xx_chip_revision(void)
{
	unsigned int v;

	v = __raw_readl(EP93XX_SYSCON_SYSCFG);
	v &= EP93XX_SYSCON_SYSCFG_REV_MASK;
	v >>= EP93XX_SYSCON_SYSCFG_REV_SHIFT;
	return v;
}