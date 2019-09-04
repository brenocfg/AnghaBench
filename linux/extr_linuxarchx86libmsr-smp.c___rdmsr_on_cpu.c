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
struct msr {int /*<<< orphan*/  h; int /*<<< orphan*/  l; } ;
struct msr_info {int /*<<< orphan*/  msr_no; struct msr reg; scalar_t__ msrs; } ;

/* Variables and functions */
 struct msr* per_cpu_ptr (scalar_t__,int) ; 
 int raw_smp_processor_id () ; 
 int /*<<< orphan*/  rdmsr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __rdmsr_on_cpu(void *info)
{
	struct msr_info *rv = info;
	struct msr *reg;
	int this_cpu = raw_smp_processor_id();

	if (rv->msrs)
		reg = per_cpu_ptr(rv->msrs, this_cpu);
	else
		reg = &rv->reg;

	rdmsr(rv->msr_no, reg->l, reg->h);
}