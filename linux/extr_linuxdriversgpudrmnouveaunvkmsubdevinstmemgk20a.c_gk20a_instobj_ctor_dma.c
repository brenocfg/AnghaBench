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
typedef  int u32 ;
struct nvkm_subdev {TYPE_2__* device; } ;
struct TYPE_7__ {int type; int offset; int length; } ;
struct TYPE_8__ {int /*<<< orphan*/ * ptrs; } ;
struct gk20a_instobj {TYPE_3__* mn; int /*<<< orphan*/  vaddr; TYPE_4__ memory; } ;
struct gk20a_instobj_dma {int handle; TYPE_3__ r; struct gk20a_instobj base; } ;
struct TYPE_5__ {struct nvkm_subdev subdev; } ;
struct gk20a_instmem {int /*<<< orphan*/  attrs; TYPE_1__ base; } ;
struct device {int dummy; } ;
struct TYPE_6__ {struct device* dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  dma_alloc_attrs (struct device*,int,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gk20a_instobj_func_dma ; 
 int /*<<< orphan*/  gk20a_instobj_ptrs ; 
 struct gk20a_instobj_dma* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvkm_error (struct nvkm_subdev*,char*) ; 
 int /*<<< orphan*/  nvkm_memory_ctor (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  nvkm_warn (struct nvkm_subdev*,char*,int*,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int
gk20a_instobj_ctor_dma(struct gk20a_instmem *imem, u32 npages, u32 align,
		       struct gk20a_instobj **_node)
{
	struct gk20a_instobj_dma *node;
	struct nvkm_subdev *subdev = &imem->base.subdev;
	struct device *dev = subdev->device->dev;

	if (!(node = kzalloc(sizeof(*node), GFP_KERNEL)))
		return -ENOMEM;
	*_node = &node->base;

	nvkm_memory_ctor(&gk20a_instobj_func_dma, &node->base.memory);
	node->base.memory.ptrs = &gk20a_instobj_ptrs;

	node->base.vaddr = dma_alloc_attrs(dev, npages << PAGE_SHIFT,
					   &node->handle, GFP_KERNEL,
					   imem->attrs);
	if (!node->base.vaddr) {
		nvkm_error(subdev, "cannot allocate DMA memory\n");
		return -ENOMEM;
	}

	/* alignment check */
	if (unlikely(node->handle & (align - 1)))
		nvkm_warn(subdev,
			  "memory not aligned as requested: %pad (0x%x)\n",
			  &node->handle, align);

	/* present memory for being mapped using small pages */
	node->r.type = 12;
	node->r.offset = node->handle >> 12;
	node->r.length = (npages << PAGE_SHIFT) >> 12;

	node->base.mn = &node->r;
	return 0;
}