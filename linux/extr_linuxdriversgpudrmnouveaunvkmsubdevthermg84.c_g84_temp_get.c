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
struct TYPE_2__ {struct nvkm_device* device; } ;
struct nvkm_therm {TYPE_1__ subdev; } ;
struct nvkm_device {int /*<<< orphan*/  fuse; } ;

/* Variables and functions */
 int ENODEV ; 
 int nvkm_fuse_read (int /*<<< orphan*/ ,int) ; 
 int nvkm_rd32 (struct nvkm_device*,int) ; 

int
g84_temp_get(struct nvkm_therm *therm)
{
	struct nvkm_device *device = therm->subdev.device;

	if (nvkm_fuse_read(device->fuse, 0x1a8) == 1)
		return nvkm_rd32(device, 0x20400);
	else
		return -ENODEV;
}