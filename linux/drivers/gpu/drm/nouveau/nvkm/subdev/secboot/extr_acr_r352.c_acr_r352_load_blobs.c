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
struct nvkm_subdev {int dummy; } ;
struct nvkm_secboot {scalar_t__ wpr_size; struct nvkm_subdev subdev; } ;
struct TYPE_2__ {scalar_t__ boot_falcon; } ;
struct acr_r352 {int firmware_ok; int /*<<< orphan*/ * hsbl_blob; int /*<<< orphan*/ * hsbl_unload_blob; TYPE_1__ base; int /*<<< orphan*/  unload_bl_header; int /*<<< orphan*/  unload_blob; int /*<<< orphan*/  load_bl_header; int /*<<< orphan*/  load_blob; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 scalar_t__ NVKM_SECBOOT_FALCON_PMU ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int acr_r352_prepare_hs_blob (struct acr_r352*,struct nvkm_secboot*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int acr_r352_prepare_ls_blob (struct acr_r352*,struct nvkm_secboot*) ; 
 void* nvkm_acr_load_firmware (struct nvkm_subdev*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvkm_debug (struct nvkm_subdev*,char*) ; 

int
acr_r352_load_blobs(struct acr_r352 *acr, struct nvkm_secboot *sb)
{
	struct nvkm_subdev *subdev = &sb->subdev;
	int ret;

	/* Firmware already loaded? */
	if (acr->firmware_ok)
		return 0;

	/* Load and prepare the managed falcon's firmwares */
	ret = acr_r352_prepare_ls_blob(acr, sb);
	if (ret)
		return ret;

	/* Load the HS firmware that will load the LS firmwares */
	if (!acr->load_blob) {
		ret = acr_r352_prepare_hs_blob(acr, sb, "acr/ucode_load",
					       &acr->load_blob,
					       &acr->load_bl_header, true);
		if (ret)
			return ret;
	}

	/* If the ACR region is dynamically programmed, we need an unload FW */
	if (sb->wpr_size == 0) {
		ret = acr_r352_prepare_hs_blob(acr, sb, "acr/ucode_unload",
					       &acr->unload_blob,
					       &acr->unload_bl_header, false);
		if (ret)
			return ret;
	}

	/* Load the HS firmware bootloader */
	if (!acr->hsbl_blob) {
		acr->hsbl_blob = nvkm_acr_load_firmware(subdev, "acr/bl", 0);
		if (IS_ERR(acr->hsbl_blob)) {
			ret = PTR_ERR(acr->hsbl_blob);
			acr->hsbl_blob = NULL;
			return ret;
		}

		if (acr->base.boot_falcon != NVKM_SECBOOT_FALCON_PMU) {
			acr->hsbl_unload_blob = nvkm_acr_load_firmware(subdev,
							    "acr/unload_bl", 0);
			if (IS_ERR(acr->hsbl_unload_blob)) {
				ret = PTR_ERR(acr->hsbl_unload_blob);
				acr->hsbl_unload_blob = NULL;
				return ret;
			}
		} else {
			acr->hsbl_unload_blob = acr->hsbl_blob;
		}
	}

	acr->firmware_ok = true;
	nvkm_debug(&sb->subdev, "LS blob successfully created\n");

	return 0;
}