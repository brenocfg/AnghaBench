#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_8__ {int oclass; } ;
struct nvkm_oclass {TYPE_4__ base; } ;
struct nvkm_dmaobj {int target; int access; } ;
struct TYPE_5__ {struct nvkm_device* device; } ;
struct TYPE_6__ {TYPE_1__ subdev; } ;
struct nvkm_dma {TYPE_2__ engine; } ;
struct nvkm_device {TYPE_3__* mmu; } ;
struct nv04_dmaobj {int clone; int flags0; int flags2; struct nvkm_dmaobj base; } ;
struct TYPE_7__ {int /*<<< orphan*/ * func; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
#define  NV_MEM_ACCESS_RO 133 
#define  NV_MEM_ACCESS_RW 132 
#define  NV_MEM_ACCESS_WO 131 
#define  NV_MEM_TARGET_PCI 130 
#define  NV_MEM_TARGET_PCI_NOSNOOP 129 
 int NV_MEM_TARGET_VM ; 
#define  NV_MEM_TARGET_VRAM 128 
 struct nv04_dmaobj* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nv04_dmaobj_func ; 
 int /*<<< orphan*/  nv04_mmu ; 
 int nvkm_dmaobj_ctor (int /*<<< orphan*/ *,struct nvkm_dma*,struct nvkm_oclass const*,void**,int /*<<< orphan*/ *,struct nvkm_dmaobj*) ; 

int
nv04_dmaobj_new(struct nvkm_dma *dma, const struct nvkm_oclass *oclass,
		void *data, u32 size, struct nvkm_dmaobj **pdmaobj)
{
	struct nvkm_device *device = dma->engine.subdev.device;
	struct nv04_dmaobj *dmaobj;
	int ret;

	if (!(dmaobj = kzalloc(sizeof(*dmaobj), GFP_KERNEL)))
		return -ENOMEM;
	*pdmaobj = &dmaobj->base;

	ret = nvkm_dmaobj_ctor(&nv04_dmaobj_func, dma, oclass,
			       &data, &size, &dmaobj->base);
	if (ret)
		return ret;

	if (dmaobj->base.target == NV_MEM_TARGET_VM) {
		if (device->mmu->func == &nv04_mmu)
			dmaobj->clone = true;
		dmaobj->base.target = NV_MEM_TARGET_PCI;
		dmaobj->base.access = NV_MEM_ACCESS_RW;
	}

	dmaobj->flags0 = oclass->base.oclass;
	switch (dmaobj->base.target) {
	case NV_MEM_TARGET_VRAM:
		dmaobj->flags0 |= 0x00003000;
		break;
	case NV_MEM_TARGET_PCI:
		dmaobj->flags0 |= 0x00023000;
		break;
	case NV_MEM_TARGET_PCI_NOSNOOP:
		dmaobj->flags0 |= 0x00033000;
		break;
	default:
		return -EINVAL;
	}

	switch (dmaobj->base.access) {
	case NV_MEM_ACCESS_RO:
		dmaobj->flags0 |= 0x00004000;
		break;
	case NV_MEM_ACCESS_WO:
		dmaobj->flags0 |= 0x00008000;
		/* fall through */
	case NV_MEM_ACCESS_RW:
		dmaobj->flags2 |= 0x00000002;
		break;
	default:
		return -EINVAL;
	}

	return 0;
}