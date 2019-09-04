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
typedef  int u32 ;
struct TYPE_2__ {int vram_is_ddr; int vram_width; unsigned long long mc_vram_size; unsigned long long real_vram_size; int /*<<< orphan*/  aper_size; int /*<<< orphan*/  visible_vram_size; int /*<<< orphan*/  aper_base; } ;
struct radeon_device {scalar_t__ family; TYPE_1__ mc; int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int CHANSIZE_MASK ; 
 int CHANSIZE_OVERRIDE ; 
 scalar_t__ CHIP_PALM ; 
 scalar_t__ CHIP_SUMO ; 
 scalar_t__ CHIP_SUMO2 ; 
 int /*<<< orphan*/  CONFIG_MEMSIZE ; 
 int /*<<< orphan*/  FUS_MC_ARB_RAMCFG ; 
 int /*<<< orphan*/  MC_ARB_RAMCFG ; 
 int /*<<< orphan*/  MC_SHARED_CHMAP ; 
 int NOOFCHAN_MASK ; 
 int NOOFCHAN_SHIFT ; 
 unsigned long long RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_resource_len (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_resource_start (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r700_vram_gtt_location (struct radeon_device*,TYPE_1__*) ; 
 int /*<<< orphan*/  radeon_update_bandwidth_info (struct radeon_device*) ; 

int evergreen_mc_init(struct radeon_device *rdev)
{
	u32 tmp;
	int chansize, numchan;

	/* Get VRAM informations */
	rdev->mc.vram_is_ddr = true;
	if ((rdev->family == CHIP_PALM) ||
	    (rdev->family == CHIP_SUMO) ||
	    (rdev->family == CHIP_SUMO2))
		tmp = RREG32(FUS_MC_ARB_RAMCFG);
	else
		tmp = RREG32(MC_ARB_RAMCFG);
	if (tmp & CHANSIZE_OVERRIDE) {
		chansize = 16;
	} else if (tmp & CHANSIZE_MASK) {
		chansize = 64;
	} else {
		chansize = 32;
	}
	tmp = RREG32(MC_SHARED_CHMAP);
	switch ((tmp & NOOFCHAN_MASK) >> NOOFCHAN_SHIFT) {
	case 0:
	default:
		numchan = 1;
		break;
	case 1:
		numchan = 2;
		break;
	case 2:
		numchan = 4;
		break;
	case 3:
		numchan = 8;
		break;
	}
	rdev->mc.vram_width = numchan * chansize;
	/* Could aper size report 0 ? */
	rdev->mc.aper_base = pci_resource_start(rdev->pdev, 0);
	rdev->mc.aper_size = pci_resource_len(rdev->pdev, 0);
	/* Setup GPU memory space */
	if ((rdev->family == CHIP_PALM) ||
	    (rdev->family == CHIP_SUMO) ||
	    (rdev->family == CHIP_SUMO2)) {
		/* size in bytes on fusion */
		rdev->mc.mc_vram_size = RREG32(CONFIG_MEMSIZE);
		rdev->mc.real_vram_size = RREG32(CONFIG_MEMSIZE);
	} else {
		/* size in MB on evergreen/cayman/tn */
		rdev->mc.mc_vram_size = RREG32(CONFIG_MEMSIZE) * 1024ULL * 1024ULL;
		rdev->mc.real_vram_size = RREG32(CONFIG_MEMSIZE) * 1024ULL * 1024ULL;
	}
	rdev->mc.visible_vram_size = rdev->mc.aper_size;
	r700_vram_gtt_location(rdev, &rdev->mc);
	radeon_update_bandwidth_info(rdev);

	return 0;
}