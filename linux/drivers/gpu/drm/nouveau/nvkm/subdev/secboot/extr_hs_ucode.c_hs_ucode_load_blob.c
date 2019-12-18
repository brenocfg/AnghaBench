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
typedef  int u32 ;
struct nvkm_subdev {int dummy; } ;
struct nvkm_falcon {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 void* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (void*) ; 
 int /*<<< orphan*/  hs_ucode_patch_signature (struct nvkm_falcon const*,void*,int) ; 
 void* nvkm_acr_load_firmware (struct nvkm_subdev*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvkm_error (struct nvkm_subdev*,char*,char const*) ; 

void *
hs_ucode_load_blob(struct nvkm_subdev *subdev, const struct nvkm_falcon *falcon,
		   const char *fw)
{
	void *acr_image;
	bool new_format;

	acr_image = nvkm_acr_load_firmware(subdev, fw, 0);
	if (IS_ERR(acr_image))
		return acr_image;

	/* detect the format to define how signature should be patched */
	switch (((u32 *)acr_image)[0]) {
	case 0x3b1d14f0:
		new_format = true;
		break;
	case 0x000010de:
		new_format = false;
		break;
	default:
		nvkm_error(subdev, "unknown header for HS blob %s\n", fw);
		return ERR_PTR(-EINVAL);
	}

	hs_ucode_patch_signature(falcon, acr_image, new_format);

	return acr_image;
}