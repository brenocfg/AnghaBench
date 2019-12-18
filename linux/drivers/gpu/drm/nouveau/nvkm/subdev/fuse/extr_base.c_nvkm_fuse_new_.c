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
struct nvkm_fuse_func {int dummy; } ;
struct nvkm_fuse {int /*<<< orphan*/  lock; struct nvkm_fuse_func const* func; int /*<<< orphan*/  subdev; } ;
struct nvkm_device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct nvkm_fuse* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvkm_fuse ; 
 int /*<<< orphan*/  nvkm_subdev_ctor (int /*<<< orphan*/ *,struct nvkm_device*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int
nvkm_fuse_new_(const struct nvkm_fuse_func *func, struct nvkm_device *device,
	       int index, struct nvkm_fuse **pfuse)
{
	struct nvkm_fuse *fuse;
	if (!(fuse = *pfuse = kzalloc(sizeof(*fuse), GFP_KERNEL)))
		return -ENOMEM;
	nvkm_subdev_ctor(&nvkm_fuse, device, index, &fuse->subdev);
	fuse->func = func;
	spin_lock_init(&fuse->lock);
	return 0;
}