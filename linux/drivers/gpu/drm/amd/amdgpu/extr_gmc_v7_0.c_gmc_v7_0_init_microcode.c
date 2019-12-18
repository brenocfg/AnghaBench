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
#define  CHIP_BONAIRE 133 
#define  CHIP_HAWAII 132 
#define  CHIP_KABINI 131 
#define  CHIP_KAVERI 130 
#define  CHIP_MULLINS 129 
#define  CHIP_TOPAZ 128 
 int /*<<< orphan*/  DRM_DEBUG (char*) ; 
 int amdgpu_ucode_validate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,char*) ; 
 int /*<<< orphan*/  release_firmware (int /*<<< orphan*/ *) ; 
 int request_firmware (int /*<<< orphan*/ **,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*) ; 

__attribute__((used)) static int gmc_v7_0_init_microcode(struct amdgpu_device *adev)
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
	case CHIP_TOPAZ:
		chip_name = "topaz";
		break;
	case CHIP_KAVERI:
	case CHIP_KABINI:
	case CHIP_MULLINS:
		return 0;
	default: BUG();
	}

	snprintf(fw_name, sizeof(fw_name), "amdgpu/%s_mc.bin", chip_name);

	err = request_firmware(&adev->gmc.fw, fw_name, adev->dev);
	if (err)
		goto out;
	err = amdgpu_ucode_validate(adev->gmc.fw);

out:
	if (err) {
		pr_err("cik_mc: Failed to load firmware \"%s\"\n", fw_name);
		release_firmware(adev->gmc.fw);
		adev->gmc.fw = NULL;
	}
	return err;
}