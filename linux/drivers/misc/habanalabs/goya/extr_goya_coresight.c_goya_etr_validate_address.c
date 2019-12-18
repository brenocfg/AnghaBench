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
typedef  int /*<<< orphan*/  u32 ;
struct asic_fixed_properties {int /*<<< orphan*/  dram_end_address; int /*<<< orphan*/  dram_user_base_address; int /*<<< orphan*/  va_space_dram_end_address; int /*<<< orphan*/  va_space_dram_start_address; } ;
struct hl_device {scalar_t__ mmu_enable; struct asic_fixed_properties asic_prop; } ;

/* Variables and functions */
 int hl_mem_area_inside_range (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int goya_etr_validate_address(struct hl_device *hdev, u64 addr,
		u32 size)
{
	struct asic_fixed_properties *prop = &hdev->asic_prop;
	u64 range_start, range_end;

	if (hdev->mmu_enable) {
		range_start = prop->va_space_dram_start_address;
		range_end = prop->va_space_dram_end_address;
	} else {
		range_start = prop->dram_user_base_address;
		range_end = prop->dram_end_address;
	}

	return hl_mem_area_inside_range(addr, size, range_start, range_end);
}