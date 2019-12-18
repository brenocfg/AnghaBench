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
struct intel_gvt_gtt_entry {scalar_t__ type; unsigned long val64; } ;

/* Variables and functions */
 unsigned long ADDR_1G_MASK ; 
 unsigned long ADDR_2M_MASK ; 
 unsigned long ADDR_4K_MASK ; 
 unsigned long ADDR_64K_MASK ; 
 scalar_t__ GTT_TYPE_PPGTT_PTE_1G_ENTRY ; 
 scalar_t__ GTT_TYPE_PPGTT_PTE_2M_ENTRY ; 
 scalar_t__ GTT_TYPE_PPGTT_PTE_64K_ENTRY ; 
 unsigned long PAGE_SHIFT ; 

__attribute__((used)) static void gen8_gtt_set_pfn(struct intel_gvt_gtt_entry *e, unsigned long pfn)
{
	if (e->type == GTT_TYPE_PPGTT_PTE_1G_ENTRY) {
		e->val64 &= ~ADDR_1G_MASK;
		pfn &= (ADDR_1G_MASK >> PAGE_SHIFT);
	} else if (e->type == GTT_TYPE_PPGTT_PTE_2M_ENTRY) {
		e->val64 &= ~ADDR_2M_MASK;
		pfn &= (ADDR_2M_MASK >> PAGE_SHIFT);
	} else if (e->type == GTT_TYPE_PPGTT_PTE_64K_ENTRY) {
		e->val64 &= ~ADDR_64K_MASK;
		pfn &= (ADDR_64K_MASK >> PAGE_SHIFT);
	} else {
		e->val64 &= ~ADDR_4K_MASK;
		pfn &= (ADDR_4K_MASK >> PAGE_SHIFT);
	}

	e->val64 |= (pfn << PAGE_SHIFT);
}