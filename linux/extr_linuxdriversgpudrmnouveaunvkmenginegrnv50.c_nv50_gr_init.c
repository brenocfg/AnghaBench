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
struct nvkm_device {int chipset; } ;
struct TYPE_4__ {struct nvkm_device* device; } ;
struct TYPE_5__ {TYPE_1__ subdev; } ;
struct TYPE_6__ {TYPE_2__ engine; } ;
struct nv50_gr {int /*<<< orphan*/  size; TYPE_3__ base; } ;

/* Variables and functions */
 struct nv50_gr* nv50_gr (struct nvkm_gr*) ; 
 int nv50_grctx_init (struct nvkm_device*,int /*<<< orphan*/ *) ; 
 int nvkm_rd32 (struct nvkm_device*,int) ; 
 int /*<<< orphan*/  nvkm_wr32 (struct nvkm_device*,int,int) ; 

int
nv50_gr_init(struct nvkm_gr *base)
{
	struct nv50_gr *gr = nv50_gr(base);
	struct nvkm_device *device = gr->base.engine.subdev.device;
	int ret, units, i;

	/* NV_PGRAPH_DEBUG_3_HW_CTX_SWITCH_ENABLED */
	nvkm_wr32(device, 0x40008c, 0x00000004);

	/* reset/enable traps and interrupts */
	nvkm_wr32(device, 0x400804, 0xc0000000);
	nvkm_wr32(device, 0x406800, 0xc0000000);
	nvkm_wr32(device, 0x400c04, 0xc0000000);
	nvkm_wr32(device, 0x401800, 0xc0000000);
	nvkm_wr32(device, 0x405018, 0xc0000000);
	nvkm_wr32(device, 0x402000, 0xc0000000);

	units = nvkm_rd32(device, 0x001540);
	for (i = 0; i < 16; i++) {
		if (!(units & (1 << i)))
			continue;

		if (device->chipset < 0xa0) {
			nvkm_wr32(device, 0x408900 + (i << 12), 0xc0000000);
			nvkm_wr32(device, 0x408e08 + (i << 12), 0xc0000000);
			nvkm_wr32(device, 0x408314 + (i << 12), 0xc0000000);
		} else {
			nvkm_wr32(device, 0x408600 + (i << 11), 0xc0000000);
			nvkm_wr32(device, 0x408708 + (i << 11), 0xc0000000);
			nvkm_wr32(device, 0x40831c + (i << 11), 0xc0000000);
		}
	}

	nvkm_wr32(device, 0x400108, 0xffffffff);
	nvkm_wr32(device, 0x400138, 0xffffffff);
	nvkm_wr32(device, 0x400100, 0xffffffff);
	nvkm_wr32(device, 0x40013c, 0xffffffff);
	nvkm_wr32(device, 0x400500, 0x00010001);

	/* upload context program, initialise ctxctl defaults */
	ret = nv50_grctx_init(device, &gr->size);
	if (ret)
		return ret;

	nvkm_wr32(device, 0x400824, 0x00000000);
	nvkm_wr32(device, 0x400828, 0x00000000);
	nvkm_wr32(device, 0x40082c, 0x00000000);
	nvkm_wr32(device, 0x400830, 0x00000000);
	nvkm_wr32(device, 0x40032c, 0x00000000);
	nvkm_wr32(device, 0x400330, 0x00000000);

	/* some unknown zcull magic */
	switch (device->chipset & 0xf0) {
	case 0x50:
	case 0x80:
	case 0x90:
		nvkm_wr32(device, 0x402ca8, 0x00000800);
		break;
	case 0xa0:
	default:
		if (device->chipset == 0xa0 ||
		    device->chipset == 0xaa ||
		    device->chipset == 0xac) {
			nvkm_wr32(device, 0x402ca8, 0x00000802);
		} else {
			nvkm_wr32(device, 0x402cc0, 0x00000000);
			nvkm_wr32(device, 0x402ca8, 0x00000002);
		}

		break;
	}

	/* zero out zcull regions */
	for (i = 0; i < 8; i++) {
		nvkm_wr32(device, 0x402c20 + (i * 0x10), 0x00000000);
		nvkm_wr32(device, 0x402c24 + (i * 0x10), 0x00000000);
		nvkm_wr32(device, 0x402c28 + (i * 0x10), 0x00000000);
		nvkm_wr32(device, 0x402c2c + (i * 0x10), 0x00000000);
	}

	return 0;
}