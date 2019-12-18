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
typedef  int u32 ;
struct nvkm_memory {int /*<<< orphan*/ * ptrs; } ;
struct nvkm_instmem {int dummy; } ;
struct TYPE_6__ {struct nvkm_memory memory; } ;
struct nv04_instobj {int /*<<< orphan*/  node; struct nv04_instmem* imem; TYPE_3__ base; } ;
struct TYPE_4__ {int /*<<< orphan*/  mutex; } ;
struct TYPE_5__ {TYPE_1__ subdev; } ;
struct nv04_instmem {TYPE_2__ base; int /*<<< orphan*/  heap; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct nv04_instobj* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct nv04_instmem* nv04_instmem (struct nvkm_instmem*) ; 
 int /*<<< orphan*/  nv04_instobj_func ; 
 int /*<<< orphan*/  nv04_instobj_ptrs ; 
 int /*<<< orphan*/  nvkm_instobj_ctor (int /*<<< orphan*/ *,TYPE_2__*,TYPE_3__*) ; 
 int nvkm_mm_head (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
nv04_instobj_new(struct nvkm_instmem *base, u32 size, u32 align, bool zero,
		 struct nvkm_memory **pmemory)
{
	struct nv04_instmem *imem = nv04_instmem(base);
	struct nv04_instobj *iobj;
	int ret;

	if (!(iobj = kzalloc(sizeof(*iobj), GFP_KERNEL)))
		return -ENOMEM;
	*pmemory = &iobj->base.memory;

	nvkm_instobj_ctor(&nv04_instobj_func, &imem->base, &iobj->base);
	iobj->base.memory.ptrs = &nv04_instobj_ptrs;
	iobj->imem = imem;

	mutex_lock(&imem->base.subdev.mutex);
	ret = nvkm_mm_head(&imem->heap, 0, 1, size, size,
			   align ? align : 1, &iobj->node);
	mutex_unlock(&imem->base.subdev.mutex);
	return ret;
}