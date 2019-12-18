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
typedef  int uint64_t ;
struct TYPE_2__ {int gtt_size; } ;
struct radeon_device {int /*<<< orphan*/  dev; TYPE_1__ mc; int /*<<< orphan*/  family; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int) ; 
 int ilog2 (int) ; 
 int radeon_agpmode ; 
 int /*<<< orphan*/  radeon_check_pot_argument (int) ; 
 int radeon_gart_size ; 
 int radeon_gart_size_auto (int /*<<< orphan*/ ) ; 
 int radeon_vm_block_size ; 
 int radeon_vm_size ; 
 int radeon_vram_limit ; 

__attribute__((used)) static void radeon_check_arguments(struct radeon_device *rdev)
{
	/* vramlimit must be a power of two */
	if (!radeon_check_pot_argument(radeon_vram_limit)) {
		dev_warn(rdev->dev, "vram limit (%d) must be a power of 2\n",
				radeon_vram_limit);
		radeon_vram_limit = 0;
	}

	if (radeon_gart_size == -1) {
		radeon_gart_size = radeon_gart_size_auto(rdev->family);
	}
	/* gtt size must be power of two and greater or equal to 32M */
	if (radeon_gart_size < 32) {
		dev_warn(rdev->dev, "gart size (%d) too small\n",
				radeon_gart_size);
		radeon_gart_size = radeon_gart_size_auto(rdev->family);
	} else if (!radeon_check_pot_argument(radeon_gart_size)) {
		dev_warn(rdev->dev, "gart size (%d) must be a power of 2\n",
				radeon_gart_size);
		radeon_gart_size = radeon_gart_size_auto(rdev->family);
	}
	rdev->mc.gtt_size = (uint64_t)radeon_gart_size << 20;

	/* AGP mode can only be -1, 1, 2, 4, 8 */
	switch (radeon_agpmode) {
	case -1:
	case 0:
	case 1:
	case 2:
	case 4:
	case 8:
		break;
	default:
		dev_warn(rdev->dev, "invalid AGP mode %d (valid mode: "
				"-1, 0, 1, 2, 4, 8)\n", radeon_agpmode);
		radeon_agpmode = 0;
		break;
	}

	if (!radeon_check_pot_argument(radeon_vm_size)) {
		dev_warn(rdev->dev, "VM size (%d) must be a power of 2\n",
			 radeon_vm_size);
		radeon_vm_size = 4;
	}

	if (radeon_vm_size < 1) {
		dev_warn(rdev->dev, "VM size (%d) too small, min is 1GB\n",
			 radeon_vm_size);
		radeon_vm_size = 4;
	}

	/*
	 * Max GPUVM size for Cayman, SI and CI are 40 bits.
	 */
	if (radeon_vm_size > 1024) {
		dev_warn(rdev->dev, "VM size (%d) too large, max is 1TB\n",
			 radeon_vm_size);
		radeon_vm_size = 4;
	}

	/* defines number of bits in page table versus page directory,
	 * a page is 4KB so we have 12 bits offset, minimum 9 bits in the
	 * page table and the remaining bits are in the page directory */
	if (radeon_vm_block_size == -1) {

		/* Total bits covered by PD + PTs */
		unsigned bits = ilog2(radeon_vm_size) + 18;

		/* Make sure the PD is 4K in size up to 8GB address space.
		   Above that split equal between PD and PTs */
		if (radeon_vm_size <= 8)
			radeon_vm_block_size = bits - 9;
		else
			radeon_vm_block_size = (bits + 3) / 2;

	} else if (radeon_vm_block_size < 9) {
		dev_warn(rdev->dev, "VM page table size (%d) too small\n",
			 radeon_vm_block_size);
		radeon_vm_block_size = 9;
	}

	if (radeon_vm_block_size > 24 ||
	    (radeon_vm_size * 1024) < (1ull << radeon_vm_block_size)) {
		dev_warn(rdev->dev, "VM page table size (%d) too large\n",
			 radeon_vm_block_size);
		radeon_vm_block_size = 9;
	}
}