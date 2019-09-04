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
struct nvkm_top_func {int dummy; } ;
struct nvkm_top {int /*<<< orphan*/  device; struct nvkm_top_func const* func; int /*<<< orphan*/  subdev; } ;
struct nvkm_device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct nvkm_top* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvkm_subdev_ctor (int /*<<< orphan*/ *,struct nvkm_device*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvkm_top ; 

int
nvkm_top_new_(const struct nvkm_top_func *func, struct nvkm_device *device,
	      int index, struct nvkm_top **ptop)
{
	struct nvkm_top *top;
	if (!(top = *ptop = kzalloc(sizeof(*top), GFP_KERNEL)))
		return -ENOMEM;
	nvkm_subdev_ctor(&nvkm_top, device, index, &top->subdev);
	top->func = func;
	INIT_LIST_HEAD(&top->device);
	return 0;
}