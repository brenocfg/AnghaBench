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
typedef  scalar_t__ u32 ;
struct amdgpu_device {scalar_t__ usec_timeout; TYPE_1__* nbio_funcs; int /*<<< orphan*/  pdev; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {scalar_t__ (* get_memsize ) (struct amdgpu_device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  amdgpu_atombios_scratch_regs_engine_hung (struct amdgpu_device*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pci_clear_master (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_restore_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_save_state (int /*<<< orphan*/ ) ; 
 int psp_gpu_reset (struct amdgpu_device*) ; 
 scalar_t__ stub1 (struct amdgpu_device*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int nv_asic_mode1_reset(struct amdgpu_device *adev)
{
	u32 i;
	int ret = 0;

	amdgpu_atombios_scratch_regs_engine_hung(adev, true);

	dev_info(adev->dev, "GPU mode1 reset\n");

	/* disable BM */
	pci_clear_master(adev->pdev);

	pci_save_state(adev->pdev);

	ret = psp_gpu_reset(adev);
	if (ret)
		dev_err(adev->dev, "GPU mode1 reset failed\n");

	pci_restore_state(adev->pdev);

	/* wait for asic to come out of reset */
	for (i = 0; i < adev->usec_timeout; i++) {
		u32 memsize = adev->nbio_funcs->get_memsize(adev);

		if (memsize != 0xffffffff)
			break;
		udelay(1);
	}

	amdgpu_atombios_scratch_regs_engine_hung(adev, false);

	return ret;
}