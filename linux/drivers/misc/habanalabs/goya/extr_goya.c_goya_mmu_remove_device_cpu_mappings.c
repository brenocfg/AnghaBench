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
struct asic_fixed_properties {scalar_t__ dram_base_address; } ;
struct hl_device {int cpu_accessible_dma_address; int /*<<< orphan*/  dev; int /*<<< orphan*/  kernel_ctx; struct goya_device* asic_specific; struct asic_fixed_properties asic_prop; } ;
struct goya_device {int hw_cap_initialized; int device_cpu_mmu_mappings_done; } ;

/* Variables and functions */
 scalar_t__ CPU_FW_IMAGE_SIZE ; 
 int HW_CAP_MMU ; 
 int PAGE_SIZE_2MB ; 
 int PAGE_SIZE_4KB ; 
 scalar_t__ SZ_2M ; 
 scalar_t__ VA_CPU_ACCESSIBLE_MEM_ADDR ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_warn_ratelimited (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 scalar_t__ hl_mmu_unmap (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  mmCPU_IF_ARUSER_OVR_EN ; 
 int /*<<< orphan*/  mmCPU_IF_AWUSER_OVR_EN ; 

void goya_mmu_remove_device_cpu_mappings(struct hl_device *hdev)
{
	struct asic_fixed_properties *prop = &hdev->asic_prop;
	struct goya_device *goya = hdev->asic_specific;
	u32 off, cpu_off;

	if (!(goya->hw_cap_initialized & HW_CAP_MMU))
		return;

	if (!goya->device_cpu_mmu_mappings_done)
		return;

	WREG32(mmCPU_IF_ARUSER_OVR_EN, 0);
	WREG32(mmCPU_IF_AWUSER_OVR_EN, 0);

	if (!(hdev->cpu_accessible_dma_address & (PAGE_SIZE_2MB - 1))) {
		if (hl_mmu_unmap(hdev->kernel_ctx, VA_CPU_ACCESSIBLE_MEM_ADDR,
				PAGE_SIZE_2MB))
			dev_warn(hdev->dev,
				"Failed to unmap CPU accessible memory\n");
	} else {
		for (cpu_off = 0 ; cpu_off < SZ_2M ; cpu_off += PAGE_SIZE_4KB)
			if (hl_mmu_unmap(hdev->kernel_ctx,
					VA_CPU_ACCESSIBLE_MEM_ADDR + cpu_off,
					PAGE_SIZE_4KB))
				dev_warn_ratelimited(hdev->dev,
					"failed to unmap address 0x%llx\n",
					VA_CPU_ACCESSIBLE_MEM_ADDR + cpu_off);
	}

	for (off = 0 ; off < CPU_FW_IMAGE_SIZE ; off += PAGE_SIZE_2MB)
		if (hl_mmu_unmap(hdev->kernel_ctx,
				prop->dram_base_address + off, PAGE_SIZE_2MB))
			dev_warn_ratelimited(hdev->dev,
					"Failed to unmap address 0x%llx\n",
					prop->dram_base_address + off);

	goya->device_cpu_mmu_mappings_done = false;
}