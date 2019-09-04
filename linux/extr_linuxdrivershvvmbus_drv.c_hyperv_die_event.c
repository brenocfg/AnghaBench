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
struct notifier_block {int dummy; } ;
struct die_args {struct pt_regs* regs; } ;

/* Variables and functions */
 int NOTIFY_DONE ; 
 int /*<<< orphan*/  hyperv_report_panic (struct pt_regs*,unsigned long) ; 

__attribute__((used)) static int hyperv_die_event(struct notifier_block *nb, unsigned long val,
			    void *args)
{
	struct die_args *die = (struct die_args *)args;
	struct pt_regs *regs = die->regs;

	hyperv_report_panic(regs, val);
	return NOTIFY_DONE;
}