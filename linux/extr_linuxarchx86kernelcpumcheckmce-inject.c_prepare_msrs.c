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
typedef  int /*<<< orphan*/  u8 ;
struct mce {scalar_t__ inject_flags; int /*<<< orphan*/  misc; int /*<<< orphan*/  addr; int /*<<< orphan*/  status; int /*<<< orphan*/  synd; int /*<<< orphan*/  mcgstatus; int /*<<< orphan*/  bank; } ;

/* Variables and functions */
 scalar_t__ DFR_INT_INJ ; 
 int /*<<< orphan*/  MSR_AMD64_SMCA_MCx_ADDR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MSR_AMD64_SMCA_MCx_DEADDR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MSR_AMD64_SMCA_MCx_DESTAT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MSR_AMD64_SMCA_MCx_MISC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MSR_AMD64_SMCA_MCx_STATUS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MSR_AMD64_SMCA_MCx_SYND (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MSR_IA32_MCG_STATUS ; 
 int /*<<< orphan*/  MSR_IA32_MCx_ADDR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MSR_IA32_MCx_MISC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MSR_IA32_MCx_STATUS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X86_FEATURE_SMCA ; 
 scalar_t__ boot_cpu_has (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wrmsrl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void prepare_msrs(void *info)
{
	struct mce m = *(struct mce *)info;
	u8 b = m.bank;

	wrmsrl(MSR_IA32_MCG_STATUS, m.mcgstatus);

	if (boot_cpu_has(X86_FEATURE_SMCA)) {
		if (m.inject_flags == DFR_INT_INJ) {
			wrmsrl(MSR_AMD64_SMCA_MCx_DESTAT(b), m.status);
			wrmsrl(MSR_AMD64_SMCA_MCx_DEADDR(b), m.addr);
		} else {
			wrmsrl(MSR_AMD64_SMCA_MCx_STATUS(b), m.status);
			wrmsrl(MSR_AMD64_SMCA_MCx_ADDR(b), m.addr);
		}

		wrmsrl(MSR_AMD64_SMCA_MCx_MISC(b), m.misc);
		wrmsrl(MSR_AMD64_SMCA_MCx_SYND(b), m.synd);
	} else {
		wrmsrl(MSR_IA32_MCx_STATUS(b), m.status);
		wrmsrl(MSR_IA32_MCx_ADDR(b), m.addr);
		wrmsrl(MSR_IA32_MCx_MISC(b), m.misc);
	}
}