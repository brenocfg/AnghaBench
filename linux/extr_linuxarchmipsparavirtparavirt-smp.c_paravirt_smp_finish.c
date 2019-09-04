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
 int HZ ; 
 int /*<<< orphan*/  local_irq_enable () ; 
 int mips_hpt_frequency ; 
 scalar_t__ read_c0_count () ; 
 int /*<<< orphan*/  write_c0_compare (scalar_t__) ; 

__attribute__((used)) static void paravirt_smp_finish(void)
{
	/* to generate the first CPU timer interrupt */
	write_c0_compare(read_c0_count() + mips_hpt_frequency / HZ);
	local_irq_enable();
}