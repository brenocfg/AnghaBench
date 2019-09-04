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
 unsigned long L1_CACHE_BYTES ; 
 int /*<<< orphan*/  __flush_wback_region (void*,unsigned long) ; 
 int /*<<< orphan*/  sh64_icache_inv_current_user_range (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void sh5_flush_cache_sigtramp(void *vaddr)
{
	unsigned long end = (unsigned long)vaddr + L1_CACHE_BYTES;

	__flush_wback_region(vaddr, L1_CACHE_BYTES);
	wmb();
	sh64_icache_inv_current_user_range((unsigned long)vaddr, end);
}