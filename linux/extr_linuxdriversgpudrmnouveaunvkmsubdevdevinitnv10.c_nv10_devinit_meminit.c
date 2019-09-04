#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int uint32_t ;
struct nvkm_subdev {struct nvkm_device* device; } ;
struct nvkm_devinit {struct nvkm_subdev subdev; } ;
struct nvkm_device {scalar_t__ card_type; int chipset; } ;
struct io_mapping {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NV04_PFB_CFG0 ; 
 int /*<<< orphan*/  NV10_PFB_REFCTRL ; 
 int /*<<< orphan*/  NV10_PFB_REFCTRL_VALID_1 ; 
 scalar_t__ NV_11 ; 
 int /*<<< orphan*/  fbmem_fini (struct io_mapping*) ; 
 struct io_mapping* fbmem_init (struct nvkm_device*) ; 
 int fbmem_peek (struct io_mapping*,int) ; 
 int /*<<< orphan*/  fbmem_poke (struct io_mapping*,int,int) ; 
 int /*<<< orphan*/  nvkm_error (struct nvkm_subdev*,char*) ; 
 int /*<<< orphan*/  nvkm_mask (struct nvkm_device*,int /*<<< orphan*/ ,int,int const) ; 
 int nvkm_rd32 (struct nvkm_device*,int) ; 
 int /*<<< orphan*/  nvkm_wr32 (struct nvkm_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
nv10_devinit_meminit(struct nvkm_devinit *init)
{
	struct nvkm_subdev *subdev = &init->subdev;
	struct nvkm_device *device = subdev->device;
	static const int mem_width[] = { 0x10, 0x00, 0x20 };
	int mem_width_count;
	uint32_t patt = 0xdeadbeef;
	struct io_mapping *fb;
	int i, j, k;

	if (device->card_type >= NV_11 && device->chipset >= 0x17)
		mem_width_count = 3;
	else
		mem_width_count = 2;

	/* Map the framebuffer aperture */
	fb = fbmem_init(device);
	if (!fb) {
		nvkm_error(subdev, "failed to map fb\n");
		return;
	}

	nvkm_wr32(device, NV10_PFB_REFCTRL, NV10_PFB_REFCTRL_VALID_1);

	/* Probe memory bus width */
	for (i = 0; i < mem_width_count; i++) {
		nvkm_mask(device, NV04_PFB_CFG0, 0x30, mem_width[i]);

		for (j = 0; j < 4; j++) {
			for (k = 0; k < 4; k++)
				fbmem_poke(fb, 0x1c, 0);

			fbmem_poke(fb, 0x1c, patt);
			fbmem_poke(fb, 0x3c, 0);

			if (fbmem_peek(fb, 0x1c) == patt)
				goto mem_width_found;
		}
	}

mem_width_found:
	patt <<= 1;

	/* Probe amount of installed memory */
	for (i = 0; i < 4; i++) {
		int off = nvkm_rd32(device, 0x10020c) - 0x100000;

		fbmem_poke(fb, off, patt);
		fbmem_poke(fb, 0, 0);

		fbmem_peek(fb, 0);
		fbmem_peek(fb, 0);
		fbmem_peek(fb, 0);
		fbmem_peek(fb, 0);

		if (fbmem_peek(fb, off) == patt)
			goto amount_found;
	}

	/* IC missing - disable the upper half memory space. */
	nvkm_mask(device, NV04_PFB_CFG0, 0x1000, 0);

amount_found:
	fbmem_fini(fb);
}