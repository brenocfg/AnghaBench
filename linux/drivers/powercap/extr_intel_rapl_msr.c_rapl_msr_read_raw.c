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
struct reg_action {int /*<<< orphan*/  mask; int /*<<< orphan*/  value; int /*<<< orphan*/  reg; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ rdmsrl_safe_on_cpu (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rapl_msr_read_raw(int cpu, struct reg_action *ra)
{
	u32 msr = (u32)ra->reg;

	if (rdmsrl_safe_on_cpu(cpu, msr, &ra->value)) {
		pr_debug("failed to read msr 0x%x on cpu %d\n", msr, cpu);
		return -EIO;
	}
	ra->value &= ra->mask;
	return 0;
}