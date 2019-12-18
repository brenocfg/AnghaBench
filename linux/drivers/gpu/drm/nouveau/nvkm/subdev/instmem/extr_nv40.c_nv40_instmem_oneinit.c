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
struct nvkm_instmem {int dummy; } ;
struct nvkm_device {int chipset; } ;
struct TYPE_3__ {struct nvkm_device* device; } ;
struct TYPE_4__ {int reserved; int /*<<< orphan*/  ramfc; int /*<<< orphan*/  ramro; int /*<<< orphan*/  ramht; int /*<<< orphan*/  vbios; TYPE_1__ subdev; } ;
struct nv40_instmem {TYPE_2__ base; int /*<<< orphan*/  heap; } ;

/* Variables and functions */
 int /*<<< orphan*/  NVKM_MEM_TARGET_INST ; 
 int hweight8 (int) ; 
 struct nv40_instmem* nv40_instmem (struct nvkm_instmem*) ; 
 scalar_t__ nv44_gr_class (struct nvkm_device*) ; 
 int nvkm_memory_new (struct nvkm_device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int nvkm_mm_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int nvkm_ramht_new (struct nvkm_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int nvkm_rd32 (struct nvkm_device*,int) ; 
 int round_up (int,int) ; 

__attribute__((used)) static int
nv40_instmem_oneinit(struct nvkm_instmem *base)
{
	struct nv40_instmem *imem = nv40_instmem(base);
	struct nvkm_device *device = imem->base.subdev.device;
	int ret, vs;

	/* PRAMIN aperture maps over the end of vram, reserve enough space
	 * to fit graphics contexts for every channel, the magics come
	 * from engine/gr/nv40.c
	 */
	vs = hweight8((nvkm_rd32(device, 0x001540) & 0x0000ff00) >> 8);
	if      (device->chipset == 0x40) imem->base.reserved = 0x6aa0 * vs;
	else if (device->chipset  < 0x43) imem->base.reserved = 0x4f00 * vs;
	else if (nv44_gr_class(device))   imem->base.reserved = 0x4980 * vs;
	else				  imem->base.reserved = 0x4a40 * vs;
	imem->base.reserved += 16 * 1024;
	imem->base.reserved *= 32;		/* per-channel */
	imem->base.reserved += 512 * 1024;	/* pci(e)gart table */
	imem->base.reserved += 512 * 1024;	/* object storage */
	imem->base.reserved = round_up(imem->base.reserved, 4096);

	ret = nvkm_mm_init(&imem->heap, 0, 0, imem->base.reserved, 1);
	if (ret)
		return ret;

	/* 0x00000-0x10000: reserve for probable vbios image */
	ret = nvkm_memory_new(device, NVKM_MEM_TARGET_INST, 0x10000, 0, false,
			      &imem->base.vbios);
	if (ret)
		return ret;

	/* 0x10000-0x18000: reserve for RAMHT */
	ret = nvkm_ramht_new(device, 0x08000, 0, NULL, &imem->base.ramht);
	if (ret)
		return ret;

	/* 0x18000-0x18200: reserve for RAMRO
	 * 0x18200-0x20000: padding
	 */
	ret = nvkm_memory_new(device, NVKM_MEM_TARGET_INST, 0x08000, 0, false,
			      &imem->base.ramro);
	if (ret)
		return ret;

	/* 0x20000-0x21000: reserve for RAMFC
	 * 0x21000-0x40000: padding and some unknown crap
	 */
	ret = nvkm_memory_new(device, NVKM_MEM_TARGET_INST, 0x20000, 0, true,
			      &imem->base.ramfc);
	if (ret)
		return ret;

	return 0;
}