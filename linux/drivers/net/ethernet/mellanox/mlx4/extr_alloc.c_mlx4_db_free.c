#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct mlx4_priv {int /*<<< orphan*/  pgdir_mutex; } ;
struct mlx4_dev {TYPE_2__* persist; } ;
struct TYPE_7__ {TYPE_4__* pgdir; } ;
struct mlx4_db {int order; int index; TYPE_3__ u; } ;
struct TYPE_8__ {int /*<<< orphan*/  list; int /*<<< orphan*/  db_dma; int /*<<< orphan*/  db_page; int /*<<< orphan*/  order1; int /*<<< orphan*/ * bits; int /*<<< orphan*/  order0; } ;
struct TYPE_6__ {TYPE_1__* pdev; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int MLX4_DB_PER_PAGE ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 scalar_t__ bitmap_full (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  clear_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (TYPE_4__*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 struct mlx4_priv* mlx4_priv (struct mlx4_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int,int /*<<< orphan*/ ) ; 

void mlx4_db_free(struct mlx4_dev *dev, struct mlx4_db *db)
{
	struct mlx4_priv *priv = mlx4_priv(dev);
	int o;
	int i;

	mutex_lock(&priv->pgdir_mutex);

	o = db->order;
	i = db->index;

	if (db->order == 0 && test_bit(i ^ 1, db->u.pgdir->order0)) {
		clear_bit(i ^ 1, db->u.pgdir->order0);
		++o;
	}
	i >>= o;
	set_bit(i, db->u.pgdir->bits[o]);

	if (bitmap_full(db->u.pgdir->order1, MLX4_DB_PER_PAGE / 2)) {
		dma_free_coherent(&dev->persist->pdev->dev, PAGE_SIZE,
				  db->u.pgdir->db_page, db->u.pgdir->db_dma);
		list_del(&db->u.pgdir->list);
		kfree(db->u.pgdir);
	}

	mutex_unlock(&priv->pgdir_mutex);
}