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
struct TYPE_2__ {unsigned int banks; int ser; int /*<<< orphan*/  rip_msr; } ;

/* Variables and functions */
 unsigned int MAX_NR_BANKS ; 
 int MCG_BANKCNT_MASK ; 
 int MCG_EXT_CNT (int) ; 
 int MCG_EXT_P ; 
 int MCG_SER_P ; 
 int /*<<< orphan*/  MSR_IA32_MCG_CAP ; 
 int /*<<< orphan*/  MSR_IA32_MCG_EIP ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int __mcheck_cpu_mce_banks_init () ; 
 TYPE_1__ mca_cfg ; 
 int /*<<< orphan*/  mce_banks ; 
 int /*<<< orphan*/  pr_info (char*,unsigned int) ; 
 int /*<<< orphan*/  pr_warn (char*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  rdmsrl (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int __mcheck_cpu_cap_init(void)
{
	unsigned b;
	u64 cap;

	rdmsrl(MSR_IA32_MCG_CAP, cap);

	b = cap & MCG_BANKCNT_MASK;
	if (!mca_cfg.banks)
		pr_info("CPU supports %d MCE banks\n", b);

	if (b > MAX_NR_BANKS) {
		pr_warn("Using only %u machine check banks out of %u\n",
			MAX_NR_BANKS, b);
		b = MAX_NR_BANKS;
	}

	/* Don't support asymmetric configurations today */
	WARN_ON(mca_cfg.banks != 0 && b != mca_cfg.banks);
	mca_cfg.banks = b;

	if (!mce_banks) {
		int err = __mcheck_cpu_mce_banks_init();

		if (err)
			return err;
	}

	/* Use accurate RIP reporting if available. */
	if ((cap & MCG_EXT_P) && MCG_EXT_CNT(cap) >= 9)
		mca_cfg.rip_msr = MSR_IA32_MCG_EIP;

	if (cap & MCG_SER_P)
		mca_cfg.ser = 1;

	return 0;
}