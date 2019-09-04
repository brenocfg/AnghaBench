#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int flags; } ;
struct TYPE_3__ {int flags; unsigned long mask; } ;

/* Variables and functions */
 int PF_RANDOMIZE ; 
 TYPE_2__* current ; 
 int mmap_is_ia32 () ; 
 TYPE_1__ va_align ; 

__attribute__((used)) static unsigned long get_align_mask(void)
{
	/* handle 32- and 64-bit case with a single conditional */
	if (va_align.flags < 0 || !(va_align.flags & (2 - mmap_is_ia32())))
		return 0;

	if (!(current->flags & PF_RANDOMIZE))
		return 0;

	return va_align.mask;
}