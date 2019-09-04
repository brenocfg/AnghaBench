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
typedef  int u32 ;
struct TYPE_2__ {struct nvkm_device* device; } ;
struct nvkm_mc {TYPE_1__ subdev; } ;
struct nvkm_device {int dummy; } ;

/* Variables and functions */
 int nvkm_rd32 (struct nvkm_device*,int) ; 

u32
gf100_mc_intr_stat(struct nvkm_mc *mc)
{
	struct nvkm_device *device = mc->subdev.device;
	u32 intr0 = nvkm_rd32(device, 0x000100);
	u32 intr1 = nvkm_rd32(device, 0x000104);
	return intr0 | intr1;
}