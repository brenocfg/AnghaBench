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
typedef  int u64 ;
struct nvkm_vmm_page {unsigned long long shift; } ;
struct nvkm_vmm {TYPE_1__* func; } ;
struct TYPE_2__ {struct nvkm_vmm_page* page; } ;

/* Variables and functions */
 int ALIGN (int,int) ; 
 int /*<<< orphan*/  IS_ALIGNED (int,unsigned long long) ; 
 int nvkm_vmm_ptes_sparse_get (struct nvkm_vmm*,struct nvkm_vmm_page const*,int,int) ; 
 int /*<<< orphan*/  nvkm_vmm_ptes_sparse_put (struct nvkm_vmm*,struct nvkm_vmm_page const*,int,int) ; 

__attribute__((used)) static int
nvkm_vmm_ptes_sparse(struct nvkm_vmm *vmm, u64 addr, u64 size, bool ref)
{
	const struct nvkm_vmm_page *page = vmm->func->page;
	int m = 0, i;
	u64 start = addr;
	u64 block;

	while (size) {
		/* Limit maximum page size based on remaining size. */
		while (size < (1ULL << page[m].shift))
			m++;
		i = m;

		/* Find largest page size suitable for alignment. */
		while (!IS_ALIGNED(addr, 1ULL << page[i].shift))
			i++;

		/* Determine number of PTEs at this page size. */
		if (i != m) {
			/* Limited to alignment boundary of next page size. */
			u64 next = 1ULL << page[i - 1].shift;
			u64 part = ALIGN(addr, next) - addr;
			if (size - part >= next)
				block = (part >> page[i].shift) << page[i].shift;
			else
				block = (size >> page[i].shift) << page[i].shift;
		} else {
			block = (size >> page[i].shift) << page[i].shift;
		}

		/* Perform operation. */
		if (ref) {
			int ret = nvkm_vmm_ptes_sparse_get(vmm, &page[i], addr, block);
			if (ret) {
				if ((size = addr - start))
					nvkm_vmm_ptes_sparse(vmm, start, size, false);
				return ret;
			}
		} else {
			nvkm_vmm_ptes_sparse_put(vmm, &page[i], addr, block);
		}

		size -= block;
		addr += block;
	}

	return 0;
}