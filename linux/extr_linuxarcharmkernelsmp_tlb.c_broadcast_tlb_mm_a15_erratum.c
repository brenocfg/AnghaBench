#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct mm_struct {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ cpumask_t ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_BITS_NONE ; 
 int /*<<< orphan*/  a15_erratum_get_cpumask (int,struct mm_struct*,TYPE_1__*) ; 
 int /*<<< orphan*/  erratum_a15_798181 () ; 
 int get_cpu () ; 
 int /*<<< orphan*/  ipi_flush_tlb_a15_erratum ; 
 int /*<<< orphan*/  put_cpu () ; 
 int /*<<< orphan*/  smp_call_function_many (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void broadcast_tlb_mm_a15_erratum(struct mm_struct *mm)
{
	int this_cpu;
	cpumask_t mask = { CPU_BITS_NONE };

	if (!erratum_a15_798181())
		return;

	this_cpu = get_cpu();
	a15_erratum_get_cpumask(this_cpu, mm, &mask);
	smp_call_function_many(&mask, ipi_flush_tlb_a15_erratum, NULL, 1);
	put_cpu();
}