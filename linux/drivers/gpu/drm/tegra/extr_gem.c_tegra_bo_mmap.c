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
struct tegra_bo {void* vaddr; int /*<<< orphan*/  num_pages; int /*<<< orphan*/  pages; TYPE_2__ gem; } ;
struct host1x_bo {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  dmabuf; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_KERNEL ; 
 int /*<<< orphan*/  VM_MAP ; 
 void* dma_buf_vmap (int /*<<< orphan*/ ) ; 
 struct tegra_bo* host1x_to_tegra_bo (struct host1x_bo*) ; 
 int /*<<< orphan*/  pgprot_writecombine (int /*<<< orphan*/ ) ; 
 void* vmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *tegra_bo_mmap(struct host1x_bo *bo)
{
	struct tegra_bo *obj = host1x_to_tegra_bo(bo);

	if (obj->vaddr)
		return obj->vaddr;
	else if (obj->gem.import_attach)
		return dma_buf_vmap(obj->gem.import_attach->dmabuf);
	else
		return vmap(obj->pages, obj->num_pages, VM_MAP,
			    pgprot_writecombine(PAGE_KERNEL));
}