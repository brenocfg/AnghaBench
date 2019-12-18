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
typedef  scalar_t__ u64 ;
struct nvkm_vmm_page {scalar_t__ shift; } ;
struct nvkm_vmm {int bootstrapped; scalar_t__ start; scalar_t__ limit; TYPE_1__* func; } ;
struct TYPE_2__ {struct nvkm_vmm_page* page; } ;

/* Variables and functions */
 int /*<<< orphan*/  nvkm_vmm_boot_ptes ; 
 int /*<<< orphan*/  nvkm_vmm_iter (struct nvkm_vmm*,struct nvkm_vmm_page const*,scalar_t__,scalar_t__ const,char*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int nvkm_vmm_ptes_get (struct nvkm_vmm*,struct nvkm_vmm_page const*,scalar_t__,scalar_t__ const) ; 

int
nvkm_vmm_boot(struct nvkm_vmm *vmm)
{
	const struct nvkm_vmm_page *page = vmm->func->page;
	const u64 limit = vmm->limit - vmm->start;
	int ret;

	while (page[1].shift)
		page++;

	ret = nvkm_vmm_ptes_get(vmm, page, vmm->start, limit);
	if (ret)
		return ret;

	nvkm_vmm_iter(vmm, page, vmm->start, limit, "bootstrap", false, false,
		      nvkm_vmm_boot_ptes, NULL, NULL, NULL);
	vmm->bootstrapped = true;
	return 0;
}