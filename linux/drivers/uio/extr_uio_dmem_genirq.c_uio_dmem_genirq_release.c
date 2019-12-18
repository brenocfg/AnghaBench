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
struct uio_mem {int /*<<< orphan*/  addr; int /*<<< orphan*/  size; } ;
struct uio_info {struct uio_dmem_genirq_platdata* priv; } ;
struct uio_dmem_genirq_platdata {int dmem_region_start; int /*<<< orphan*/  alloc_lock; scalar_t__* dmem_region_vaddr; TYPE_2__* pdev; TYPE_1__* uioinfo; int /*<<< orphan*/  refcnt; } ;
struct inode {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {struct uio_mem* mem; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMEM_MAP_ERROR ; 
 size_t MAX_UIO_MAPS ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int uio_dmem_genirq_release(struct uio_info *info, struct inode *inode)
{
	struct uio_dmem_genirq_platdata *priv = info->priv;
	struct uio_mem *uiomem;
	int dmem_region = priv->dmem_region_start;

	/* Tell the Runtime PM code that the device has become idle */
	pm_runtime_put_sync(&priv->pdev->dev);

	uiomem = &priv->uioinfo->mem[priv->dmem_region_start];

	mutex_lock(&priv->alloc_lock);

	priv->refcnt--;
	while (!priv->refcnt && uiomem < &priv->uioinfo->mem[MAX_UIO_MAPS]) {
		if (!uiomem->size)
			break;
		if (priv->dmem_region_vaddr[dmem_region]) {
			dma_free_coherent(&priv->pdev->dev, uiomem->size,
					priv->dmem_region_vaddr[dmem_region],
					uiomem->addr);
		}
		uiomem->addr = DMEM_MAP_ERROR;
		++dmem_region;
		++uiomem;
	}

	mutex_unlock(&priv->alloc_lock);
	return 0;
}