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
 int /*<<< orphan*/  PAGE_NONE ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  cea_set_pte (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_tlb_kernel_range (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 

__attribute__((used)) static void ds_clear_cea(void *cea, size_t size)
{
	unsigned long start = (unsigned long)cea;
	size_t msz = 0;

	preempt_disable();
	for (; msz < size; msz += PAGE_SIZE, cea += PAGE_SIZE)
		cea_set_pte(cea, 0, PAGE_NONE);

	flush_tlb_kernel_range(start, start + size);
	preempt_enable();
}