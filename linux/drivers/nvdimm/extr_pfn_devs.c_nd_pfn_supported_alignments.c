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
 int /*<<< orphan*/  CONFIG_HAVE_ARCH_TRANSPARENT_HUGEPAGE_PUD ; 
 unsigned long HPAGE_PMD_SIZE ; 
 unsigned long HPAGE_PUD_SIZE ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 unsigned long PAGE_SIZE ; 
 scalar_t__ has_transparent_hugepage () ; 

__attribute__((used)) static unsigned long *nd_pfn_supported_alignments(unsigned long *alignments)
{

	alignments[0] = PAGE_SIZE;

	if (has_transparent_hugepage()) {
		alignments[1] = HPAGE_PMD_SIZE;
		if (IS_ENABLED(CONFIG_HAVE_ARCH_TRANSPARENT_HUGEPAGE_PUD))
			alignments[2] = HPAGE_PUD_SIZE;
	}

	return alignments;
}