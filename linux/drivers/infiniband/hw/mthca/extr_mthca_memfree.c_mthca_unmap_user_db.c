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
struct mthca_user_db_table {int /*<<< orphan*/  mutex; TYPE_1__* page; } ;
struct mthca_uar {int dummy; } ;
struct mthca_dev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  refcount; } ;

/* Variables and functions */
 int MTHCA_DB_REC_PER_PAGE ; 
 int /*<<< orphan*/  mthca_is_memfree (struct mthca_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void mthca_unmap_user_db(struct mthca_dev *dev, struct mthca_uar *uar,
			 struct mthca_user_db_table *db_tab, int index)
{
	if (!mthca_is_memfree(dev))
		return;

	/*
	 * To make our bookkeeping simpler, we don't unmap DB
	 * pages until we clean up the whole db table.
	 */

	mutex_lock(&db_tab->mutex);

	--db_tab->page[index / MTHCA_DB_REC_PER_PAGE].refcount;

	mutex_unlock(&db_tab->mutex);
}