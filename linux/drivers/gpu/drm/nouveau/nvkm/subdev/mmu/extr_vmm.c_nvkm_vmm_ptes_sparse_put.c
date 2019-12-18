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
typedef  int /*<<< orphan*/  u64 ;
struct nvkm_vmm_page {TYPE_2__* desc; } ;
struct nvkm_vmm {int dummy; } ;
struct TYPE_4__ {TYPE_1__* func; } ;
struct TYPE_3__ {scalar_t__ unmap; scalar_t__ invalid; } ;

/* Variables and functions */
 int /*<<< orphan*/  nvkm_vmm_iter (struct nvkm_vmm*,struct nvkm_vmm_page const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  nvkm_vmm_sparse_unref_ptes ; 

__attribute__((used)) static void
nvkm_vmm_ptes_sparse_put(struct nvkm_vmm *vmm, const struct nvkm_vmm_page *page,
			 u64 addr, u64 size)
{
	nvkm_vmm_iter(vmm, page, addr, size, "sparse unref", false, false,
		      nvkm_vmm_sparse_unref_ptes, NULL, NULL,
		      page->desc->func->invalid ?
		      page->desc->func->invalid : page->desc->func->unmap);
}