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
struct kv_reset_save_regs {int /*<<< orphan*/  member_0; } ;
struct amdgpu_device {int flags; scalar_t__ usec_timeout; int has_hw_reset; int /*<<< orphan*/  pdev; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int AMD_IS_APU ; 
 int EINVAL ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdgpu_device_pci_config_reset (struct amdgpu_device*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  kv_restore_regs_for_reset (struct amdgpu_device*,struct kv_reset_save_regs*) ; 
 int /*<<< orphan*/  kv_save_regs_for_reset (struct amdgpu_device*,struct kv_reset_save_regs*) ; 
 int /*<<< orphan*/  mmCONFIG_MEMSIZE ; 
 int /*<<< orphan*/  pci_clear_master (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_master (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int cik_gpu_pci_config_reset(struct amdgpu_device *adev)
{
	struct kv_reset_save_regs kv_save = { 0 };
	u32 i;
	int r = -EINVAL;

	dev_info(adev->dev, "GPU pci config reset\n");

	if (adev->flags & AMD_IS_APU)
		kv_save_regs_for_reset(adev, &kv_save);

	/* disable BM */
	pci_clear_master(adev->pdev);
	/* reset */
	amdgpu_device_pci_config_reset(adev);

	udelay(100);

	/* wait for asic to come out of reset */
	for (i = 0; i < adev->usec_timeout; i++) {
		if (RREG32(mmCONFIG_MEMSIZE) != 0xffffffff) {
			/* enable BM */
			pci_set_master(adev->pdev);
			adev->has_hw_reset = true;
			r = 0;
			break;
		}
		udelay(1);
	}

	/* does asic init need to be run first??? */
	if (adev->flags & AMD_IS_APU)
		kv_restore_regs_for_reset(adev, &kv_save);

	return r;
}