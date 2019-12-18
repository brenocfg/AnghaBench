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
struct nvkm_gsp {int /*<<< orphan*/  subdev; } ;
struct nvkm_device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  gv100_gsp ; 
 struct nvkm_gsp* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvkm_subdev_ctor (int /*<<< orphan*/ *,struct nvkm_device*,int,int /*<<< orphan*/ *) ; 

int
gv100_gsp_new(struct nvkm_device *device, int index, struct nvkm_gsp **pgsp)
{
	struct nvkm_gsp *gsp;

	if (!(gsp = *pgsp = kzalloc(sizeof(*gsp), GFP_KERNEL)))
		return -ENOMEM;

	nvkm_subdev_ctor(&gv100_gsp, device, index, &gsp->subdev);
	return 0;
}