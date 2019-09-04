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
struct nvkm_device {int chipset; } ;
struct io_mapping {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NV04_PFB_CFG0 ; 
 int /*<<< orphan*/  NV10_PFB_REFCTRL ; 
 int /*<<< orphan*/  NV10_PFB_REFCTRL_VALID_1 ; 
 int /*<<< orphan*/  fbmem_fini (struct io_mapping*) ; 
 struct io_mapping* fbmem_init (struct nvkm_device*) ; 
 int fbmem_peek (struct io_mapping*,int) ; 
 int /*<<< orphan*/  fbmem_poke (struct io_mapping*,int,int) ; 
 int /*<<< orphan*/  nvkm_error (struct nvkm_subdev*,char*) ; 
 int /*<<< orphan*/  nvkm_mask (struct nvkm_device*,int /*<<< orphan*/ ,int,int) ; 
 int nvkm_rd32 (struct nvkm_device*,int) ; 
 int /*<<< orphan*/  nvkm_wr32 (struct nvkm_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
nv20_devinit_meminit(struct nvkm_devinit *init)
{
	struct nvkm_subdev *subdev = &init->subdev;
	struct nvkm_device *device = subdev->device;
	uint32_t mask = (device->chipset >= 0x25 ? 0x300 : 0x900);
	uint32_t amount, off;
	struct io_mapping *fb;

	/* Map the framebuffer aperture */
	fb = fbmem_init(device);
	if (!fb) {
		nvkm_error(subdev, "failed to map fb\n");
		return;
	}

	nvkm_wr32(device, NV10_PFB_REFCTRL, NV10_PFB_REFCTRL_VALID_1);

	/* Allow full addressing */
	nvkm_mask(device, NV04_PFB_CFG0, 0, mask);

	amount = nvkm_rd32(device, 0x10020c);
	for (off = amount; off > 0x2000000; off -= 0x2000000)
		fbmem_poke(fb, off - 4, off);

	amount = nvkm_rd32(device, 0x10020c);
	if (amount != fbmem_peek(fb, amount - 4))
		/* IC missing - disable the upper half memory space. */
		nvkm_mask(device, NV04_PFB_CFG0, mask, 0);

	fbmem_fini(fb);
}