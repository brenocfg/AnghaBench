#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {struct nvkm_device* device; } ;
struct TYPE_4__ {TYPE_1__ subdev; } ;
struct nvkm_disp {TYPE_2__ engine; } ;
struct nvkm_device {int dummy; } ;

/* Variables and functions */
 int nvkm_rd32 (struct nvkm_device*,int) ; 

int
gv100_disp_wndw_cnt(struct nvkm_disp *disp, unsigned long *pmask)
{
	struct nvkm_device *device = disp->engine.subdev.device;
	*pmask = nvkm_rd32(device, 0x610064);
	return (nvkm_rd32(device, 0x610074) & 0x03f00000) >> 20;
}