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
struct nvkm_subdev {struct nvkm_device* device; } ;
struct nvkm_devinit {int dummy; } ;
struct nvkm_device {int dummy; } ;
struct TYPE_2__ {int post; struct nvkm_subdev subdev; } ;
struct nv04_devinit {scalar_t__ owner; TYPE_1__ base; } ;

/* Variables and functions */
 struct nv04_devinit* nv04_devinit (struct nvkm_devinit*) ; 
 int /*<<< orphan*/  nvkm_debug (struct nvkm_subdev*,char*) ; 
 int /*<<< orphan*/  nvkm_mask (struct nvkm_device*,int,int,int) ; 
 int nvkm_rdvgac (struct nvkm_device*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ nvkm_rdvgaowner (struct nvkm_device*) ; 
 int /*<<< orphan*/  nvkm_wrvgaowner (struct nvkm_device*,int /*<<< orphan*/ ) ; 

void
nv04_devinit_preinit(struct nvkm_devinit *base)
{
	struct nv04_devinit *init = nv04_devinit(base);
	struct nvkm_subdev *subdev = &init->base.subdev;
	struct nvkm_device *device = subdev->device;

	/* make i2c busses accessible */
	nvkm_mask(device, 0x000200, 0x00000001, 0x00000001);

	/* unslave crtcs */
	if (init->owner < 0)
		init->owner = nvkm_rdvgaowner(device);
	nvkm_wrvgaowner(device, 0);

	if (!init->base.post) {
		u32 htotal = nvkm_rdvgac(device, 0, 0x06);
		htotal |= (nvkm_rdvgac(device, 0, 0x07) & 0x01) << 8;
		htotal |= (nvkm_rdvgac(device, 0, 0x07) & 0x20) << 4;
		htotal |= (nvkm_rdvgac(device, 0, 0x25) & 0x01) << 10;
		htotal |= (nvkm_rdvgac(device, 0, 0x41) & 0x01) << 11;
		if (!htotal) {
			nvkm_debug(subdev, "adaptor not initialised\n");
			init->base.post = true;
		}
	}
}