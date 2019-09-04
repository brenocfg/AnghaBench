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
 int /*<<< orphan*/  alchemy_rdsmem (int /*<<< orphan*/ ) ; 
 void* alchemy_rdsys (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ ** sleep_static_memctlr ; 
 void** sleep_sys_clocks ; 
 void* sleep_sys_pinfunc ; 

__attribute__((used)) static void save_core_regs(void)
{
	/* Clocks and PLLs. */
	sleep_sys_clocks[0] = alchemy_rdsys(AU1000_SYS_FREQCTRL0);
	sleep_sys_clocks[1] = alchemy_rdsys(AU1000_SYS_FREQCTRL1);
	sleep_sys_clocks[2] = alchemy_rdsys(AU1000_SYS_CLKSRC);
	sleep_sys_clocks[3] = alchemy_rdsys(AU1000_SYS_CPUPLL);
	sleep_sys_clocks[4] = alchemy_rdsys(AU1000_SYS_AUXPLL);

	/* pin mux config */
	sleep_sys_pinfunc = alchemy_rdsys(AU1000_SYS_PINFUNC);

	/* Save the static memory controller configuration. */
	sleep_static_memctlr[0][0] = alchemy_rdsmem(AU1000_MEM_STCFG0);
	sleep_static_memctlr[0][1] = alchemy_rdsmem(AU1000_MEM_STTIME0);
	sleep_static_memctlr[0][2] = alchemy_rdsmem(AU1000_MEM_STADDR0);
	sleep_static_memctlr[1][0] = alchemy_rdsmem(AU1000_MEM_STCFG1);
	sleep_static_memctlr[1][1] = alchemy_rdsmem(AU1000_MEM_STTIME1);
	sleep_static_memctlr[1][2] = alchemy_rdsmem(AU1000_MEM_STADDR1);
	sleep_static_memctlr[2][0] = alchemy_rdsmem(AU1000_MEM_STCFG2);
	sleep_static_memctlr[2][1] = alchemy_rdsmem(AU1000_MEM_STTIME2);
	sleep_static_memctlr[2][2] = alchemy_rdsmem(AU1000_MEM_STADDR2);
	sleep_static_memctlr[3][0] = alchemy_rdsmem(AU1000_MEM_STCFG3);
	sleep_static_memctlr[3][1] = alchemy_rdsmem(AU1000_MEM_STTIME3);
	sleep_static_memctlr[3][2] = alchemy_rdsmem(AU1000_MEM_STADDR3);
}