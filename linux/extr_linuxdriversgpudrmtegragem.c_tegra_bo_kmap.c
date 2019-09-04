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
struct TYPE_4__ {TYPE_1__* import_attach; } ;
struct tegra_bo {void* vaddr; scalar_t__ pages; TYPE_2__ gem; } ;
struct host1x_bo {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  dmabuf; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_KERNEL ; 
 unsigned int PAGE_SIZE ; 
 int /*<<< orphan*/  VM_MAP ; 
 void* dma_buf_kmap (int /*<<< orphan*/ ,unsigned int) ; 
 struct tegra_bo* host1x_to_tegra_bo (struct host1x_bo*) ; 
 int /*<<< orphan*/  pgprot_writecombine (int /*<<< orphan*/ ) ; 
 void* vmap (scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *tegra_bo_kmap(struct host1x_bo *bo, unsigned int page)
{
	struct tegra_bo *obj = host1x_to_tegra_bo(bo);

	if (obj->vaddr)
		return obj->vaddr + page * PAGE_SIZE;
	else if (obj->gem.import_attach)
		return dma_buf_kmap(obj->gem.import_attach->dmabuf, page);
	else
		return vmap(obj->pages + page, 1, VM_MAP,
			    pgprot_writecombine(PAGE_KERNEL));
}