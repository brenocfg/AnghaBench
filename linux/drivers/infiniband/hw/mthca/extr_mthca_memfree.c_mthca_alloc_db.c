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
typedef  int u32 ;
struct mthca_dev {TYPE_2__* db_tab; TYPE_1__* pdev; int /*<<< orphan*/  driver_uar; } ;
struct mthca_db_page {int /*<<< orphan*/ * db_rec; int /*<<< orphan*/  used; int /*<<< orphan*/  mapping; } ;
typedef  enum mthca_db_type { ____Placeholder_mthca_db_type } mthca_db_type ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_4__ {int max_group1; int min_group2; int /*<<< orphan*/  mutex; struct mthca_db_page* page; int /*<<< orphan*/  npages; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MTHCA_DB_REC_PER_PAGE ; 
#define  MTHCA_DB_TYPE_CQ_ARM 132 
#define  MTHCA_DB_TYPE_CQ_SET_CI 131 
#define  MTHCA_DB_TYPE_RQ 130 
#define  MTHCA_DB_TYPE_SQ 129 
#define  MTHCA_DB_TYPE_SRQ 128 
 int /*<<< orphan*/  MTHCA_ICM_PAGE_SIZE ; 
 int /*<<< orphan*/  bitmap_full (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bitmap_zero (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cpu_to_be64 (int) ; 
 int /*<<< orphan*/ * dma_alloc_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int find_first_zero_bit (int /*<<< orphan*/ ,int) ; 
 int mthca_MAP_ICM_page (struct mthca_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mthca_uarc_virt (struct mthca_dev*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int,int /*<<< orphan*/ ) ; 

int mthca_alloc_db(struct mthca_dev *dev, enum mthca_db_type type,
		   u32 qn, __be32 **db)
{
	int group;
	int start, end, dir;
	int i, j;
	struct mthca_db_page *page;
	int ret = 0;

	mutex_lock(&dev->db_tab->mutex);

	switch (type) {
	case MTHCA_DB_TYPE_CQ_ARM:
	case MTHCA_DB_TYPE_SQ:
		group = 0;
		start = 0;
		end   = dev->db_tab->max_group1;
		dir   = 1;
		break;

	case MTHCA_DB_TYPE_CQ_SET_CI:
	case MTHCA_DB_TYPE_RQ:
	case MTHCA_DB_TYPE_SRQ:
		group = 1;
		start = dev->db_tab->npages - 1;
		end   = dev->db_tab->min_group2;
		dir   = -1;
		break;

	default:
		ret = -EINVAL;
		goto out;
	}

	for (i = start; i != end; i += dir)
		if (dev->db_tab->page[i].db_rec &&
		    !bitmap_full(dev->db_tab->page[i].used,
				 MTHCA_DB_REC_PER_PAGE)) {
			page = dev->db_tab->page + i;
			goto found;
		}

	for (i = start; i != end; i += dir)
		if (!dev->db_tab->page[i].db_rec) {
			page = dev->db_tab->page + i;
			goto alloc;
		}

	if (dev->db_tab->max_group1 >= dev->db_tab->min_group2 - 1) {
		ret = -ENOMEM;
		goto out;
	}

	if (group == 0)
		++dev->db_tab->max_group1;
	else
		--dev->db_tab->min_group2;

	page = dev->db_tab->page + end;

alloc:
	page->db_rec = dma_alloc_coherent(&dev->pdev->dev,
					  MTHCA_ICM_PAGE_SIZE, &page->mapping,
					  GFP_KERNEL);
	if (!page->db_rec) {
		ret = -ENOMEM;
		goto out;
	}

	ret = mthca_MAP_ICM_page(dev, page->mapping,
				 mthca_uarc_virt(dev, &dev->driver_uar, i));
	if (ret) {
		dma_free_coherent(&dev->pdev->dev, MTHCA_ICM_PAGE_SIZE,
				  page->db_rec, page->mapping);
		goto out;
	}

	bitmap_zero(page->used, MTHCA_DB_REC_PER_PAGE);

found:
	j = find_first_zero_bit(page->used, MTHCA_DB_REC_PER_PAGE);
	set_bit(j, page->used);

	if (group == 1)
		j = MTHCA_DB_REC_PER_PAGE - 1 - j;

	ret = i * MTHCA_DB_REC_PER_PAGE + j;

	page->db_rec[j] = cpu_to_be64((qn << 8) | (type << 5));

	*db = (__be32 *) &page->db_rec[j];

out:
	mutex_unlock(&dev->db_tab->mutex);

	return ret;
}