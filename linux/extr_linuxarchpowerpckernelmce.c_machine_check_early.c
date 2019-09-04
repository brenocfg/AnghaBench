#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pt_regs {int dummy; } ;
struct TYPE_4__ {long (* machine_check_early ) (struct pt_regs*) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  mce_exceptions; } ;

/* Variables and functions */
 int /*<<< orphan*/  __this_cpu_inc (int /*<<< orphan*/ ) ; 
 TYPE_2__* cur_cpu_spec ; 
 TYPE_1__ irq_stat ; 
 long stub1 (struct pt_regs*) ; 

long machine_check_early(struct pt_regs *regs)
{
	long handled = 0;

	__this_cpu_inc(irq_stat.mce_exceptions);

	if (cur_cpu_spec && cur_cpu_spec->machine_check_early)
		handled = cur_cpu_spec->machine_check_early(regs);
	return handled;
}