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
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  amdgpu_atombios_scratch_regs_engine_hung (struct amdgpu_device*,int) ; 
 int vi_gpu_pci_config_reset (struct amdgpu_device*) ; 

__attribute__((used)) static int vi_asic_reset(struct amdgpu_device *adev)
{
	int r;

	amdgpu_atombios_scratch_regs_engine_hung(adev, true);

	r = vi_gpu_pci_config_reset(adev);

	amdgpu_atombios_scratch_regs_engine_hung(adev, false);

	return r;
}