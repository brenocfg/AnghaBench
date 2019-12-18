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
struct TYPE_4__ {int /*<<< orphan*/  encap_lock; int /*<<< orphan*/  neigh_ht; } ;
struct mlx5e_rep_priv {TYPE_2__ neigh_update; } ;
struct mlx5e_neigh_hash_entry {int /*<<< orphan*/  rhash_node; int /*<<< orphan*/  neigh_list; TYPE_1__* priv; } ;
struct TYPE_3__ {struct mlx5e_rep_priv* ppriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5e_neigh_ht_params ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rhashtable_remove_fast (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mlx5e_rep_neigh_entry_remove(struct mlx5e_neigh_hash_entry *nhe)
{
	struct mlx5e_rep_priv *rpriv = nhe->priv->ppriv;

	mutex_lock(&rpriv->neigh_update.encap_lock);

	list_del_rcu(&nhe->neigh_list);

	rhashtable_remove_fast(&rpriv->neigh_update.neigh_ht,
			       &nhe->rhash_node,
			       mlx5e_neigh_ht_params);
	mutex_unlock(&rpriv->neigh_update.encap_lock);
}