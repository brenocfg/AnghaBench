#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ oclass; } ;
struct nvkm_oclass {int /*<<< orphan*/  ctor; TYPE_3__ base; TYPE_1__* client; } ;
struct nvkm_object {int dummy; } ;
struct nvkm_mmu {TYPE_5__* func; } ;
struct TYPE_12__ {struct nvkm_mmu* mmu; } ;
struct TYPE_10__ {TYPE_3__ user; } ;
struct TYPE_8__ {TYPE_3__ user; } ;
struct TYPE_11__ {TYPE_4__ vmm; TYPE_2__ mem; } ;
struct TYPE_7__ {scalar_t__ super; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  nvkm_umem_new ; 
 TYPE_6__* nvkm_ummu (struct nvkm_object*) ; 
 int /*<<< orphan*/  nvkm_uvmm_new ; 

__attribute__((used)) static int
nvkm_ummu_sclass(struct nvkm_object *object, int index,
		 struct nvkm_oclass *oclass)
{
	struct nvkm_mmu *mmu = nvkm_ummu(object)->mmu;

	if (mmu->func->mem.user.oclass && oclass->client->super) {
		if (index-- == 0) {
			oclass->base = mmu->func->mem.user;
			oclass->ctor = nvkm_umem_new;
			return 0;
		}
	}

	if (mmu->func->vmm.user.oclass) {
		if (index-- == 0) {
			oclass->base = mmu->func->vmm.user;
			oclass->ctor = nvkm_uvmm_new;
			return 0;
		}
	}

	return -EINVAL;
}