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
struct stacktrace_ops {int dummy; } ;
struct pt_regs {int dummy; } ;

/* Variables and functions */
 unsigned long __MEMORY_START ; 
 int /*<<< orphan*/  sh64_unwind_inner (struct stacktrace_ops const*,void*,struct pt_regs*) ; 

__attribute__((used)) static inline void unwind_nested(const struct stacktrace_ops *ops, void *data,
				 unsigned long pc, unsigned long fp)
{
	if ((fp >= __MEMORY_START) &&
	    ((fp & 7) == 0))
		sh64_unwind_inner(ops, data, (struct pt_regs *)fp);
}