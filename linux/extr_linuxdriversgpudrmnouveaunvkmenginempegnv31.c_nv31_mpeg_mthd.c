#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct nvkm_device {int dummy; } ;
struct TYPE_4__ {struct nvkm_device* device; } ;
struct TYPE_5__ {TYPE_1__ subdev; } ;
struct nv31_mpeg {TYPE_3__* func; TYPE_2__ engine; } ;
struct TYPE_6__ {int (* mthd_dma ) (struct nvkm_device*,int,int) ;} ;

/* Variables and functions */
 int stub1 (struct nvkm_device*,int,int) ; 

__attribute__((used)) static bool
nv31_mpeg_mthd(struct nv31_mpeg *mpeg, u32 mthd, u32 data)
{
	struct nvkm_device *device = mpeg->engine.subdev.device;
	switch (mthd) {
	case 0x190:
	case 0x1a0:
	case 0x1b0:
		return mpeg->func->mthd_dma(device, mthd, data);
	default:
		break;
	}
	return false;
}