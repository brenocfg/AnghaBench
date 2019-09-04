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
struct pt_regs {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  preempt_enable_no_resched () ; 
 int /*<<< orphan*/  rcu_nmi_exit () ; 
 int /*<<< orphan*/  user_mode (struct pt_regs*) ; 

void ist_exit(struct pt_regs *regs)
{
	preempt_enable_no_resched();

	if (!user_mode(regs))
		rcu_nmi_exit();
}