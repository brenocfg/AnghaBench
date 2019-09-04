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
 unsigned long MMAP_RND_MASK ; 
 unsigned long PAGE_SHIFT ; 
 int PF_RANDOMIZE ; 
 TYPE_1__* current ; 
 unsigned long get_random_int () ; 

__attribute__((used)) static unsigned long mmap_rnd(void)
{
	unsigned long rnd = 0;

	if (current->flags & PF_RANDOMIZE)
		rnd = get_random_int() & MMAP_RND_MASK;

	return rnd << PAGE_SHIFT;
}