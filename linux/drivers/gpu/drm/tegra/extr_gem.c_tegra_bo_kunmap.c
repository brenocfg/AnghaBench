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
struct tegra_bo {TYPE_2__ gem; scalar_t__ vaddr; } ;
struct host1x_bo {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  dmabuf; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_buf_kunmap (int /*<<< orphan*/ ,unsigned int,void*) ; 
 struct tegra_bo* host1x_to_tegra_bo (struct host1x_bo*) ; 
 int /*<<< orphan*/  vunmap (void*) ; 

__attribute__((used)) static void tegra_bo_kunmap(struct host1x_bo *bo, unsigned int page,
			    void *addr)
{
	struct tegra_bo *obj = host1x_to_tegra_bo(bo);

	if (obj->vaddr)
		return;
	else if (obj->gem.import_attach)
		dma_buf_kunmap(obj->gem.import_attach->dmabuf, page, addr);
	else
		vunmap(addr);
}