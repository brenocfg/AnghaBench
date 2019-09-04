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
struct amdgpu_device {scalar_t__ usec_timeout; int has_hw_reset; int /*<<< orphan*/  pdev; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdgpu_device_pci_config_reset (struct amdgpu_device*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mmCONFIG_MEMSIZE ; 
 int /*<<< orphan*/  pci_clear_master (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_master (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int vi_gpu_pci_config_reset(struct amdgpu_device *adev)
{
	u32 i;

	dev_info(adev->dev, "GPU pci config reset\n");

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
			return 0;
		}
		udelay(1);
	}
	return -EINVAL;
}