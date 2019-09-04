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
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 unsigned long PAGE_ALIGN (unsigned long) ; 
 unsigned long PAGE_SIZE ; 
 int PF_RANDOMIZE ; 
 unsigned long STACK_TOP ; 
 int VDSO_RANDOMIZE_SIZE ; 
 TYPE_1__* current ; 
 int get_random_int () ; 

__attribute__((used)) static unsigned long vdso_base(void)
{
	unsigned long base;

	/* Skip the delay slot emulation page */
	base = STACK_TOP + PAGE_SIZE;

	if (current->flags & PF_RANDOMIZE) {
		base += get_random_int() & (VDSO_RANDOMIZE_SIZE - 1);
		base = PAGE_ALIGN(base);
	}

	return base;
}