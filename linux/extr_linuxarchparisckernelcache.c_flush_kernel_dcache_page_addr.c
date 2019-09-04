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
 int /*<<< orphan*/  flush_kernel_dcache_page_asm (void*) ; 
 int /*<<< orphan*/  pdtlb_kernel (void*) ; 
 int /*<<< orphan*/  purge_tlb_end (unsigned long) ; 
 int /*<<< orphan*/  purge_tlb_start (unsigned long) ; 

void flush_kernel_dcache_page_addr(void *addr)
{
	unsigned long flags;

	flush_kernel_dcache_page_asm(addr);
	purge_tlb_start(flags);
	pdtlb_kernel(addr);
	purge_tlb_end(flags);
}