#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct tegra_vde_cache_entry {int /*<<< orphan*/  list; TYPE_2__* a; int /*<<< orphan*/  dma_dir; int /*<<< orphan*/  sgt; int /*<<< orphan*/  iova; TYPE_1__* vde; int /*<<< orphan*/  refcnt; } ;
struct dma_buf {int dummy; } ;
struct TYPE_5__ {struct dma_buf* dmabuf; } ;
struct TYPE_4__ {scalar_t__ domain; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_buf_detach (struct dma_buf*,TYPE_2__*) ; 
 int /*<<< orphan*/  dma_buf_put (struct dma_buf*) ; 
 int /*<<< orphan*/  dma_buf_unmap_attachment (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct tegra_vde_cache_entry*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tegra_vde_iommu_unmap (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tegra_vde_release_entry(struct tegra_vde_cache_entry *entry)
{
	struct dma_buf *dmabuf = entry->a->dmabuf;

	WARN_ON_ONCE(entry->refcnt);

	if (entry->vde->domain)
		tegra_vde_iommu_unmap(entry->vde, entry->iova);

	dma_buf_unmap_attachment(entry->a, entry->sgt, entry->dma_dir);
	dma_buf_detach(dmabuf, entry->a);
	dma_buf_put(dmabuf);

	list_del(&entry->list);
	kfree(entry);
}