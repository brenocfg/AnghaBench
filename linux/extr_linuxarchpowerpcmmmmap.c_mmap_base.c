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
struct rlimit {unsigned long rlim_cur; } ;

/* Variables and functions */
 unsigned long DEFAULT_MAP_WINDOW ; 
 unsigned long MAX_GAP ; 
 unsigned long MIN_GAP ; 
 unsigned long PAGE_ALIGN (unsigned long) ; 
 unsigned long stack_guard_gap ; 
 unsigned long stack_maxrandom_size () ; 

__attribute__((used)) static inline unsigned long mmap_base(unsigned long rnd,
				      struct rlimit *rlim_stack)
{
	unsigned long gap = rlim_stack->rlim_cur;
	unsigned long pad = stack_maxrandom_size() + stack_guard_gap;

	/* Values close to RLIM_INFINITY can overflow. */
	if (gap + pad > gap)
		gap += pad;

	if (gap < MIN_GAP)
		gap = MIN_GAP;
	else if (gap > MAX_GAP)
		gap = MAX_GAP;

	return PAGE_ALIGN(DEFAULT_MAP_WINDOW - gap - rnd);
}