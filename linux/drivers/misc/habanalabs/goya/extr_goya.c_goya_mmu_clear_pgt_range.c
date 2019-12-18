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
typedef  int /*<<< orphan*/  u64 ;
typedef  scalar_t__ u32 ;
struct asic_fixed_properties {scalar_t__ mmu_pgt_size; int /*<<< orphan*/  mmu_pgt_addr; } ;
struct hl_device {struct goya_device* asic_specific; struct asic_fixed_properties asic_prop; } ;
struct goya_device {int hw_cap_initialized; } ;

/* Variables and functions */
 int HW_CAP_MMU ; 
 scalar_t__ MMU_CACHE_MNG_SIZE ; 
 scalar_t__ MMU_DRAM_DEFAULT_PAGE_SIZE ; 
 int goya_memset_device_memory (struct hl_device*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int goya_mmu_clear_pgt_range(struct hl_device *hdev)
{
	struct asic_fixed_properties *prop = &hdev->asic_prop;
	struct goya_device *goya = hdev->asic_specific;
	u64 addr = prop->mmu_pgt_addr;
	u32 size = prop->mmu_pgt_size + MMU_DRAM_DEFAULT_PAGE_SIZE +
			MMU_CACHE_MNG_SIZE;

	if (!(goya->hw_cap_initialized & HW_CAP_MMU))
		return 0;

	return goya_memset_device_memory(hdev, addr, size, 0, true);
}