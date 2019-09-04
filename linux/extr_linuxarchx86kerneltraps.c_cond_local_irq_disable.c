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
struct pt_regs {int flags; } ;

/* Variables and functions */
 int X86_EFLAGS_IF ; 
 int /*<<< orphan*/  local_irq_disable () ; 

__attribute__((used)) static inline void cond_local_irq_disable(struct pt_regs *regs)
{
	if (regs->flags & X86_EFLAGS_IF)
		local_irq_disable();
}