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
typedef  scalar_t__ u64 ;
struct asic_fixed_properties {int max_asid; int mmu_hop_table_size; scalar_t__ mmu_pgt_addr; } ;
struct hl_device {int dram_supports_virtual_memory; int dram_default_page_mapping; TYPE_1__* asic_funcs; int /*<<< orphan*/  dev; int /*<<< orphan*/  mmu_enable; struct goya_device* asic_specific; struct asic_fixed_properties asic_prop; } ;
struct goya_device {int hw_cap_initialized; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* mmu_invalidate_cache ) (struct hl_device*,int) ;} ;

/* Variables and functions */
 int HW_CAP_MMU ; 
 int MMU_CACHE_MNG_ADDR ; 
 int /*<<< orphan*/  STLB_STLB_FEATURE_EN_FOLLOWER_EN_MASK ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WREG32_AND (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int goya_mmu_update_asid_hop0_addr (struct hl_device*,int,scalar_t__) ; 
 int lower_32_bits (int) ; 
 int /*<<< orphan*/  mmMMU_MMU_ENABLE ; 
 int /*<<< orphan*/  mmMMU_SPI_MASK ; 
 int /*<<< orphan*/  mmSTLB_CACHE_INV_BASE_39_8 ; 
 int /*<<< orphan*/  mmSTLB_CACHE_INV_BASE_49_40 ; 
 int /*<<< orphan*/  mmSTLB_STLB_FEATURE_EN ; 
 int /*<<< orphan*/  stub1 (struct hl_device*,int) ; 

int goya_mmu_init(struct hl_device *hdev)
{
	struct asic_fixed_properties *prop = &hdev->asic_prop;
	struct goya_device *goya = hdev->asic_specific;
	u64 hop0_addr;
	int rc, i;

	if (!hdev->mmu_enable)
		return 0;

	if (goya->hw_cap_initialized & HW_CAP_MMU)
		return 0;

	hdev->dram_supports_virtual_memory = true;
	hdev->dram_default_page_mapping = true;

	for (i = 0 ; i < prop->max_asid ; i++) {
		hop0_addr = prop->mmu_pgt_addr +
				(i * prop->mmu_hop_table_size);

		rc = goya_mmu_update_asid_hop0_addr(hdev, i, hop0_addr);
		if (rc) {
			dev_err(hdev->dev,
				"failed to set hop0 addr for asid %d\n", i);
			goto err;
		}
	}

	goya->hw_cap_initialized |= HW_CAP_MMU;

	/* init MMU cache manage page */
	WREG32(mmSTLB_CACHE_INV_BASE_39_8,
				lower_32_bits(MMU_CACHE_MNG_ADDR >> 8));
	WREG32(mmSTLB_CACHE_INV_BASE_49_40, MMU_CACHE_MNG_ADDR >> 40);

	/* Remove follower feature due to performance bug */
	WREG32_AND(mmSTLB_STLB_FEATURE_EN,
			(~STLB_STLB_FEATURE_EN_FOLLOWER_EN_MASK));

	hdev->asic_funcs->mmu_invalidate_cache(hdev, true);

	WREG32(mmMMU_MMU_ENABLE, 1);
	WREG32(mmMMU_SPI_MASK, 0xF);

	return 0;

err:
	return rc;
}