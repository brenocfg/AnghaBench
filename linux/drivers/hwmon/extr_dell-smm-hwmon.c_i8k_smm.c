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
struct smm_regs {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_online_cpus () ; 
 int /*<<< orphan*/  i8k_smm_func ; 
 int /*<<< orphan*/  put_online_cpus () ; 
 int smp_call_on_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct smm_regs*,int) ; 

__attribute__((used)) static int i8k_smm(struct smm_regs *regs)
{
	int ret;

	get_online_cpus();
	ret = smp_call_on_cpu(0, i8k_smm_func, regs, true);
	put_online_cpus();

	return ret;
}