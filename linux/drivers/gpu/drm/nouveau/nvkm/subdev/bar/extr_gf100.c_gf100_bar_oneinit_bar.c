#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct nvkm_device {TYPE_1__* func; } ;
struct lock_class_key {int dummy; } ;
struct gf100_barN {int /*<<< orphan*/  inst; TYPE_4__* vmm; } ;
struct TYPE_8__ {int /*<<< orphan*/  debug; struct nvkm_device* device; } ;
struct TYPE_9__ {TYPE_2__ subdev; } ;
struct gf100_bar {TYPE_3__ base; scalar_t__ bar2_halve; } ;
typedef  int resource_size_t ;
struct TYPE_10__ {int /*<<< orphan*/  debug; int /*<<< orphan*/ * engref; } ;
struct TYPE_7__ {int (* resource_size ) (struct nvkm_device*,int) ;} ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  NVKM_MEM_TARGET_INST ; 
 size_t NVKM_SUBDEV_BAR ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int nvkm_memory_new (struct nvkm_device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int nvkm_vmm_boot (TYPE_4__*) ; 
 int nvkm_vmm_join (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int nvkm_vmm_new (struct nvkm_device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct lock_class_key*,char*,TYPE_4__**) ; 
 int stub1 (struct nvkm_device*,int) ; 

__attribute__((used)) static int
gf100_bar_oneinit_bar(struct gf100_bar *bar, struct gf100_barN *bar_vm,
		      struct lock_class_key *key, int bar_nr)
{
	struct nvkm_device *device = bar->base.subdev.device;
	resource_size_t bar_len;
	int ret;

	ret = nvkm_memory_new(device, NVKM_MEM_TARGET_INST, 0x1000, 0, false,
			      &bar_vm->inst);
	if (ret)
		return ret;

	bar_len = device->func->resource_size(device, bar_nr);
	if (!bar_len)
		return -ENOMEM;
	if (bar_nr == 3 && bar->bar2_halve)
		bar_len >>= 1;

	ret = nvkm_vmm_new(device, 0, bar_len, NULL, 0, key,
			   (bar_nr == 3) ? "bar2" : "bar1", &bar_vm->vmm);
	if (ret)
		return ret;

	atomic_inc(&bar_vm->vmm->engref[NVKM_SUBDEV_BAR]);
	bar_vm->vmm->debug = bar->base.subdev.debug;

	/*
	 * Bootstrap page table lookup.
	 */
	if (bar_nr == 3) {
		ret = nvkm_vmm_boot(bar_vm->vmm);
		if (ret)
			return ret;
	}

	return nvkm_vmm_join(bar_vm->vmm, bar_vm->inst);
}