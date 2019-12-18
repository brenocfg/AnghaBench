#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned long long uint32_t ;
typedef  int u64 ;
struct TYPE_3__ {int vram_is_ddr; int vram_width; int real_vram_size; int mc_vram_size; unsigned long long aper_size; unsigned long long visible_vram_size; int igp_sideport_enabled; scalar_t__ gtt_size; scalar_t__ gtt_base_align; scalar_t__ aper_base; } ;
struct radeon_device {int fastfb_working; TYPE_1__ mc; int /*<<< orphan*/  pdev; } ;
typedef  scalar_t__ resource_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_INFO (char*,unsigned long long,unsigned long long) ; 
 unsigned long long G_00005F_K8_ADDR_EXT (void*) ; 
 int G_000100_MC_FB_START (int) ; 
 int /*<<< orphan*/  RADEON_CONFIG_MEMSIZE ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 void* RREG32_MC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  R_00001E_K8_FB_LOCATION ; 
 int /*<<< orphan*/  R_00005F_MC_MISC_UMA_CNTL ; 
 int /*<<< orphan*/  R_000100_MCCFG_FB_LOCATION ; 
 unsigned long long pci_resource_len (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ pci_resource_start (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int radeon_atombios_sideport_present (struct radeon_device*) ; 
 int radeon_fastfb ; 
 int /*<<< orphan*/  radeon_gtt_location (struct radeon_device*,TYPE_1__*) ; 
 int /*<<< orphan*/  radeon_update_bandwidth_info (struct radeon_device*) ; 
 int /*<<< orphan*/  radeon_vram_location (struct radeon_device*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  rs400_gart_adjust_size (struct radeon_device*) ; 
 int /*<<< orphan*/  rs690_pm_info (struct radeon_device*) ; 

__attribute__((used)) static void rs690_mc_init(struct radeon_device *rdev)
{
	u64 base;
	uint32_t h_addr, l_addr;
	unsigned long long k8_addr;

	rs400_gart_adjust_size(rdev);
	rdev->mc.vram_is_ddr = true;
	rdev->mc.vram_width = 128;
	rdev->mc.real_vram_size = RREG32(RADEON_CONFIG_MEMSIZE);
	rdev->mc.mc_vram_size = rdev->mc.real_vram_size;
	rdev->mc.aper_base = pci_resource_start(rdev->pdev, 0);
	rdev->mc.aper_size = pci_resource_len(rdev->pdev, 0);
	rdev->mc.visible_vram_size = rdev->mc.aper_size;
	base = RREG32_MC(R_000100_MCCFG_FB_LOCATION);
	base = G_000100_MC_FB_START(base) << 16;
	rdev->mc.igp_sideport_enabled = radeon_atombios_sideport_present(rdev);
	/* Some boards seem to be configured for 128MB of sideport memory,
	 * but really only have 64MB.  Just skip the sideport and use
	 * UMA memory.
	 */
	if (rdev->mc.igp_sideport_enabled &&
	    (rdev->mc.real_vram_size == (384 * 1024 * 1024))) {
		base += 128 * 1024 * 1024;
		rdev->mc.real_vram_size -= 128 * 1024 * 1024;
		rdev->mc.mc_vram_size = rdev->mc.real_vram_size;
	}

	/* Use K8 direct mapping for fast fb access. */ 
	rdev->fastfb_working = false;
	h_addr = G_00005F_K8_ADDR_EXT(RREG32_MC(R_00005F_MC_MISC_UMA_CNTL));
	l_addr = RREG32_MC(R_00001E_K8_FB_LOCATION);
	k8_addr = ((unsigned long long)h_addr) << 32 | l_addr;
#if defined(CONFIG_X86_32) && !defined(CONFIG_X86_PAE)
	if (k8_addr + rdev->mc.visible_vram_size < 0x100000000ULL)	
#endif
	{
		/* FastFB shall be used with UMA memory. Here it is simply disabled when sideport 
		 * memory is present.
		 */
		if (rdev->mc.igp_sideport_enabled == false && radeon_fastfb == 1) {
			DRM_INFO("Direct mapping: aper base at 0x%llx, replaced by direct mapping base 0x%llx.\n", 
					(unsigned long long)rdev->mc.aper_base, k8_addr);
			rdev->mc.aper_base = (resource_size_t)k8_addr;
			rdev->fastfb_working = true;
		}
	}  

	rs690_pm_info(rdev);
	radeon_vram_location(rdev, &rdev->mc, base);
	rdev->mc.gtt_base_align = rdev->mc.gtt_size - 1;
	radeon_gtt_location(rdev, &rdev->mc);
	radeon_update_bandwidth_info(rdev);
}