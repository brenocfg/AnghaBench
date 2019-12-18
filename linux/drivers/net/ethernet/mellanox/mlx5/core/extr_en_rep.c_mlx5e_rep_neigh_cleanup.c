#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct mlx5e_neigh_update_table {int /*<<< orphan*/  neigh_ht; int /*<<< orphan*/  encap_lock; int /*<<< orphan*/  neigh_stats_work; int /*<<< orphan*/  netevent_nb; } ;
struct mlx5e_rep_priv {struct mlx5e_neigh_update_table neigh_update; int /*<<< orphan*/  netdev; } ;
struct mlx5e_priv {int /*<<< orphan*/  wq; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 struct mlx5e_priv* netdev_priv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rhashtable_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_netevent_notifier (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mlx5e_rep_neigh_cleanup(struct mlx5e_rep_priv *rpriv)
{
	struct mlx5e_neigh_update_table *neigh_update = &rpriv->neigh_update;
	struct mlx5e_priv *priv = netdev_priv(rpriv->netdev);

	unregister_netevent_notifier(&neigh_update->netevent_nb);

	flush_workqueue(priv->wq); /* flush neigh update works */

	cancel_delayed_work_sync(&rpriv->neigh_update.neigh_stats_work);

	mutex_destroy(&neigh_update->encap_lock);
	rhashtable_destroy(&neigh_update->neigh_ht);
}