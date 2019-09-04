#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_8__ {TYPE_4__* pgdir; } ;
struct mlx5_db {TYPE_2__ u; int /*<<< orphan*/  index; } ;
struct TYPE_9__ {int /*<<< orphan*/  pgdir_mutex; } ;
struct mlx5_core_dev {TYPE_3__ priv; TYPE_1__* pdev; } ;
struct TYPE_10__ {struct TYPE_10__* bitmap; int /*<<< orphan*/  list; int /*<<< orphan*/  db_dma; int /*<<< orphan*/  db_page; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int PAGE_SIZE ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,TYPE_4__*) ; 
 scalar_t__ bitmap_full (TYPE_4__*,int) ; 
 int cache_line_size () ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (TYPE_4__*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void mlx5_db_free(struct mlx5_core_dev *dev, struct mlx5_db *db)
{
	u32 db_per_page = PAGE_SIZE / cache_line_size();

	mutex_lock(&dev->priv.pgdir_mutex);

	__set_bit(db->index, db->u.pgdir->bitmap);

	if (bitmap_full(db->u.pgdir->bitmap, db_per_page)) {
		dma_free_coherent(&(dev->pdev->dev), PAGE_SIZE,
				  db->u.pgdir->db_page, db->u.pgdir->db_dma);
		list_del(&db->u.pgdir->list);
		kfree(db->u.pgdir->bitmap);
		kfree(db->u.pgdir);
	}

	mutex_unlock(&dev->priv.pgdir_mutex);
}