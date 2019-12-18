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
typedef  size_t u64 ;
struct pvrdma_page_dir {size_t npages; scalar_t__* pages; } ;
struct pvrdma_dev {TYPE_1__* pdev; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (scalar_t__*) ; 
 int /*<<< orphan*/  pvrdma_page_dir_get_dma (struct pvrdma_page_dir*,size_t) ; 

__attribute__((used)) static void pvrdma_page_dir_cleanup_pages(struct pvrdma_dev *dev,
					  struct pvrdma_page_dir *pdir)
{
	if (pdir->pages) {
		u64 i;

		for (i = 0; i < pdir->npages && pdir->pages[i]; i++) {
			dma_addr_t page_dma = pvrdma_page_dir_get_dma(pdir, i);

			dma_free_coherent(&dev->pdev->dev, PAGE_SIZE,
					  pdir->pages[i], page_dma);
		}

		kfree(pdir->pages);
	}
}