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
typedef  unsigned int u8 ;
struct tegra_mc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MC_EMEM_ADR_CFG ; 
 unsigned int MC_EMEM_ADR_CFG_EMEM_NUMDEV ; 
 unsigned int mc_readl (struct tegra_mc*,int /*<<< orphan*/ ) ; 

unsigned int tegra_mc_get_emem_device_count(struct tegra_mc *mc)
{
	u8 dram_count;

	dram_count = mc_readl(mc, MC_EMEM_ADR_CFG);
	dram_count &= MC_EMEM_ADR_CFG_EMEM_NUMDEV;
	dram_count++;

	return dram_count;
}