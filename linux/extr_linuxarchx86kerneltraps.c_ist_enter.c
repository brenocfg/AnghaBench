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
 int /*<<< orphan*/  RCU_LOCKDEP_WARN (int,char*) ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  rcu_is_watching () ; 
 int /*<<< orphan*/  rcu_nmi_enter () ; 
 scalar_t__ user_mode (struct pt_regs*) ; 

void ist_enter(struct pt_regs *regs)
{
	if (user_mode(regs)) {
		RCU_LOCKDEP_WARN(!rcu_is_watching(), "entry code didn't wake RCU");
	} else {
		/*
		 * We might have interrupted pretty much anything.  In
		 * fact, if we're a machine check, we can even interrupt
		 * NMI processing.  We don't want in_nmi() to return true,
		 * but we need to notify RCU.
		 */
		rcu_nmi_enter();
	}

	preempt_disable();

	/* This code is a bit fragile.  Test it. */
	RCU_LOCKDEP_WARN(!rcu_is_watching(), "ist_enter didn't work");
}