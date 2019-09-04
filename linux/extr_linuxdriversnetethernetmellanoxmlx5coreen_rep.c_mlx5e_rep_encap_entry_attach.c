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
struct mlx5e_priv {int dummy; } ;
struct mlx5e_neigh_hash_entry {int /*<<< orphan*/  encap_list; } ;
struct mlx5e_encap_entry {int /*<<< orphan*/  encap_list; int /*<<< orphan*/  m_neigh; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int mlx5e_rep_neigh_entry_create (struct mlx5e_priv*,struct mlx5e_encap_entry*,struct mlx5e_neigh_hash_entry**) ; 
 struct mlx5e_neigh_hash_entry* mlx5e_rep_neigh_entry_lookup (struct mlx5e_priv*,int /*<<< orphan*/ *) ; 

int mlx5e_rep_encap_entry_attach(struct mlx5e_priv *priv,
				 struct mlx5e_encap_entry *e)
{
	struct mlx5e_neigh_hash_entry *nhe;
	int err;

	nhe = mlx5e_rep_neigh_entry_lookup(priv, &e->m_neigh);
	if (!nhe) {
		err = mlx5e_rep_neigh_entry_create(priv, e, &nhe);
		if (err)
			return err;
	}
	list_add(&e->encap_list, &nhe->encap_list);
	return 0;
}