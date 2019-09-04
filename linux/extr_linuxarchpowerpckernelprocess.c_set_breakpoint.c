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
struct arch_hw_breakpoint {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __set_breakpoint (struct arch_hw_breakpoint*) ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 

__attribute__((used)) static void set_breakpoint(struct arch_hw_breakpoint *brk)
{
	preempt_disable();
	__set_breakpoint(brk);
	preempt_enable();
}