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
typedef  int /*<<< orphan*/  u32 ;
struct msr_regs_info {int err; int /*<<< orphan*/ * regs; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  __rdmsr_safe_regs_on_cpu ; 
 int smp_call_function_single (unsigned int,int /*<<< orphan*/ ,struct msr_regs_info*,int) ; 

int rdmsr_safe_regs_on_cpu(unsigned int cpu, u32 *regs)
{
	int err;
	struct msr_regs_info rv;

	rv.regs   = regs;
	rv.err    = -EIO;
	err = smp_call_function_single(cpu, __rdmsr_safe_regs_on_cpu, &rv, 1);

	return err ? err : rv.err;
}