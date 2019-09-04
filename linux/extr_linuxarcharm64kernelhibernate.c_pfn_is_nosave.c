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

/* Variables and functions */
 int /*<<< orphan*/  __nosave_begin ; 
 int /*<<< orphan*/  __nosave_end ; 
 scalar_t__ crash_is_nosave (unsigned long) ; 
 unsigned long sym_to_pfn (int /*<<< orphan*/ *) ; 

int pfn_is_nosave(unsigned long pfn)
{
	unsigned long nosave_begin_pfn = sym_to_pfn(&__nosave_begin);
	unsigned long nosave_end_pfn = sym_to_pfn(&__nosave_end - 1);

	return ((pfn >= nosave_begin_pfn) && (pfn <= nosave_end_pfn)) ||
		crash_is_nosave(pfn);
}