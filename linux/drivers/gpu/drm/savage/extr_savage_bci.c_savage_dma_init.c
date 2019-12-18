#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int nr_dma_pages; scalar_t__ current_dma_page; scalar_t__ first_dma_page; int /*<<< orphan*/  last_dma_age; TYPE_4__* dma_pages; TYPE_1__* cmd_dma; } ;
typedef  TYPE_2__ drm_savage_private_t ;
typedef  int /*<<< orphan*/  drm_savage_dma_page_t ;
struct TYPE_7__ {scalar_t__ flushed; scalar_t__ used; int /*<<< orphan*/  age; } ;
struct TYPE_5__ {int size; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int SAVAGE_DMA_PAGE_SIZE ; 
 int /*<<< orphan*/  SET_AGE (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__* kmalloc_array (int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int savage_dma_init(drm_savage_private_t * dev_priv)
{
	unsigned int i;

	dev_priv->nr_dma_pages = dev_priv->cmd_dma->size /
	    (SAVAGE_DMA_PAGE_SIZE * 4);
	dev_priv->dma_pages = kmalloc_array(dev_priv->nr_dma_pages,
					    sizeof(drm_savage_dma_page_t),
					    GFP_KERNEL);
	if (dev_priv->dma_pages == NULL)
		return -ENOMEM;

	for (i = 0; i < dev_priv->nr_dma_pages; ++i) {
		SET_AGE(&dev_priv->dma_pages[i].age, 0, 0);
		dev_priv->dma_pages[i].used = 0;
		dev_priv->dma_pages[i].flushed = 0;
	}
	SET_AGE(&dev_priv->last_dma_age, 0, 0);

	dev_priv->first_dma_page = 0;
	dev_priv->current_dma_page = 0;

	return 0;
}