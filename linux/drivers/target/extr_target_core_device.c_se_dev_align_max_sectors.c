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
typedef  scalar_t__ u32 ;

/* Variables and functions */
 scalar_t__ PAGE_SIZE ; 
 scalar_t__ max (unsigned long,scalar_t__) ; 
 int /*<<< orphan*/  pr_info (char*,scalar_t__,scalar_t__) ; 
 scalar_t__ rounddown (scalar_t__,scalar_t__) ; 

__attribute__((used)) static u32 se_dev_align_max_sectors(u32 max_sectors, u32 block_size)
{
	u32 aligned_max_sectors;
	u32 alignment;
	/*
	 * Limit max_sectors to a PAGE_SIZE aligned value for modern
	 * transport_allocate_data_tasks() operation.
	 */
	alignment = max(1ul, PAGE_SIZE / block_size);
	aligned_max_sectors = rounddown(max_sectors, alignment);

	if (max_sectors != aligned_max_sectors)
		pr_info("Rounding down aligned max_sectors from %u to %u\n",
			max_sectors, aligned_max_sectors);

	return aligned_max_sectors;
}