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
 int CM_GCR_GIC_STATUS_EX ; 
 int ENODEV ; 
 int /*<<< orphan*/  cps_smp_ops ; 
 int /*<<< orphan*/  mips_cm_present () ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 int read_gcr_gic_status () ; 
 int /*<<< orphan*/  register_smp_ops (int /*<<< orphan*/ *) ; 

int register_cps_smp_ops(void)
{
	if (!mips_cm_present()) {
		pr_warn("MIPS CPS SMP unable to proceed without a CM\n");
		return -ENODEV;
	}

	/* check we have a GIC - we need one for IPIs */
	if (!(read_gcr_gic_status() & CM_GCR_GIC_STATUS_EX)) {
		pr_warn("MIPS CPS SMP unable to proceed without a GIC\n");
		return -ENODEV;
	}

	register_smp_ops(&cps_smp_ops);
	return 0;
}