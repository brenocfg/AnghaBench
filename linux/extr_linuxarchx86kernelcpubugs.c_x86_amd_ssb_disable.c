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
typedef  int u64 ;

/* Variables and functions */
 int /*<<< orphan*/  MSR_AMD64_LS_CFG ; 
 int /*<<< orphan*/  MSR_AMD64_VIRT_SPEC_CTRL ; 
 int SPEC_CTRL_SSBD ; 
 int /*<<< orphan*/  X86_FEATURE_LS_CFG_SSBD ; 
 int /*<<< orphan*/  X86_FEATURE_VIRT_SSBD ; 
 scalar_t__ boot_cpu_has (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wrmsrl (int /*<<< orphan*/ ,int) ; 
 int x86_amd_ls_cfg_base ; 
 int x86_amd_ls_cfg_ssbd_mask ; 

__attribute__((used)) static void x86_amd_ssb_disable(void)
{
	u64 msrval = x86_amd_ls_cfg_base | x86_amd_ls_cfg_ssbd_mask;

	if (boot_cpu_has(X86_FEATURE_VIRT_SSBD))
		wrmsrl(MSR_AMD64_VIRT_SPEC_CTRL, SPEC_CTRL_SSBD);
	else if (boot_cpu_has(X86_FEATURE_LS_CFG_SSBD))
		wrmsrl(MSR_AMD64_LS_CFG, msrval);
}