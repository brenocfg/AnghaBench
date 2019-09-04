#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ shift; } ;

/* Variables and functions */
 size_t MMU_PAGE_64K ; 
 TYPE_1__* mmu_psize_defs ; 

int spu_64k_pages_available(void)
{
	return mmu_psize_defs[MMU_PAGE_64K].shift != 0;
}