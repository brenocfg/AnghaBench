#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct task_struct {int dummy; } ;
struct pt_regs {int dummy; } ;
struct TYPE_5__ {int reset_ovfl_pmds; } ;
struct TYPE_6__ {TYPE_1__ bits; } ;
struct TYPE_7__ {int pmd_eventid; TYPE_2__ ovfl_ctrl; } ;
typedef  TYPE_3__ pfm_ovfl_arg_t ;

/* Variables and functions */
 scalar_t__ allow_ints ; 
 int /*<<< orphan*/  oprofile_add_sample (struct pt_regs*,int) ; 

__attribute__((used)) static int
perfmon_handler(struct task_struct *task, void *buf, pfm_ovfl_arg_t *arg,
                struct pt_regs *regs, unsigned long stamp)
{
	int event = arg->pmd_eventid;
 
	arg->ovfl_ctrl.bits.reset_ovfl_pmds = 1;

	/* the owner of the oprofile event buffer may have exited
	 * without perfmon being shutdown (e.g. SIGSEGV)
	 */
	if (allow_ints)
		oprofile_add_sample(regs, event);
	return 0;
}