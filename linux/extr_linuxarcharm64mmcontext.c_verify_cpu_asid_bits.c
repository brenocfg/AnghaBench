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
typedef  scalar_t__ u32 ;

/* Variables and functions */
 scalar_t__ asid_bits ; 
 int /*<<< orphan*/  cpu_panic_kernel () ; 
 scalar_t__ get_cpu_asid_bits () ; 
 int /*<<< orphan*/  pr_crit (char*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  smp_processor_id () ; 

void verify_cpu_asid_bits(void)
{
	u32 asid = get_cpu_asid_bits();

	if (asid < asid_bits) {
		/*
		 * We cannot decrease the ASID size at runtime, so panic if we support
		 * fewer ASID bits than the boot CPU.
		 */
		pr_crit("CPU%d: smaller ASID size(%u) than boot CPU (%u)\n",
				smp_processor_id(), asid, asid_bits);
		cpu_panic_kernel();
	}
}