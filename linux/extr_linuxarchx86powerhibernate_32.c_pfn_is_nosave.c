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
 unsigned long PAGE_ALIGN (unsigned long) ; 
 unsigned long PAGE_SHIFT ; 
 int /*<<< orphan*/  __nosave_begin ; 
 int /*<<< orphan*/  __nosave_end ; 
 unsigned long __pa_symbol (int /*<<< orphan*/ *) ; 

int pfn_is_nosave(unsigned long pfn)
{
	unsigned long nosave_begin_pfn = __pa_symbol(&__nosave_begin) >> PAGE_SHIFT;
	unsigned long nosave_end_pfn = PAGE_ALIGN(__pa_symbol(&__nosave_end)) >> PAGE_SHIFT;
	return (pfn >= nosave_begin_pfn) && (pfn < nosave_end_pfn);
}