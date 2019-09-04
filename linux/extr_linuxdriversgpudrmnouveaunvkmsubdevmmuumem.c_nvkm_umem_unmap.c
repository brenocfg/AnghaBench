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
struct nvkm_umem {int /*<<< orphan*/ * map; int /*<<< orphan*/ * bar; TYPE_2__* mmu; scalar_t__ io; } ;
struct nvkm_object {int dummy; } ;
struct nvkm_device {int dummy; } ;
struct TYPE_3__ {struct nvkm_device* device; } ;
struct TYPE_4__ {TYPE_1__ subdev; } ;

/* Variables and functions */
 int EEXIST ; 
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvkm_bar_bar1_vmm (struct nvkm_device*) ; 
 struct nvkm_umem* nvkm_umem (struct nvkm_object*) ; 
 int /*<<< orphan*/  nvkm_vmm_put (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  vunmap (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
nvkm_umem_unmap(struct nvkm_object *object)
{
	struct nvkm_umem *umem = nvkm_umem(object);

	if (!umem->map)
		return -EEXIST;

	if (umem->io) {
		if (!IS_ERR(umem->bar)) {
			struct nvkm_device *device = umem->mmu->subdev.device;
			nvkm_vmm_put(nvkm_bar_bar1_vmm(device), &umem->bar);
		} else {
			umem->bar = NULL;
		}
	} else {
		vunmap(umem->map);
		umem->map = NULL;
	}

	return 0;
}