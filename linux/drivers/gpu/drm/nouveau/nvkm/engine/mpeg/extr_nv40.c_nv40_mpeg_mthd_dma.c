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
struct nvkm_subdev {int dummy; } ;
struct nvkm_instmem {int dummy; } ;
struct nvkm_device {int /*<<< orphan*/  mpeg; struct nvkm_instmem* imem; } ;
struct TYPE_2__ {struct nvkm_subdev subdev; } ;
struct nv31_mpeg {TYPE_1__ engine; } ;

/* Variables and functions */
 struct nv31_mpeg* nv31_mpeg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvkm_error (struct nvkm_subdev*,char*,int,int,int,int) ; 
 int nvkm_instmem_rd32 (struct nvkm_instmem*,int) ; 
 int /*<<< orphan*/  nvkm_mask (struct nvkm_device*,int,int,int) ; 
 int /*<<< orphan*/  nvkm_wr32 (struct nvkm_device*,int,int) ; 

bool
nv40_mpeg_mthd_dma(struct nvkm_device *device, u32 mthd, u32 data)
{
	struct nvkm_instmem *imem = device->imem;
	struct nv31_mpeg *mpeg = nv31_mpeg(device->mpeg);
	struct nvkm_subdev *subdev = &mpeg->engine.subdev;
	u32 inst = data << 4;
	u32 dma0 = nvkm_instmem_rd32(imem, inst + 0);
	u32 dma1 = nvkm_instmem_rd32(imem, inst + 4);
	u32 dma2 = nvkm_instmem_rd32(imem, inst + 8);
	u32 base = (dma2 & 0xfffff000) | (dma0 >> 20);
	u32 size = dma1 + 1;

	/* only allow linear DMA objects */
	if (!(dma0 & 0x00002000)) {
		nvkm_error(subdev, "inst %08x dma0 %08x dma1 %08x dma2 %08x\n",
			   inst, dma0, dma1, dma2);
		return false;
	}

	if (mthd == 0x0190) {
		/* DMA_CMD */
		nvkm_mask(device, 0x00b300, 0x00030000, (dma0 & 0x00030000));
		nvkm_wr32(device, 0x00b334, base);
		nvkm_wr32(device, 0x00b324, size);
	} else
	if (mthd == 0x01a0) {
		/* DMA_DATA */
		nvkm_mask(device, 0x00b300, 0x000c0000, (dma0 & 0x00030000) << 2);
		nvkm_wr32(device, 0x00b360, base);
		nvkm_wr32(device, 0x00b364, size);
	} else {
		/* DMA_IMAGE, VRAM only */
		if (dma0 & 0x00030000)
			return false;

		nvkm_wr32(device, 0x00b370, base);
		nvkm_wr32(device, 0x00b374, size);
	}

	return true;
}