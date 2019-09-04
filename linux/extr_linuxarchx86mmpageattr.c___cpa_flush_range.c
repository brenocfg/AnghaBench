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
 int /*<<< orphan*/  __flush_tlb_all () ; 

__attribute__((used)) static void __cpa_flush_range(void *arg)
{
	/*
	 * We could optimize that further and do individual per page
	 * tlb invalidates for a low number of pages. Caveat: we must
	 * flush the high aliases on 64bit as well.
	 */
	__flush_tlb_all();
}