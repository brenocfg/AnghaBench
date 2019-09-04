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
struct nvkm_gr {int dummy; } ;
struct nvkm_device {scalar_t__ card_type; int chipset; } ;
struct TYPE_4__ {struct nvkm_device* device; } ;
struct TYPE_5__ {TYPE_1__ subdev; } ;
struct TYPE_6__ {TYPE_2__ engine; } ;
struct nv10_gr {TYPE_3__ base; } ;

/* Variables and functions */
 int NV03_PGRAPH_INTR ; 
 int NV03_PGRAPH_INTR_EN ; 
 int NV04_PGRAPH_DEBUG_0 ; 
 int NV04_PGRAPH_DEBUG_1 ; 
 int NV04_PGRAPH_DEBUG_2 ; 
 int NV04_PGRAPH_DEBUG_3 ; 
 int NV10_PGRAPH_CTX_CONTROL ; 
 int NV10_PGRAPH_CTX_SWITCH (int) ; 
 int /*<<< orphan*/  NV10_PGRAPH_CTX_USER ; 
 int NV10_PGRAPH_DEBUG_4 ; 
 int NV10_PGRAPH_FFINTFC_ST2 ; 
 int NV10_PGRAPH_STATE ; 
 scalar_t__ NV_11 ; 
 struct nv10_gr* nv10_gr (struct nvkm_gr*) ; 
 int /*<<< orphan*/  nvkm_mask (struct nvkm_device*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  nvkm_wr32 (struct nvkm_device*,int,int) ; 

int
nv10_gr_init(struct nvkm_gr *base)
{
	struct nv10_gr *gr = nv10_gr(base);
	struct nvkm_device *device = gr->base.engine.subdev.device;

	nvkm_wr32(device, NV03_PGRAPH_INTR   , 0xFFFFFFFF);
	nvkm_wr32(device, NV03_PGRAPH_INTR_EN, 0xFFFFFFFF);

	nvkm_wr32(device, NV04_PGRAPH_DEBUG_0, 0xFFFFFFFF);
	nvkm_wr32(device, NV04_PGRAPH_DEBUG_0, 0x00000000);
	nvkm_wr32(device, NV04_PGRAPH_DEBUG_1, 0x00118700);
	/* nvkm_wr32(device, NV04_PGRAPH_DEBUG_2, 0x24E00810); */ /* 0x25f92ad9 */
	nvkm_wr32(device, NV04_PGRAPH_DEBUG_2, 0x25f92ad9);
	nvkm_wr32(device, NV04_PGRAPH_DEBUG_3, 0x55DE0830 | (1 << 29) | (1 << 31));

	if (device->card_type >= NV_11 && device->chipset >= 0x17) {
		nvkm_wr32(device, NV10_PGRAPH_DEBUG_4, 0x1f000000);
		nvkm_wr32(device, 0x400a10, 0x03ff3fb6);
		nvkm_wr32(device, 0x400838, 0x002f8684);
		nvkm_wr32(device, 0x40083c, 0x00115f3f);
		nvkm_wr32(device, 0x4006b0, 0x40000020);
	} else {
		nvkm_wr32(device, NV10_PGRAPH_DEBUG_4, 0x00000000);
	}

	nvkm_wr32(device, NV10_PGRAPH_CTX_SWITCH(0), 0x00000000);
	nvkm_wr32(device, NV10_PGRAPH_CTX_SWITCH(1), 0x00000000);
	nvkm_wr32(device, NV10_PGRAPH_CTX_SWITCH(2), 0x00000000);
	nvkm_wr32(device, NV10_PGRAPH_CTX_SWITCH(3), 0x00000000);
	nvkm_wr32(device, NV10_PGRAPH_CTX_SWITCH(4), 0x00000000);
	nvkm_wr32(device, NV10_PGRAPH_STATE, 0xFFFFFFFF);

	nvkm_mask(device, NV10_PGRAPH_CTX_USER, 0xff000000, 0x1f000000);
	nvkm_wr32(device, NV10_PGRAPH_CTX_CONTROL, 0x10000100);
	nvkm_wr32(device, NV10_PGRAPH_FFINTFC_ST2, 0x08000000);
	return 0;
}