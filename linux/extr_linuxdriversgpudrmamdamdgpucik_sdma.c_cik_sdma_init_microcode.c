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
struct TYPE_4__ {int num_instances; TYPE_1__* instance; } ;
struct amdgpu_device {int asic_type; TYPE_2__ sdma; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  fw_name ;
struct TYPE_3__ {int /*<<< orphan*/ * fw; } ;

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

__attribute__((used)) static int cik_sdma_init_microcode(struct amdgpu_device *adev)
{
	const char *chip_name;
	char fw_name[30];
	int err = 0, i;

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

	for (i = 0; i < adev->sdma.num_instances; i++) {
		if (i == 0)
			snprintf(fw_name, sizeof(fw_name), "amdgpu/%s_sdma.bin", chip_name);
		else
			snprintf(fw_name, sizeof(fw_name), "amdgpu/%s_sdma1.bin", chip_name);
		err = request_firmware(&adev->sdma.instance[i].fw, fw_name, adev->dev);
		if (err)
			goto out;
		err = amdgpu_ucode_validate(adev->sdma.instance[i].fw);
	}
out:
	if (err) {
		pr_err("cik_sdma: Failed to load firmware \"%s\"\n", fw_name);
		for (i = 0; i < adev->sdma.num_instances; i++) {
			release_firmware(adev->sdma.instance[i].fw);
			adev->sdma.instance[i].fw = NULL;
		}
	}
	return err;
}