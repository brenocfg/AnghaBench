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
struct TYPE_4__ {int /*<<< orphan*/ * fw; } ;
struct amdgpu_device {int asic_type; TYPE_2__ gmc; int /*<<< orphan*/  dev; TYPE_1__* pdev; } ;
typedef  int /*<<< orphan*/  fw_name ;
struct TYPE_3__ {int device; int revision; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
#define  CHIP_CARRIZO 135 
#define  CHIP_FIJI 134 
#define  CHIP_POLARIS10 133 
#define  CHIP_POLARIS11 132 
#define  CHIP_POLARIS12 131 
#define  CHIP_STONEY 130 
#define  CHIP_TONGA 129 
#define  CHIP_VEGAM 128 
 int /*<<< orphan*/  DRM_DEBUG (char*) ; 
 int amdgpu_ucode_validate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,char*) ; 
 int /*<<< orphan*/  release_firmware (int /*<<< orphan*/ *) ; 
 int request_firmware (int /*<<< orphan*/ **,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*) ; 

__attribute__((used)) static int gmc_v8_0_init_microcode(struct amdgpu_device *adev)
{
	const char *chip_name;
	char fw_name[30];
	int err;

	DRM_DEBUG("\n");

	switch (adev->asic_type) {
	case CHIP_TONGA:
		chip_name = "tonga";
		break;
	case CHIP_POLARIS11:
		if (((adev->pdev->device == 0x67ef) &&
		     ((adev->pdev->revision == 0xe0) ||
		      (adev->pdev->revision == 0xe5))) ||
		    ((adev->pdev->device == 0x67ff) &&
		     ((adev->pdev->revision == 0xcf) ||
		      (adev->pdev->revision == 0xef) ||
		      (adev->pdev->revision == 0xff))))
			chip_name = "polaris11_k";
		else if ((adev->pdev->device == 0x67ef) &&
			 (adev->pdev->revision == 0xe2))
			chip_name = "polaris11_k";
		else
			chip_name = "polaris11";
		break;
	case CHIP_POLARIS10:
		if ((adev->pdev->device == 0x67df) &&
		    ((adev->pdev->revision == 0xe1) ||
		     (adev->pdev->revision == 0xf7)))
			chip_name = "polaris10_k";
		else
			chip_name = "polaris10";
		break;
	case CHIP_POLARIS12:
		if (((adev->pdev->device == 0x6987) &&
		     ((adev->pdev->revision == 0xc0) ||
		      (adev->pdev->revision == 0xc3))) ||
		    ((adev->pdev->device == 0x6981) &&
		     ((adev->pdev->revision == 0x00) ||
		      (adev->pdev->revision == 0x01) ||
		      (adev->pdev->revision == 0x10))))
			chip_name = "polaris12_k";
		else
			chip_name = "polaris12";
		break;
	case CHIP_FIJI:
	case CHIP_CARRIZO:
	case CHIP_STONEY:
	case CHIP_VEGAM:
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
		pr_err("mc: Failed to load firmware \"%s\"\n", fw_name);
		release_firmware(adev->gmc.fw);
		adev->gmc.fw = NULL;
	}
	return err;
}