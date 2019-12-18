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
typedef  int u32 ;
struct TYPE_2__ {int vram_width; unsigned long long mc_vram_size; unsigned long long real_vram_size; unsigned long long gart_size; int /*<<< orphan*/  aper_size; int /*<<< orphan*/  visible_vram_size; int /*<<< orphan*/  aper_base; } ;
struct amdgpu_device {int flags; int asic_type; TYPE_1__ gmc; int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int AMD_IS_APU ; 
#define  CHIP_HAINAN 132 
#define  CHIP_OLAND 131 
#define  CHIP_PITCAIRN 130 
#define  CHIP_TAHITI 129 
#define  CHIP_VERDE 128 
 int MC_ARB_RAMCFG__CHANSIZE_MASK ; 
 int MC_SHARED_CHMAP__NOOFCHAN_MASK ; 
 int MC_SHARED_CHMAP__NOOFCHAN__SHIFT ; 
 unsigned long long RREG32 (int /*<<< orphan*/ ) ; 
 int amdgpu_device_resize_fb_bar (struct amdgpu_device*) ; 
 int amdgpu_gart_size ; 
 int /*<<< orphan*/  gmc_v6_0_vram_gtt_location (struct amdgpu_device*,TYPE_1__*) ; 
 int /*<<< orphan*/  mmCONFIG_MEMSIZE ; 
 int /*<<< orphan*/  mmMC_ARB_RAMCFG ; 
 int /*<<< orphan*/  mmMC_SHARED_CHMAP ; 
 int /*<<< orphan*/  pci_resource_len (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_resource_start (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gmc_v6_0_mc_init(struct amdgpu_device *adev)
{

	u32 tmp;
	int chansize, numchan;
	int r;

	tmp = RREG32(mmMC_ARB_RAMCFG);
	if (tmp & (1 << 11)) {
		chansize = 16;
	} else if (tmp & MC_ARB_RAMCFG__CHANSIZE_MASK) {
		chansize = 64;
	} else {
		chansize = 32;
	}
	tmp = RREG32(mmMC_SHARED_CHMAP);
	switch ((tmp & MC_SHARED_CHMAP__NOOFCHAN_MASK) >> MC_SHARED_CHMAP__NOOFCHAN__SHIFT) {
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
	case 4:
		numchan = 3;
		break;
	case 5:
		numchan = 6;
		break;
	case 6:
		numchan = 10;
		break;
	case 7:
		numchan = 12;
		break;
	case 8:
		numchan = 16;
		break;
	}
	adev->gmc.vram_width = numchan * chansize;
	/* size in MB on si */
	adev->gmc.mc_vram_size = RREG32(mmCONFIG_MEMSIZE) * 1024ULL * 1024ULL;
	adev->gmc.real_vram_size = RREG32(mmCONFIG_MEMSIZE) * 1024ULL * 1024ULL;

	if (!(adev->flags & AMD_IS_APU)) {
		r = amdgpu_device_resize_fb_bar(adev);
		if (r)
			return r;
	}
	adev->gmc.aper_base = pci_resource_start(adev->pdev, 0);
	adev->gmc.aper_size = pci_resource_len(adev->pdev, 0);
	adev->gmc.visible_vram_size = adev->gmc.aper_size;

	/* set the gart size */
	if (amdgpu_gart_size == -1) {
		switch (adev->asic_type) {
		case CHIP_HAINAN:    /* no MM engines */
		default:
			adev->gmc.gart_size = 256ULL << 20;
			break;
		case CHIP_VERDE:    /* UVD, VCE do not support GPUVM */
		case CHIP_TAHITI:   /* UVD, VCE do not support GPUVM */
		case CHIP_PITCAIRN: /* UVD, VCE do not support GPUVM */
		case CHIP_OLAND:    /* UVD, VCE do not support GPUVM */
			adev->gmc.gart_size = 1024ULL << 20;
			break;
		}
	} else {
		adev->gmc.gart_size = (u64)amdgpu_gart_size << 20;
	}

	gmc_v6_0_vram_gtt_location(adev, &adev->gmc);

	return 0;
}