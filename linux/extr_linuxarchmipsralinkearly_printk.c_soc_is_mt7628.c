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
 int /*<<< orphan*/  CONFIG_SOC_MT7620 ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 scalar_t__ MT7628_CHIP_NAME1 ; 
 scalar_t__ __raw_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chipid_membase ; 

__attribute__((used)) static inline int soc_is_mt7628(void)
{
	return IS_ENABLED(CONFIG_SOC_MT7620) &&
		(__raw_readl(chipid_membase) == MT7628_CHIP_NAME1);
}