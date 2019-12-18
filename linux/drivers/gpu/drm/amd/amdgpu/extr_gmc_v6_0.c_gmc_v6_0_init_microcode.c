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
struct TYPE_2__ {int /*<<< orphan*/ * fw; } ;
struct amdgpu_device {int asic_type; TYPE_1__ gmc; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  fw_name ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
#define  CHIP_HAINAN 132 
#define  CHIP_OLAND 131 
#define  CHIP_PITCAIRN 130 
#define  CHIP_TAHITI 129 
#define  CHIP_VERDE 128 
 int /*<<< orphan*/  DRM_DEBUG (char*) ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 int amdgpu_ucode_validate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  mmMC_SEQ_MISC0 ; 
 int /*<<< orphan*/  release_firmware (int /*<<< orphan*/ *) ; 
 int request_firmware (int /*<<< orphan*/ **,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,...) ; 

__attribute__((used)) static int gmc_v6_0_init_microcode(struct amdgpu_device *adev)
{
	const char *chip_name;
	char fw_name[30];
	int err;
	bool is_58_fw = false;

	DRM_DEBUG("\n");

	switch (adev->asic_type) {
	case CHIP_TAHITI:
		chip_name = "tahiti";
		break;
	case CHIP_PITCAIRN:
		chip_name = "pitcairn";
		break;
	case CHIP_VERDE:
		chip_name = "verde";
		break;
	case CHIP_OLAND:
		chip_name = "oland";
		break;
	case CHIP_HAINAN:
		chip_name = "hainan";
		break;
	default: BUG();
	}

	/* this memory configuration requires special firmware */
	if (((RREG32(mmMC_SEQ_MISC0) & 0xff000000) >> 24) == 0x58)
		is_58_fw = true;

	if (is_58_fw)
		snprintf(fw_name, sizeof(fw_name), "amdgpu/si58_mc.bin");
	else
		snprintf(fw_name, sizeof(fw_name), "amdgpu/%s_mc.bin", chip_name);
	err = request_firmware(&adev->gmc.fw, fw_name, adev->dev);
	if (err)
		goto out;

	err = amdgpu_ucode_validate(adev->gmc.fw);

out:
	if (err) {
		dev_err(adev->dev,
		       "si_mc: Failed to load firmware \"%s\"\n",
		       fw_name);
		release_firmware(adev->gmc.fw);
		adev->gmc.fw = NULL;
	}
	return err;
}