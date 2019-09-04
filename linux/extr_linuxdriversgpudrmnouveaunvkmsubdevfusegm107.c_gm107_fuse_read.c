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
typedef  scalar_t__ u32 ;
struct TYPE_2__ {struct nvkm_device* device; } ;
struct nvkm_fuse {TYPE_1__ subdev; } ;
struct nvkm_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ nvkm_rd32 (struct nvkm_device*,scalar_t__) ; 

__attribute__((used)) static u32
gm107_fuse_read(struct nvkm_fuse *fuse, u32 addr)
{
	struct nvkm_device *device = fuse->subdev.device;
	return nvkm_rd32(device, 0x021100 + addr);
}