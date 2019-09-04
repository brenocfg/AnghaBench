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
 unsigned long DIV_ROUND_UP (unsigned long,unsigned long) ; 
 unsigned long PAGE_MASK ; 
 unsigned long PAGE_SHIFT ; 
 unsigned long PAGE_SIZE ; 
 unsigned long VMW_PPN_SIZE ; 
 scalar_t__ likely (int) ; 

__attribute__((used)) static unsigned long vmw_mob_calculate_pt_pages(unsigned long data_pages)
{
	unsigned long data_size = data_pages * PAGE_SIZE;
	unsigned long tot_size = 0;

	while (likely(data_size > PAGE_SIZE)) {
		data_size = DIV_ROUND_UP(data_size, PAGE_SIZE);
		data_size *= VMW_PPN_SIZE;
		tot_size += (data_size + PAGE_SIZE - 1) & PAGE_MASK;
	}

	return tot_size >> PAGE_SHIFT;
}