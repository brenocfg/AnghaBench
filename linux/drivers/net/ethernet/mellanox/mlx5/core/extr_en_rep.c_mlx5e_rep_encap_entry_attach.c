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
struct TYPE_2__ {int /*<<< orphan*/  encap_lock; } ;
struct mlx5_tun_entropy {int dummy; } ;
struct mlx5_rep_uplink_priv {struct mlx5_tun_entropy tun_entropy; } ;
struct mlx5e_rep_priv {TYPE_1__ neigh_update; struct mlx5_rep_uplink_priv uplink_priv; } ;
struct mlx5e_priv {struct mlx5e_rep_priv* ppriv; } ;
struct mlx5e_neigh_hash_entry {int /*<<< orphan*/  encap_list_lock; int /*<<< orphan*/  encap_list; } ;
struct mlx5e_encap_entry {int /*<<< orphan*/  encap_list; struct mlx5e_neigh_hash_entry* nhe; int /*<<< orphan*/  reformat_type; int /*<<< orphan*/  m_neigh; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5_tun_entropy_refcount_dec (struct mlx5_tun_entropy*,int /*<<< orphan*/ ) ; 
 int mlx5_tun_entropy_refcount_inc (struct mlx5_tun_entropy*,int /*<<< orphan*/ ) ; 
 int mlx5e_rep_neigh_entry_create (struct mlx5e_priv*,struct mlx5e_encap_entry*,struct mlx5e_neigh_hash_entry**) ; 
 struct mlx5e_neigh_hash_entry* mlx5e_rep_neigh_entry_lookup (struct mlx5e_priv*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int mlx5e_rep_encap_entry_attach(struct mlx5e_priv *priv,
				 struct mlx5e_encap_entry *e)
{
	struct mlx5e_rep_priv *rpriv = priv->ppriv;
	struct mlx5_rep_uplink_priv *uplink_priv = &rpriv->uplink_priv;
	struct mlx5_tun_entropy *tun_entropy = &uplink_priv->tun_entropy;
	struct mlx5e_neigh_hash_entry *nhe;
	int err;

	err = mlx5_tun_entropy_refcount_inc(tun_entropy, e->reformat_type);
	if (err)
		return err;

	mutex_lock(&rpriv->neigh_update.encap_lock);
	nhe = mlx5e_rep_neigh_entry_lookup(priv, &e->m_neigh);
	if (!nhe) {
		err = mlx5e_rep_neigh_entry_create(priv, e, &nhe);
		if (err) {
			mutex_unlock(&rpriv->neigh_update.encap_lock);
			mlx5_tun_entropy_refcount_dec(tun_entropy,
						      e->reformat_type);
			return err;
		}
	}

	e->nhe = nhe;
	spin_lock(&nhe->encap_list_lock);
	list_add_rcu(&e->encap_list, &nhe->encap_list);
	spin_unlock(&nhe->encap_list_lock);

	mutex_unlock(&rpriv->neigh_update.encap_lock);

	return 0;
}