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
struct rlimit {unsigned long rlim_max; } ;

/* Variables and functions */
 unsigned long PAGE_ALIGN (scalar_t__) ; 
 unsigned long PAGE_SHIFT ; 
 int /*<<< orphan*/  RLIMIT_STACK ; 
 unsigned long STACK_RND_MASK ; 
 unsigned long STACK_SIZE_MAX ; 
 scalar_t__ STACK_TOP ; 
 unsigned long rlimit_max (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned long mmap_upper_limit(struct rlimit *rlim_stack)
{
	unsigned long stack_base;

	/* Limit stack size - see setup_arg_pages() in fs/exec.c */
	stack_base = rlim_stack ? rlim_stack->rlim_max
				: rlimit_max(RLIMIT_STACK);
	if (stack_base > STACK_SIZE_MAX)
		stack_base = STACK_SIZE_MAX;

	/* Add space for stack randomization. */
	stack_base += (STACK_RND_MASK << PAGE_SHIFT);

	return PAGE_ALIGN(STACK_TOP - stack_base);
}