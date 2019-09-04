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

__attribute__((used)) static int
gf100_volt_speedo_read(struct nvkm_volt *volt)
{
	struct nvkm_device *device = volt->subdev.device;
	struct nvkm_fuse *fuse = device->fuse;

	if (!fuse)
		return -EINVAL;

	return nvkm_fuse_read(fuse, 0x1cc);
}