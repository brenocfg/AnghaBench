#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  wq; int /*<<< orphan*/  rules; int /*<<< orphan*/  arfs_lock; } ;
struct TYPE_6__ {TYPE_2__ arfs; } ;
struct mlx5e_priv {TYPE_3__ fs; TYPE_1__* netdev; } ;
struct TYPE_4__ {int hw_features; } ;

/* Variables and functions */
 int ARFS_NUM_TYPES ; 
 int ENOMEM ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int NETIF_F_NTUPLE ; 
 int arfs_create_table (struct mlx5e_priv*,int) ; 
 int /*<<< orphan*/  create_singlethread_workqueue (char*) ; 
 int /*<<< orphan*/  mlx5e_arfs_destroy_tables (struct mlx5e_priv*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int mlx5e_arfs_create_tables(struct mlx5e_priv *priv)
{
	int err = 0;
	int i;

	if (!(priv->netdev->hw_features & NETIF_F_NTUPLE))
		return 0;

	spin_lock_init(&priv->fs.arfs.arfs_lock);
	INIT_LIST_HEAD(&priv->fs.arfs.rules);
	priv->fs.arfs.wq = create_singlethread_workqueue("mlx5e_arfs");
	if (!priv->fs.arfs.wq)
		return -ENOMEM;

	for (i = 0; i < ARFS_NUM_TYPES; i++) {
		err = arfs_create_table(priv, i);
		if (err)
			goto err;
	}
	return 0;
err:
	mlx5e_arfs_destroy_tables(priv);
	return err;
}