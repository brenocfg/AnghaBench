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
struct mthca_user_db_table {TYPE_2__* page; } ;
struct mthca_uar {int dummy; } ;
struct TYPE_3__ {int uarc_size; } ;
struct mthca_dev {int /*<<< orphan*/  pdev; TYPE_1__ uar_table; } ;
struct TYPE_4__ {int /*<<< orphan*/  mem; scalar_t__ uvirt; } ;

/* Variables and functions */
 int MTHCA_ICM_PAGE_SIZE ; 
 int /*<<< orphan*/  PCI_DMA_TODEVICE ; 
 int /*<<< orphan*/  kfree (struct mthca_user_db_table*) ; 
 int /*<<< orphan*/  mthca_UNMAP_ICM (struct mthca_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mthca_is_memfree (struct mthca_dev*) ; 
 int /*<<< orphan*/  mthca_uarc_virt (struct mthca_dev*,struct mthca_uar*,int) ; 
 int /*<<< orphan*/  pci_unmap_sg (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_user_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_page (int /*<<< orphan*/ *) ; 

void mthca_cleanup_user_db_tab(struct mthca_dev *dev, struct mthca_uar *uar,
			       struct mthca_user_db_table *db_tab)
{
	int i;

	if (!mthca_is_memfree(dev))
		return;

	for (i = 0; i < dev->uar_table.uarc_size / MTHCA_ICM_PAGE_SIZE; ++i) {
		if (db_tab->page[i].uvirt) {
			mthca_UNMAP_ICM(dev, mthca_uarc_virt(dev, uar, i), 1);
			pci_unmap_sg(dev->pdev, &db_tab->page[i].mem, 1, PCI_DMA_TODEVICE);
			put_user_page(sg_page(&db_tab->page[i].mem));
		}
	}

	kfree(db_tab);
}