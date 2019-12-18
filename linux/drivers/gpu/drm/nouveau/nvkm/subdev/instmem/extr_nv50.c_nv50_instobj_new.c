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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct nvkm_memory {int dummy; } ;
struct nvkm_instmem {int dummy; } ;
struct nvkm_device {int dummy; } ;
struct TYPE_6__ {struct nvkm_memory memory; } ;
struct nv50_instobj {int /*<<< orphan*/  ram; int /*<<< orphan*/  lru; int /*<<< orphan*/  maps; struct nv50_instmem* imem; TYPE_3__ base; } ;
struct TYPE_4__ {struct nvkm_device* device; } ;
struct TYPE_5__ {TYPE_1__ subdev; } ;
struct nv50_instmem {TYPE_2__ base; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct nv50_instobj* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  max (int /*<<< orphan*/ ,int) ; 
 struct nv50_instmem* nv50_instmem (struct nvkm_instmem*) ; 
 int /*<<< orphan*/  nv50_instobj_func ; 
 int /*<<< orphan*/  nvkm_instobj_ctor (int /*<<< orphan*/ *,TYPE_2__*,TYPE_3__*) ; 
 int nvkm_ram_get (struct nvkm_device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  order_base_2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nv50_instobj_new(struct nvkm_instmem *base, u32 size, u32 align, bool zero,
		 struct nvkm_memory **pmemory)
{
	struct nv50_instmem *imem = nv50_instmem(base);
	struct nv50_instobj *iobj;
	struct nvkm_device *device = imem->base.subdev.device;
	u8 page = max(order_base_2(align), 12);

	if (!(iobj = kzalloc(sizeof(*iobj), GFP_KERNEL)))
		return -ENOMEM;
	*pmemory = &iobj->base.memory;

	nvkm_instobj_ctor(&nv50_instobj_func, &imem->base, &iobj->base);
	iobj->imem = imem;
	refcount_set(&iobj->maps, 0);
	INIT_LIST_HEAD(&iobj->lru);

	return nvkm_ram_get(device, 0, 1, page, size, true, true, &iobj->ram);
}