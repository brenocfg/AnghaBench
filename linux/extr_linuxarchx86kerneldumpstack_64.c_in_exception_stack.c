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
struct stack_info {unsigned long* begin; unsigned long* end; unsigned long* next_sp; scalar_t__ type; } ;
struct pt_regs {scalar_t__ sp; } ;
struct TYPE_2__ {scalar_t__* ist; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int N_EXCEPTION_STACKS ; 
 scalar_t__ STACK_TYPE_EXCEPTION ; 
 int* exception_stack_sizes ; 
 int /*<<< orphan*/  orig_ist ; 
 TYPE_1__* raw_cpu_ptr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool in_exception_stack(unsigned long *stack, struct stack_info *info)
{
	unsigned long *begin, *end;
	struct pt_regs *regs;
	unsigned k;

	BUILD_BUG_ON(N_EXCEPTION_STACKS != 4);

	for (k = 0; k < N_EXCEPTION_STACKS; k++) {
		end   = (unsigned long *)raw_cpu_ptr(&orig_ist)->ist[k];
		begin = end - (exception_stack_sizes[k] / sizeof(long));
		regs  = (struct pt_regs *)end - 1;

		if (stack <= begin || stack >= end)
			continue;

		info->type	= STACK_TYPE_EXCEPTION + k;
		info->begin	= begin;
		info->end	= end;
		info->next_sp	= (unsigned long *)regs->sp;

		return true;
	}

	return false;
}