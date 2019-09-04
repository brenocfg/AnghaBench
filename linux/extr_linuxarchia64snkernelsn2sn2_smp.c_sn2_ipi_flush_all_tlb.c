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
struct mm_struct {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  shub_ipi_flushes; int /*<<< orphan*/  shub_ipi_flushes_itc_clocks; } ;

/* Variables and functions */
 int /*<<< orphan*/  __this_cpu_add (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  __this_cpu_inc (int /*<<< orphan*/ ) ; 
 unsigned long ia64_get_itc () ; 
 int /*<<< orphan*/ * mm_cpumask (struct mm_struct*) ; 
 TYPE_1__ ptcstats ; 
 int /*<<< orphan*/  smp_flush_tlb_cpumask (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
sn2_ipi_flush_all_tlb(struct mm_struct *mm)
{
	unsigned long itc;

	itc = ia64_get_itc();
	smp_flush_tlb_cpumask(*mm_cpumask(mm));
	itc = ia64_get_itc() - itc;
	__this_cpu_add(ptcstats.shub_ipi_flushes_itc_clocks, itc);
	__this_cpu_inc(ptcstats.shub_ipi_flushes);
}