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
struct mlx5_tun_entropy {int dummy; } ;
struct mlx5_rep_uplink_priv {struct mlx5_tun_entropy tun_entropy; } ;
struct mlx5e_rep_priv {struct mlx5_rep_uplink_priv uplink_priv; } ;
struct mlx5e_priv {struct mlx5e_rep_priv* ppriv; } ;
struct mlx5e_encap_entry {int /*<<< orphan*/  reformat_type; TYPE_1__* nhe; int /*<<< orphan*/  encap_list; } ;
struct TYPE_2__ {int /*<<< orphan*/  encap_list_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5_tun_entropy_refcount_dec (struct mlx5_tun_entropy*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5e_rep_neigh_entry_release (TYPE_1__*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void mlx5e_rep_encap_entry_detach(struct mlx5e_priv *priv,
				  struct mlx5e_encap_entry *e)
{
	struct mlx5e_rep_priv *rpriv = priv->ppriv;
	struct mlx5_rep_uplink_priv *uplink_priv = &rpriv->uplink_priv;
	struct mlx5_tun_entropy *tun_entropy = &uplink_priv->tun_entropy;

	if (!e->nhe)
		return;

	spin_lock(&e->nhe->encap_list_lock);
	list_del_rcu(&e->encap_list);
	spin_unlock(&e->nhe->encap_list_lock);

	mlx5e_rep_neigh_entry_release(e->nhe);
	e->nhe = NULL;
	mlx5_tun_entropy_refcount_dec(tun_entropy, e->reformat_type);
}