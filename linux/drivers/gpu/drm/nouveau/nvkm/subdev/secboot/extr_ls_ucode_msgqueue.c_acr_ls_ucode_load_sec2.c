#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* device; } ;
struct nvkm_secboot {TYPE_3__ subdev; } ;
struct nvkm_sec2 {int /*<<< orphan*/  queue; int /*<<< orphan*/  falcon; } ;
struct TYPE_5__ {int /*<<< orphan*/  app_version; } ;
struct ls_ucode_img {TYPE_2__ ucode_desc; } ;
struct TYPE_4__ {struct nvkm_sec2* sec2; } ;

/* Variables and functions */
 int acr_ls_ucode_load_msgqueue (TYPE_3__*,char*,int,struct ls_ucode_img*) ; 
 int nvkm_msgqueue_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nvkm_secboot const*,int /*<<< orphan*/ *) ; 

int
acr_ls_ucode_load_sec2(const struct nvkm_secboot *sb, int maxver,
		       struct ls_ucode_img *img)
{
	struct nvkm_sec2 *sec = sb->subdev.device->sec2;
	int ver, ret;

	ver = acr_ls_ucode_load_msgqueue(&sb->subdev, "sec2", maxver, img);
	if (ver < 0)
		return ver;

	/* Allocate the PMU queue corresponding to the FW version */
	ret = nvkm_msgqueue_new(img->ucode_desc.app_version, sec->falcon,
				sb, &sec->queue);
	if (ret)
		return ret;

	return ver;
}