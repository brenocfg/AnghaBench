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
struct g2d_data {int /*<<< orphan*/  cmdlist_dma_attrs; scalar_t__ cmdlist_pool; scalar_t__ cmdlist_pool_virt; int /*<<< orphan*/  drm_dev; int /*<<< orphan*/  cmdlist_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  G2D_CMDLIST_POOL_SIZE ; 
 int /*<<< orphan*/  dma_free_attrs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_dma_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void g2d_fini_cmdlist(struct g2d_data *g2d)
{
	kfree(g2d->cmdlist_node);

	if (g2d->cmdlist_pool_virt && g2d->cmdlist_pool) {
		dma_free_attrs(to_dma_dev(g2d->drm_dev),
				G2D_CMDLIST_POOL_SIZE,
				g2d->cmdlist_pool_virt,
				g2d->cmdlist_pool, g2d->cmdlist_dma_attrs);
	}
}