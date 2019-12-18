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
struct TYPE_2__ {scalar_t__ app_size; scalar_t__ app_start_offset; } ;
struct ls_ucode_img {void* sig; int /*<<< orphan*/  sig_size; TYPE_1__ ucode_desc; int /*<<< orphan*/  ucode_size; void* ucode_data; } ;
struct firmware {int /*<<< orphan*/  size; int /*<<< orphan*/  data; } ;
typedef  int /*<<< orphan*/  f ;

/* Variables and functions */
 int /*<<< orphan*/  ALIGN (scalar_t__,int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* kmemdup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int nvkm_firmware_get_version (struct nvkm_subdev const*,char*,int,int,struct firmware const**) ; 
 int /*<<< orphan*/  nvkm_firmware_put (struct firmware const*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*) ; 

__attribute__((used)) static int
acr_ls_ucode_load_msgqueue(const struct nvkm_subdev *subdev, const char *name,
			   int maxver, struct ls_ucode_img *img)
{
	const struct firmware *image, *desc, *sig;
	char f[64];
	int ver, ret;

	snprintf(f, sizeof(f), "%s/image", name);
	ver = nvkm_firmware_get_version(subdev, f, 0, maxver, &image);
	if (ver < 0)
		return ver;
	img->ucode_data = kmemdup(image->data, image->size, GFP_KERNEL);
	nvkm_firmware_put(image);
	if (!img->ucode_data)
		return -ENOMEM;

	snprintf(f, sizeof(f), "%s/desc", name);
	ret = nvkm_firmware_get_version(subdev, f, ver, ver, &desc);
	if (ret < 0)
		return ret;
	memcpy(&img->ucode_desc, desc->data, sizeof(img->ucode_desc));
	img->ucode_size = ALIGN(img->ucode_desc.app_start_offset + img->ucode_desc.app_size, 256);
	nvkm_firmware_put(desc);

	snprintf(f, sizeof(f), "%s/sig", name);
	ret = nvkm_firmware_get_version(subdev, f, ver, ver, &sig);
	if (ret < 0)
		return ret;
	img->sig_size = sig->size;
	img->sig = kmemdup(sig->data, sig->size, GFP_KERNEL);
	nvkm_firmware_put(sig);
	if (!img->sig)
		return -ENOMEM;

	return ver;
}