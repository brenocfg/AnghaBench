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
struct pvrdma_page_dir {int /*<<< orphan*/  dir_dma; scalar_t__ dir; } ;
struct pvrdma_dev {TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pvrdma_page_dir_cleanup_tables (struct pvrdma_dev*,struct pvrdma_page_dir*) ; 

void pvrdma_page_dir_cleanup(struct pvrdma_dev *dev,
			     struct pvrdma_page_dir *pdir)
{
	if (pdir->dir) {
		pvrdma_page_dir_cleanup_tables(dev, pdir);
		dma_free_coherent(&dev->pdev->dev, PAGE_SIZE,
				  pdir->dir, pdir->dir_dma);
	}
}