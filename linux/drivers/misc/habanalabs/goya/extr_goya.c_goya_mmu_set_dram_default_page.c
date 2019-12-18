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
typedef  int u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int mmu_dram_default_page_addr; } ;
struct hl_device {TYPE_1__ asic_prop; struct goya_device* asic_specific; } ;
struct goya_device {int hw_cap_initialized; } ;

/* Variables and functions */
 int HW_CAP_MMU ; 
 int /*<<< orphan*/  MMU_DRAM_DEFAULT_PAGE_SIZE ; 
 int goya_memset_device_memory (struct hl_device*,int,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int goya_mmu_set_dram_default_page(struct hl_device *hdev)
{
	struct goya_device *goya = hdev->asic_specific;
	u64 addr = hdev->asic_prop.mmu_dram_default_page_addr;
	u32 size = MMU_DRAM_DEFAULT_PAGE_SIZE;
	u64 val = 0x9999999999999999ull;

	if (!(goya->hw_cap_initialized & HW_CAP_MMU))
		return 0;

	return goya_memset_device_memory(hdev, addr, size, val, true);
}