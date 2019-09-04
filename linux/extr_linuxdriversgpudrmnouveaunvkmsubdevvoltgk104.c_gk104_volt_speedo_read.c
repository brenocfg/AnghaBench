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
struct nvkm_volt {TYPE_1__ subdev; } ;
struct nvkm_fuse {int dummy; } ;
struct nvkm_device {struct nvkm_fuse* fuse; } ;

/* Variables and functions */
 int EINVAL ; 
 int nvkm_fuse_read (struct nvkm_fuse*,int) ; 
 int /*<<< orphan*/  nvkm_wr32 (struct nvkm_device*,int,int) ; 

__attribute__((used)) static int
gk104_volt_speedo_read(struct nvkm_volt *volt)
{
	struct nvkm_device *device = volt->subdev.device;
	struct nvkm_fuse *fuse = device->fuse;
	int ret;

	if (!fuse)
		return -EINVAL;

	nvkm_wr32(device, 0x122634, 0x0);
	ret = nvkm_fuse_read(fuse, 0x3a8);
	nvkm_wr32(device, 0x122634, 0x41);
	return ret;
}