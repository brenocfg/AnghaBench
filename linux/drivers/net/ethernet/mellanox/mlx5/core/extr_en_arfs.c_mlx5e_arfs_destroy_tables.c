#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_5__* arfs_tables; int /*<<< orphan*/  wq; } ;
struct TYPE_8__ {TYPE_2__ arfs; } ;
struct mlx5e_priv {TYPE_3__ fs; TYPE_1__* netdev; } ;
struct TYPE_9__ {int /*<<< orphan*/  t; } ;
struct TYPE_10__ {TYPE_4__ ft; } ;
struct TYPE_6__ {int hw_features; } ;

/* Variables and functions */
 int ARFS_NUM_TYPES ; 
 int /*<<< orphan*/  IS_ERR_OR_NULL (int /*<<< orphan*/ ) ; 
 int NETIF_F_NTUPLE ; 
 int /*<<< orphan*/  arfs_del_rules (struct mlx5e_priv*) ; 
 int /*<<< orphan*/  arfs_destroy_table (TYPE_5__*) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 

void mlx5e_arfs_destroy_tables(struct mlx5e_priv *priv)
{
	int i;

	if (!(priv->netdev->hw_features & NETIF_F_NTUPLE))
		return;

	arfs_del_rules(priv);
	destroy_workqueue(priv->fs.arfs.wq);
	for (i = 0; i < ARFS_NUM_TYPES; i++) {
		if (!IS_ERR_OR_NULL(priv->fs.arfs.arfs_tables[i].ft.t))
			arfs_destroy_table(&priv->fs.arfs.arfs_tables[i]);
	}
}