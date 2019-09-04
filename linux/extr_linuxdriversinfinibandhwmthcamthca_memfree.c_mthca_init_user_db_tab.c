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
struct mthca_user_db_table {TYPE_1__* page; int /*<<< orphan*/  mutex; } ;
struct TYPE_4__ {int uarc_size; } ;
struct mthca_dev {TYPE_2__ uar_table; } ;
struct TYPE_3__ {int /*<<< orphan*/  mem; scalar_t__ uvirt; scalar_t__ refcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct mthca_user_db_table* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MTHCA_ICM_PAGE_SIZE ; 
 struct mthca_user_db_table* kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mthca_is_memfree (struct mthca_dev*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  page ; 
 int /*<<< orphan*/  sg_init_table (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  struct_size (struct mthca_user_db_table*,int /*<<< orphan*/ ,int) ; 

struct mthca_user_db_table *mthca_init_user_db_tab(struct mthca_dev *dev)
{
	struct mthca_user_db_table *db_tab;
	int npages;
	int i;

	if (!mthca_is_memfree(dev))
		return NULL;

	npages = dev->uar_table.uarc_size / MTHCA_ICM_PAGE_SIZE;
	db_tab = kmalloc(struct_size(db_tab, page, npages), GFP_KERNEL);
	if (!db_tab)
		return ERR_PTR(-ENOMEM);

	mutex_init(&db_tab->mutex);
	for (i = 0; i < npages; ++i) {
		db_tab->page[i].refcount = 0;
		db_tab->page[i].uvirt    = 0;
		sg_init_table(&db_tab->page[i].mem, 1);
	}

	return db_tab;
}