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
struct TYPE_2__ {int /*<<< orphan*/ * rlc_fw; int /*<<< orphan*/ * mec2_fw; int /*<<< orphan*/ * mec_fw; int /*<<< orphan*/ * ce_fw; int /*<<< orphan*/ * me_fw; int /*<<< orphan*/ * pfp_fw; } ;
struct amdgpu_device {int asic_type; TYPE_1__ gfx; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  fw_name ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
#define  CHIP_BONAIRE 132 
#define  CHIP_HAWAII 131 
#define  CHIP_KABINI 130 
#define  CHIP_KAVERI 129 
#define  CHIP_MULLINS 128 
 int /*<<< orphan*/  DRM_DEBUG (char*) ; 
 int amdgpu_ucode_validate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,char*) ; 
 int /*<<< orphan*/  release_firmware (int /*<<< orphan*/ *) ; 
 int request_firmware (int /*<<< orphan*/ **,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*) ; 

__attribute__((used)) static int gfx_v7_0_init_microcode(struct amdgpu_device *adev)
{
	const char *chip_name;
	char fw_name[30];
	int err;

	DRM_DEBUG("\n");

	switch (adev->asic_type) {
	case CHIP_BONAIRE:
		chip_name = "bonaire";
		break;
	case CHIP_HAWAII:
		chip_name = "hawaii";
		break;
	case CHIP_KAVERI:
		chip_name = "kaveri";
		break;
	case CHIP_KABINI:
		chip_name = "kabini";
		break;
	case CHIP_MULLINS:
		chip_name = "mullins";
		break;
	default: BUG();
	}

	snprintf(fw_name, sizeof(fw_name), "amdgpu/%s_pfp.bin", chip_name);
	err = request_firmware(&adev->gfx.pfp_fw, fw_name, adev->dev);
	if (err)
		goto out;
	err = amdgpu_ucode_validate(adev->gfx.pfp_fw);
	if (err)
		goto out;

	snprintf(fw_name, sizeof(fw_name), "amdgpu/%s_me.bin", chip_name);
	err = request_firmware(&adev->gfx.me_fw, fw_name, adev->dev);
	if (err)
		goto out;
	err = amdgpu_ucode_validate(adev->gfx.me_fw);
	if (err)
		goto out;

	snprintf(fw_name, sizeof(fw_name), "amdgpu/%s_ce.bin", chip_name);
	err = request_firmware(&adev->gfx.ce_fw, fw_name, adev->dev);
	if (err)
		goto out;
	err = amdgpu_ucode_validate(adev->gfx.ce_fw);
	if (err)
		goto out;

	snprintf(fw_name, sizeof(fw_name), "amdgpu/%s_mec.bin", chip_name);
	err = request_firmware(&adev->gfx.mec_fw, fw_name, adev->dev);
	if (err)
		goto out;
	err = amdgpu_ucode_validate(adev->gfx.mec_fw);
	if (err)
		goto out;

	if (adev->asic_type == CHIP_KAVERI) {
		snprintf(fw_name, sizeof(fw_name), "amdgpu/%s_mec2.bin", chip_name);
		err = request_firmware(&adev->gfx.mec2_fw, fw_name, adev->dev);
		if (err)
			goto out;
		err = amdgpu_ucode_validate(adev->gfx.mec2_fw);
		if (err)
			goto out;
	}

	snprintf(fw_name, sizeof(fw_name), "amdgpu/%s_rlc.bin", chip_name);
	err = request_firmware(&adev->gfx.rlc_fw, fw_name, adev->dev);
	if (err)
		goto out;
	err = amdgpu_ucode_validate(adev->gfx.rlc_fw);

out:
	if (err) {
		pr_err("gfx7: Failed to load firmware \"%s\"\n", fw_name);
		release_firmware(adev->gfx.pfp_fw);
		adev->gfx.pfp_fw = NULL;
		release_firmware(adev->gfx.me_fw);
		adev->gfx.me_fw = NULL;
		release_firmware(adev->gfx.ce_fw);
		adev->gfx.ce_fw = NULL;
		release_firmware(adev->gfx.mec_fw);
		adev->gfx.mec_fw = NULL;
		release_firmware(adev->gfx.mec2_fw);
		adev->gfx.mec2_fw = NULL;
		release_firmware(adev->gfx.rlc_fw);
		adev->gfx.rlc_fw = NULL;
	}
	return err;
}