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
typedef  int u32 ;
struct nvkm_vma {int /*<<< orphan*/  addr; } ;
struct nvkm_subdev {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  device; } ;
struct nvkm_secboot {TYPE_3__ subdev; TYPE_5__* acr; } ;
struct nvkm_gpuobj {int /*<<< orphan*/  size; } ;
struct nvkm_falcon {TYPE_4__* owner; } ;
struct TYPE_6__ {struct nvkm_subdev subdev; } ;
struct gm200_secboot {int /*<<< orphan*/  vmm; int /*<<< orphan*/  inst; TYPE_1__ base; } ;
struct TYPE_10__ {TYPE_2__* func; } ;
struct TYPE_9__ {int /*<<< orphan*/  index; } ;
struct TYPE_7__ {int (* load ) (TYPE_5__*,struct nvkm_falcon*,struct nvkm_gpuobj*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 struct gm200_secboot* gm200_secboot (struct nvkm_secboot*) ; 
 int /*<<< orphan*/  nvkm_falcon_bind_context (struct nvkm_falcon*,int /*<<< orphan*/ ) ; 
 int nvkm_falcon_get (struct nvkm_falcon*,struct nvkm_subdev*) ; 
 int /*<<< orphan*/  nvkm_falcon_put (struct nvkm_falcon*,struct nvkm_subdev*) ; 
 int nvkm_falcon_rd32 (struct nvkm_falcon*,int) ; 
 int nvkm_falcon_reset (struct nvkm_falcon*) ; 
 int /*<<< orphan*/  nvkm_falcon_set_start_addr (struct nvkm_falcon*,int) ; 
 int /*<<< orphan*/  nvkm_falcon_start (struct nvkm_falcon*) ; 
 int nvkm_falcon_wait_for_halt (struct nvkm_falcon*,int) ; 
 int /*<<< orphan*/  nvkm_falcon_wr32 (struct nvkm_falcon*,int,int) ; 
 int /*<<< orphan*/  nvkm_mc_intr_mask (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int nvkm_memory_map (struct nvkm_gpuobj*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nvkm_vma*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int nvkm_vmm_get (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct nvkm_vma**) ; 
 int /*<<< orphan*/  nvkm_vmm_put (int /*<<< orphan*/ ,struct nvkm_vma**) ; 
 int stub1 (TYPE_5__*,struct nvkm_falcon*,struct nvkm_gpuobj*,int /*<<< orphan*/ ) ; 

int
gm200_secboot_run_blob(struct nvkm_secboot *sb, struct nvkm_gpuobj *blob,
		       struct nvkm_falcon *falcon)
{
	struct gm200_secboot *gsb = gm200_secboot(sb);
	struct nvkm_subdev *subdev = &gsb->base.subdev;
	struct nvkm_vma *vma = NULL;
	u32 start_address;
	int ret;

	ret = nvkm_falcon_get(falcon, subdev);
	if (ret)
		return ret;

	/* Map the HS firmware so the HS bootloader can see it */
	ret = nvkm_vmm_get(gsb->vmm, 12, blob->size, &vma);
	if (ret) {
		nvkm_falcon_put(falcon, subdev);
		return ret;
	}

	ret = nvkm_memory_map(blob, 0, gsb->vmm, vma, NULL, 0);
	if (ret)
		goto end;

	/* Reset and set the falcon up */
	ret = nvkm_falcon_reset(falcon);
	if (ret)
		goto end;
	nvkm_falcon_bind_context(falcon, gsb->inst);

	/* Load the HS bootloader into the falcon's IMEM/DMEM */
	ret = sb->acr->func->load(sb->acr, falcon, blob, vma->addr);
	if (ret < 0)
		goto end;

	start_address = ret;

	/* Disable interrupts as we will poll for the HALT bit */
	nvkm_mc_intr_mask(sb->subdev.device, falcon->owner->index, false);

	/* Set default error value in mailbox register */
	nvkm_falcon_wr32(falcon, 0x040, 0xdeada5a5);

	/* Start the HS bootloader */
	nvkm_falcon_set_start_addr(falcon, start_address);
	nvkm_falcon_start(falcon);
	ret = nvkm_falcon_wait_for_halt(falcon, 100);
	if (ret)
		goto end;

	/*
	 * The mailbox register contains the (positive) error code - return this
	 * to the caller
	 */
	ret = nvkm_falcon_rd32(falcon, 0x040);

end:
	/* Reenable interrupts */
	nvkm_mc_intr_mask(sb->subdev.device, falcon->owner->index, true);

	/* We don't need the ACR firmware anymore */
	nvkm_vmm_put(gsb->vmm, &vma);
	nvkm_falcon_put(falcon, subdev);

	return ret;
}