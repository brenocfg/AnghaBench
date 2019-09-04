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
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  flush_tlb_kernel_range_common (unsigned long,scalar_t__) ; 

void __flush_tlb_one(unsigned long addr)
{
	flush_tlb_kernel_range_common(addr, addr + PAGE_SIZE);
}