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
struct nvkm_devinit_func {int dummy; } ;
struct nvkm_devinit {int /*<<< orphan*/  force_post; struct nvkm_devinit_func const* func; int /*<<< orphan*/  subdev; } ;
struct nvkm_device {int /*<<< orphan*/  cfgopt; } ;

/* Variables and functions */
 int /*<<< orphan*/  nvkm_boolopt (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  nvkm_devinit ; 
 int /*<<< orphan*/  nvkm_subdev_ctor (int /*<<< orphan*/ *,struct nvkm_device*,int,int /*<<< orphan*/ *) ; 

void
nvkm_devinit_ctor(const struct nvkm_devinit_func *func,
		  struct nvkm_device *device, int index,
		  struct nvkm_devinit *init)
{
	nvkm_subdev_ctor(&nvkm_devinit, device, index, &init->subdev);
	init->func = func;
	init->force_post = nvkm_boolopt(device->cfgopt, "NvForcePost", false);
}