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
struct TYPE_4__ {int /*<<< orphan*/  memory; int /*<<< orphan*/ * vaddr; struct gk20a_instmem* imem; } ;
struct gk20a_instobj_iommu {TYPE_2__ base; int /*<<< orphan*/  vaddr_node; int /*<<< orphan*/  use_cpt; } ;
struct TYPE_3__ {int /*<<< orphan*/  subdev; } ;
struct gk20a_instmem {int /*<<< orphan*/  vaddr_max; int /*<<< orphan*/  vaddr_use; TYPE_1__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvkm_debug (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nvkm_memory_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vunmap (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
gk20a_instobj_iommu_recycle_vaddr(struct gk20a_instobj_iommu *obj)
{
	struct gk20a_instmem *imem = obj->base.imem;
	/* there should not be any user left... */
	WARN_ON(obj->use_cpt);
	list_del(&obj->vaddr_node);
	vunmap(obj->base.vaddr);
	obj->base.vaddr = NULL;
	imem->vaddr_use -= nvkm_memory_size(&obj->base.memory);
	nvkm_debug(&imem->base.subdev, "vaddr used: %x/%x\n", imem->vaddr_use,
		   imem->vaddr_max);
}