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
 unsigned long HPAGE_PMD_SIZE ; 
 unsigned long PAGE_SIZE ; 
 scalar_t__ has_transparent_hugepage () ; 

__attribute__((used)) static unsigned long nd_pfn_default_alignment(void)
{

	if (has_transparent_hugepage())
		return HPAGE_PMD_SIZE;
	return PAGE_SIZE;
}