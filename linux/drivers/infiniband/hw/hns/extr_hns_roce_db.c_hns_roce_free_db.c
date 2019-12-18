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
struct hns_roce_dev {int /*<<< orphan*/  pgdir_mutex; int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {TYPE_2__* pgdir; } ;
struct hns_roce_db {int order; int index; TYPE_1__ u; } ;
struct TYPE_4__ {int /*<<< orphan*/  list; int /*<<< orphan*/  db_dma; int /*<<< orphan*/  page; int /*<<< orphan*/  order1; int /*<<< orphan*/ * bits; int /*<<< orphan*/  order0; } ;

/* Variables and functions */
 int HNS_ROCE_DB_PER_PAGE ; 
 int HNS_ROCE_DB_TYPE_COUNT ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 scalar_t__ bitmap_full (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  clear_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (TYPE_2__*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int,int /*<<< orphan*/ ) ; 

void hns_roce_free_db(struct hns_roce_dev *hr_dev, struct hns_roce_db *db)
{
	int o;
	int i;

	mutex_lock(&hr_dev->pgdir_mutex);

	o = db->order;
	i = db->index;

	if (db->order == 0 && test_bit(i ^ 1, db->u.pgdir->order0)) {
		clear_bit(i ^ 1, db->u.pgdir->order0);
		++o;
	}

	i >>= o;
	set_bit(i, db->u.pgdir->bits[o]);

	if (bitmap_full(db->u.pgdir->order1,
			HNS_ROCE_DB_PER_PAGE / HNS_ROCE_DB_TYPE_COUNT)) {
		dma_free_coherent(hr_dev->dev, PAGE_SIZE, db->u.pgdir->page,
				  db->u.pgdir->db_dma);
		list_del(&db->u.pgdir->list);
		kfree(db->u.pgdir);
	}

	mutex_unlock(&hr_dev->pgdir_mutex);
}