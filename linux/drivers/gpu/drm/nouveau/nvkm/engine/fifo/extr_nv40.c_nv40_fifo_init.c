#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct nvkm_ramht {int bits; TYPE_3__* gpuobj; } ;
struct nvkm_memory {int dummy; } ;
struct nvkm_instmem {struct nvkm_memory* ramfc; struct nvkm_memory* ramro; struct nvkm_ramht* ramht; } ;
struct nvkm_fifo {int dummy; } ;
struct nvkm_fb {TYPE_4__* ram; } ;
struct nvkm_device {int chipset; struct nvkm_instmem* imem; struct nvkm_fb* fb; } ;
struct TYPE_6__ {struct nvkm_device* device; } ;
struct TYPE_7__ {TYPE_1__ subdev; } ;
struct TYPE_10__ {int nr; TYPE_2__ engine; } ;
struct nv04_fifo {TYPE_5__ base; } ;
struct TYPE_9__ {int /*<<< orphan*/  size; } ;
struct TYPE_8__ {int addr; } ;

/* Variables and functions */
 int NV03_PFIFO_CACHE1_PUSH0 ; 
 int NV03_PFIFO_CACHE1_PUSH1 ; 
 int NV03_PFIFO_CACHES ; 
 int NV03_PFIFO_INTR_0 ; 
 int NV03_PFIFO_INTR_EN_0 ; 
 int NV03_PFIFO_RAMHT ; 
 int NV03_PFIFO_RAMRO ; 
 int NV04_PFIFO_CACHE1_PULL0 ; 
 struct nv04_fifo* nv04_fifo (struct nvkm_fifo*) ; 
 int nvkm_memory_addr (struct nvkm_memory*) ; 
 int /*<<< orphan*/  nvkm_wr32 (struct nvkm_device*,int,int) ; 

__attribute__((used)) static void
nv40_fifo_init(struct nvkm_fifo *base)
{
	struct nv04_fifo *fifo = nv04_fifo(base);
	struct nvkm_device *device = fifo->base.engine.subdev.device;
	struct nvkm_fb *fb = device->fb;
	struct nvkm_instmem *imem = device->imem;
	struct nvkm_ramht *ramht = imem->ramht;
	struct nvkm_memory *ramro = imem->ramro;
	struct nvkm_memory *ramfc = imem->ramfc;

	nvkm_wr32(device, 0x002040, 0x000000ff);
	nvkm_wr32(device, 0x002044, 0x2101ffff);
	nvkm_wr32(device, 0x002058, 0x00000001);

	nvkm_wr32(device, NV03_PFIFO_RAMHT, (0x03 << 24) /* search 128 */ |
					    ((ramht->bits - 9) << 16) |
					    (ramht->gpuobj->addr >> 8));
	nvkm_wr32(device, NV03_PFIFO_RAMRO, nvkm_memory_addr(ramro) >> 8);

	switch (device->chipset) {
	case 0x47:
	case 0x49:
	case 0x4b:
		nvkm_wr32(device, 0x002230, 0x00000001);
		/* fall through */
	case 0x40:
	case 0x41:
	case 0x42:
	case 0x43:
	case 0x45:
	case 0x48:
		nvkm_wr32(device, 0x002220, 0x00030002);
		break;
	default:
		nvkm_wr32(device, 0x002230, 0x00000000);
		nvkm_wr32(device, 0x002220, ((fb->ram->size - 512 * 1024 +
					      nvkm_memory_addr(ramfc)) >> 16) |
					    0x00030000);
		break;
	}

	nvkm_wr32(device, NV03_PFIFO_CACHE1_PUSH1, fifo->base.nr - 1);

	nvkm_wr32(device, NV03_PFIFO_INTR_0, 0xffffffff);
	nvkm_wr32(device, NV03_PFIFO_INTR_EN_0, 0xffffffff);

	nvkm_wr32(device, NV03_PFIFO_CACHE1_PUSH0, 1);
	nvkm_wr32(device, NV04_PFIFO_CACHE1_PULL0, 1);
	nvkm_wr32(device, NV03_PFIFO_CACHES, 1);
}