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
typedef  size_t u32 ;
struct ath10k_mem_region {scalar_t__ len; } ;
struct TYPE_2__ {int size; struct ath10k_mem_region* regions; } ;
struct ath10k_hw_mem_layout {TYPE_1__ region_table; } ;
struct ath10k_dump_ram_data_hdr {int dummy; } ;
struct ath10k {int dummy; } ;

/* Variables and functions */
 size_t ALIGN (size_t,int) ; 
 struct ath10k_hw_mem_layout* ath10k_coredump_get_mem_layout (struct ath10k*) ; 

__attribute__((used)) static u32 ath10k_coredump_get_ramdump_size(struct ath10k *ar)
{
	const struct ath10k_hw_mem_layout *hw;
	const struct ath10k_mem_region *mem_region;
	size_t size = 0;
	int i;

	hw = ath10k_coredump_get_mem_layout(ar);

	if (!hw)
		return 0;

	mem_region = &hw->region_table.regions[0];

	for (i = 0; i < hw->region_table.size; i++) {
		size += mem_region->len;
		mem_region++;
	}

	/* reserve space for the headers */
	size += hw->region_table.size * sizeof(struct ath10k_dump_ram_data_hdr);

	/* make sure it is aligned 16 bytes for debug message print out */
	size = ALIGN(size, 16);

	return size;
}