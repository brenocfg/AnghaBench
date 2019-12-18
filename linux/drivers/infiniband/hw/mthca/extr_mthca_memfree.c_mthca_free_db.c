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
struct mthca_dev {TYPE_2__* db_tab; TYPE_1__* pdev; int /*<<< orphan*/  driver_uar; } ;
struct mthca_db_page {scalar_t__* db_rec; int /*<<< orphan*/  mapping; int /*<<< orphan*/  used; } ;
struct TYPE_4__ {int min_group2; int max_group1; int /*<<< orphan*/  mutex; struct mthca_db_page* page; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int MTHCA_DB_REC_PER_PAGE ; 
 int /*<<< orphan*/  MTHCA_ICM_PAGE_SIZE ; 
 scalar_t__ bitmap_empty (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  clear_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mthca_UNMAP_ICM (struct mthca_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mthca_uarc_virt (struct mthca_dev*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void mthca_free_db(struct mthca_dev *dev, int type, int db_index)
{
	int i, j;
	struct mthca_db_page *page;

	i = db_index / MTHCA_DB_REC_PER_PAGE;
	j = db_index % MTHCA_DB_REC_PER_PAGE;

	page = dev->db_tab->page + i;

	mutex_lock(&dev->db_tab->mutex);

	page->db_rec[j] = 0;
	if (i >= dev->db_tab->min_group2)
		j = MTHCA_DB_REC_PER_PAGE - 1 - j;
	clear_bit(j, page->used);

	if (bitmap_empty(page->used, MTHCA_DB_REC_PER_PAGE) &&
	    i >= dev->db_tab->max_group1 - 1) {
		mthca_UNMAP_ICM(dev, mthca_uarc_virt(dev, &dev->driver_uar, i), 1);

		dma_free_coherent(&dev->pdev->dev, MTHCA_ICM_PAGE_SIZE,
				  page->db_rec, page->mapping);
		page->db_rec = NULL;

		if (i == dev->db_tab->max_group1) {
			--dev->db_tab->max_group1;
			/* XXX may be able to unmap more pages now */
		}
		if (i == dev->db_tab->min_group2)
			++dev->db_tab->min_group2;
	}

	mutex_unlock(&dev->db_tab->mutex);
}