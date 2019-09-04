#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct stack_frame {unsigned long back_chain; int /*<<< orphan*/ * gprs; } ;
struct TYPE_2__ {int /*<<< orphan*/  addr; } ;
struct pt_regs {unsigned long* gprs; TYPE_1__ psw; } ;
typedef  scalar_t__ (* dump_trace_func_t ) (void*,int /*<<< orphan*/ ,int) ;

/* Variables and functions */
 int /*<<< orphan*/  user_mode (struct pt_regs*) ; 

__attribute__((used)) static unsigned long
__dump_trace(dump_trace_func_t func, void *data, unsigned long sp,
	     unsigned long low, unsigned long high)
{
	struct stack_frame *sf;
	struct pt_regs *regs;

	while (1) {
		if (sp < low || sp > high - sizeof(*sf))
			return sp;
		sf = (struct stack_frame *) sp;
		if (func(data, sf->gprs[8], 0))
			return sp;
		/* Follow the backchain. */
		while (1) {
			low = sp;
			sp = sf->back_chain;
			if (!sp)
				break;
			if (sp <= low || sp > high - sizeof(*sf))
				return sp;
			sf = (struct stack_frame *) sp;
			if (func(data, sf->gprs[8], 1))
				return sp;
		}
		/* Zero backchain detected, check for interrupt frame. */
		sp = (unsigned long) (sf + 1);
		if (sp <= low || sp > high - sizeof(*regs))
			return sp;
		regs = (struct pt_regs *) sp;
		if (!user_mode(regs)) {
			if (func(data, regs->psw.addr, 1))
				return sp;
		}
		low = sp;
		sp = regs->gprs[15];
	}
}