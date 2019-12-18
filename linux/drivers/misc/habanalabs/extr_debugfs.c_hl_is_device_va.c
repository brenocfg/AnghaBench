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
typedef  scalar_t__ u64 ;
struct asic_fixed_properties {scalar_t__ va_space_dram_start_address; scalar_t__ va_space_dram_end_address; scalar_t__ va_space_host_start_address; scalar_t__ va_space_host_end_address; } ;
struct hl_device {scalar_t__ dram_supports_virtual_memory; int /*<<< orphan*/  mmu_enable; struct asic_fixed_properties asic_prop; } ;

/* Variables and functions */

__attribute__((used)) static bool hl_is_device_va(struct hl_device *hdev, u64 addr)
{
	struct asic_fixed_properties *prop = &hdev->asic_prop;

	if (!hdev->mmu_enable)
		goto out;

	if (hdev->dram_supports_virtual_memory &&
			addr >= prop->va_space_dram_start_address &&
			addr < prop->va_space_dram_end_address)
		return true;

	if (addr >= prop->va_space_host_start_address &&
			addr < prop->va_space_host_end_address)
		return true;
out:
	return false;
}