#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  unsigned long long u64 ;
struct nvkm_vmm_page {int dummy; } ;
struct nvkm_vmm_map {int dummy; } ;
struct nvkm_vmm {int dummy; } ;
typedef  int /*<<< orphan*/  nvkm_vmm_pte_func ;

/* Variables and functions */
 int ENOMEM ; 
 unsigned long long nvkm_vmm_iter (struct nvkm_vmm*,struct nvkm_vmm_page const*,unsigned long long,unsigned long long,char*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nvkm_vmm_map*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvkm_vmm_ptes_unmap_put (struct nvkm_vmm*,struct nvkm_vmm_page const*,unsigned long long,unsigned long long,int,int) ; 
 int /*<<< orphan*/  nvkm_vmm_ref_ptes ; 

__attribute__((used)) static int
nvkm_vmm_ptes_get_map(struct nvkm_vmm *vmm, const struct nvkm_vmm_page *page,
		      u64 addr, u64 size, struct nvkm_vmm_map *map,
		      nvkm_vmm_pte_func func)
{
	u64 fail = nvkm_vmm_iter(vmm, page, addr, size, "ref + map", true,
				 false, nvkm_vmm_ref_ptes, func, map, NULL);
	if (fail != ~0ULL) {
		if ((size = fail - addr))
			nvkm_vmm_ptes_unmap_put(vmm, page, addr, size, false, false);
		return -ENOMEM;
	}
	return 0;
}