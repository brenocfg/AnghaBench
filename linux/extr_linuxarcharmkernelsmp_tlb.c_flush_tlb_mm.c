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
struct mm_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __flush_tlb_mm (struct mm_struct*) ; 
 int /*<<< orphan*/  broadcast_tlb_mm_a15_erratum (struct mm_struct*) ; 
 int /*<<< orphan*/  ipi_flush_tlb_mm ; 
 int /*<<< orphan*/  mm_cpumask (struct mm_struct*) ; 
 int /*<<< orphan*/  on_each_cpu_mask (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mm_struct*,int) ; 
 scalar_t__ tlb_ops_need_broadcast () ; 

void flush_tlb_mm(struct mm_struct *mm)
{
	if (tlb_ops_need_broadcast())
		on_each_cpu_mask(mm_cpumask(mm), ipi_flush_tlb_mm, mm, 1);
	else
		__flush_tlb_mm(mm);
	broadcast_tlb_mm_a15_erratum(mm);
}