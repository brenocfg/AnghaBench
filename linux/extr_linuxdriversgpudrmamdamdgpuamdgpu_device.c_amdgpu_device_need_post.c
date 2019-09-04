#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_3__ {TYPE_2__* fw; } ;
struct amdgpu_device {scalar_t__ asic_type; int has_hw_reset; TYPE_1__ pm; int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {scalar_t__ data; } ;

/* Variables and functions */
 scalar_t__ CHIP_BONAIRE ; 
 scalar_t__ CHIP_FIJI ; 
 int amdgpu_asic_get_config_memsize (struct amdgpu_device*) ; 
 int amdgpu_atombios_scratch_need_asic_init (struct amdgpu_device*) ; 
 scalar_t__ amdgpu_passthrough (struct amdgpu_device*) ; 
 scalar_t__ amdgpu_sriov_vf (struct amdgpu_device*) ; 
 int request_firmware (TYPE_2__**,char*,int /*<<< orphan*/ ) ; 

bool amdgpu_device_need_post(struct amdgpu_device *adev)
{
	uint32_t reg;

	if (amdgpu_sriov_vf(adev))
		return false;

	if (amdgpu_passthrough(adev)) {
		/* for FIJI: In whole GPU pass-through virtualization case, after VM reboot
		 * some old smc fw still need driver do vPost otherwise gpu hang, while
		 * those smc fw version above 22.15 doesn't have this flaw, so we force
		 * vpost executed for smc version below 22.15
		 */
		if (adev->asic_type == CHIP_FIJI) {
			int err;
			uint32_t fw_ver;
			err = request_firmware(&adev->pm.fw, "amdgpu/fiji_smc.bin", adev->dev);
			/* force vPost if error occured */
			if (err)
				return true;

			fw_ver = *((uint32_t *)adev->pm.fw->data + 69);
			if (fw_ver < 0x00160e00)
				return true;
		}
	}

	if (adev->has_hw_reset) {
		adev->has_hw_reset = false;
		return true;
	}

	/* bios scratch used on CIK+ */
	if (adev->asic_type >= CHIP_BONAIRE)
		return amdgpu_atombios_scratch_need_asic_init(adev);

	/* check MEM_SIZE for older asics */
	reg = amdgpu_asic_get_config_memsize(adev);

	if ((reg != 0) && (reg != 0xffffffff))
		return false;

	return true;
}