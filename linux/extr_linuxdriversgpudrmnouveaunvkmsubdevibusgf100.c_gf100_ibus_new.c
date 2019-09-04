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
struct nvkm_subdev {int dummy; } ;
struct nvkm_device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  gf100_ibus ; 
 struct nvkm_subdev* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvkm_subdev_ctor (int /*<<< orphan*/ *,struct nvkm_device*,int,struct nvkm_subdev*) ; 

int
gf100_ibus_new(struct nvkm_device *device, int index,
	       struct nvkm_subdev **pibus)
{
	struct nvkm_subdev *ibus;
	if (!(ibus = *pibus = kzalloc(sizeof(*ibus), GFP_KERNEL)))
		return -ENOMEM;
	nvkm_subdev_ctor(&gf100_ibus, device, index, ibus);
	return 0;
}