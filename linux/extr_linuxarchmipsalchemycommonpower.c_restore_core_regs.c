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
 int /*<<< orphan*/  AU1000_MEM_STADDR0 ; 
 int /*<<< orphan*/  AU1000_MEM_STADDR1 ; 
 int /*<<< orphan*/  AU1000_MEM_STADDR2 ; 
 int /*<<< orphan*/  AU1000_MEM_STADDR3 ; 
 int /*<<< orphan*/  AU1000_MEM_STCFG0 ; 
 int /*<<< orphan*/  AU1000_MEM_STCFG1 ; 
 int /*<<< orphan*/  AU1000_MEM_STCFG2 ; 
 int /*<<< orphan*/  AU1000_MEM_STCFG3 ; 
 int /*<<< orphan*/  AU1000_MEM_STTIME0 ; 
 int /*<<< orphan*/  AU1000_MEM_STTIME1 ; 
 int /*<<< orphan*/  AU1000_MEM_STTIME2 ; 
 int /*<<< orphan*/  AU1000_MEM_STTIME3 ; 
 int /*<<< orphan*/  AU1000_SYS_AUXPLL ; 
 int /*<<< orphan*/  AU1000_SYS_CLKSRC ; 
 int /*<<< orphan*/  AU1000_SYS_CPUPLL ; 
 int /*<<< orphan*/  AU1000_SYS_FREQCTRL0 ; 
 int /*<<< orphan*/  AU1000_SYS_FREQCTRL1 ; 
 int /*<<< orphan*/  AU1000_SYS_PINFUNC ; 
 int /*<<< orphan*/  alchemy_wrsmem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  alchemy_wrsys (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  au1xxx_cpu_has_pll_wo () ; 
 int /*<<< orphan*/ ** sleep_static_memctlr ; 
 int /*<<< orphan*/ * sleep_sys_clocks ; 
 int /*<<< orphan*/  sleep_sys_pinfunc ; 

__attribute__((used)) static void restore_core_regs(void)
{
	/* restore clock configuration.  Writing CPUPLL last will
	 * stall a bit and stabilize other clocks (unless this is
	 * one of those Au1000 with a write-only PLL, where we dont
	 * have a valid value)
	 */
	alchemy_wrsys(sleep_sys_clocks[0], AU1000_SYS_FREQCTRL0);
	alchemy_wrsys(sleep_sys_clocks[1], AU1000_SYS_FREQCTRL1);
	alchemy_wrsys(sleep_sys_clocks[2], AU1000_SYS_CLKSRC);
	alchemy_wrsys(sleep_sys_clocks[4], AU1000_SYS_AUXPLL);
	if (!au1xxx_cpu_has_pll_wo())
		alchemy_wrsys(sleep_sys_clocks[3], AU1000_SYS_CPUPLL);

	alchemy_wrsys(sleep_sys_pinfunc, AU1000_SYS_PINFUNC);

	/* Restore the static memory controller configuration. */
	alchemy_wrsmem(sleep_static_memctlr[0][0], AU1000_MEM_STCFG0);
	alchemy_wrsmem(sleep_static_memctlr[0][1], AU1000_MEM_STTIME0);
	alchemy_wrsmem(sleep_static_memctlr[0][2], AU1000_MEM_STADDR0);
	alchemy_wrsmem(sleep_static_memctlr[1][0], AU1000_MEM_STCFG1);
	alchemy_wrsmem(sleep_static_memctlr[1][1], AU1000_MEM_STTIME1);
	alchemy_wrsmem(sleep_static_memctlr[1][2], AU1000_MEM_STADDR1);
	alchemy_wrsmem(sleep_static_memctlr[2][0], AU1000_MEM_STCFG2);
	alchemy_wrsmem(sleep_static_memctlr[2][1], AU1000_MEM_STTIME2);
	alchemy_wrsmem(sleep_static_memctlr[2][2], AU1000_MEM_STADDR2);
	alchemy_wrsmem(sleep_static_memctlr[3][0], AU1000_MEM_STCFG3);
	alchemy_wrsmem(sleep_static_memctlr[3][1], AU1000_MEM_STTIME3);
	alchemy_wrsmem(sleep_static_memctlr[3][2], AU1000_MEM_STADDR3);
}