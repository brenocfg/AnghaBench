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
typedef  int uint32_t ;
struct psb_mmu_pd {int /*<<< orphan*/  p; } ;
struct psb_mmu_driver {int dummy; } ;

/* Variables and functions */
 int PAGE_SHIFT ; 
 int page_to_pfn (int /*<<< orphan*/ ) ; 
 struct psb_mmu_pd* psb_mmu_get_default_pd (struct psb_mmu_driver*) ; 

uint32_t psb_get_default_pd_addr(struct psb_mmu_driver *driver)
{
	struct psb_mmu_pd *pd;

	pd = psb_mmu_get_default_pd(driver);
	return page_to_pfn(pd->p) << PAGE_SHIFT;
}