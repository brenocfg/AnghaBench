#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  int /*<<< orphan*/  mce_banks_t ;
typedef  enum mcp_flags { ____Placeholder_mcp_flags } mcp_flags ;
struct TYPE_2__ {int /*<<< orphan*/  bootlog; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_NR_BANKS ; 
 int MCG_CTL_P ; 
 int MCP_DONTLOG ; 
 int MCP_UC ; 
 int /*<<< orphan*/  MSR_IA32_MCG_CAP ; 
 int /*<<< orphan*/  MSR_IA32_MCG_CTL ; 
 int /*<<< orphan*/  X86_CR4_MCE ; 
 int /*<<< orphan*/  bitmap_fill (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cr4_set_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  machine_check_poll (int,int /*<<< orphan*/ *) ; 
 TYPE_1__ mca_cfg ; 
 int /*<<< orphan*/  rdmsrl (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wrmsr (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void __mcheck_cpu_init_generic(void)
{
	enum mcp_flags m_fl = 0;
	mce_banks_t all_banks;
	u64 cap;

	if (!mca_cfg.bootlog)
		m_fl = MCP_DONTLOG;

	/*
	 * Log the machine checks left over from the previous reset.
	 */
	bitmap_fill(all_banks, MAX_NR_BANKS);
	machine_check_poll(MCP_UC | m_fl, &all_banks);

	cr4_set_bits(X86_CR4_MCE);

	rdmsrl(MSR_IA32_MCG_CAP, cap);
	if (cap & MCG_CTL_P)
		wrmsr(MSR_IA32_MCG_CTL, 0xffffffff, 0xffffffff);
}