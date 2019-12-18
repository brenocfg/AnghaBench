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
typedef  unsigned long long u64 ;
struct nvkm_vmm_page {int type; TYPE_2__* desc; } ;
struct nvkm_vmm {int dummy; } ;
struct TYPE_4__ {TYPE_1__* func; } ;
struct TYPE_3__ {int /*<<< orphan*/  sparse; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int NVKM_VMM_PAGE_SPARSE ; 
 unsigned long long nvkm_vmm_iter (struct nvkm_vmm*,struct nvkm_vmm_page const*,unsigned long long,unsigned long long,char*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvkm_vmm_ptes_sparse_put (struct nvkm_vmm*,struct nvkm_vmm_page const*,unsigned long long,unsigned long long) ; 
 int /*<<< orphan*/  nvkm_vmm_sparse_ref_ptes ; 

__attribute__((used)) static int
nvkm_vmm_ptes_sparse_get(struct nvkm_vmm *vmm, const struct nvkm_vmm_page *page,
			 u64 addr, u64 size)
{
	if ((page->type & NVKM_VMM_PAGE_SPARSE)) {
		u64 fail = nvkm_vmm_iter(vmm, page, addr, size, "sparse ref",
					 true, false, nvkm_vmm_sparse_ref_ptes,
					 NULL, NULL, page->desc->func->sparse);
		if (fail != ~0ULL) {
			if ((size = fail - addr))
				nvkm_vmm_ptes_sparse_put(vmm, page, addr, size);
			return -ENOMEM;
		}
		return 0;
	}
	return -EINVAL;
}