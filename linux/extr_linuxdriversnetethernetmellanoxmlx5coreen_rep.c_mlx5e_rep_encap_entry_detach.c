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
struct mlx5e_encap_entry {int /*<<< orphan*/  m_neigh; int /*<<< orphan*/  encap_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5e_rep_neigh_entry_destroy (struct mlx5e_priv*,struct mlx5e_neigh_hash_entry*) ; 
 struct mlx5e_neigh_hash_entry* mlx5e_rep_neigh_entry_lookup (struct mlx5e_priv*,int /*<<< orphan*/ *) ; 

void mlx5e_rep_encap_entry_detach(struct mlx5e_priv *priv,
				  struct mlx5e_encap_entry *e)
{
	struct mlx5e_neigh_hash_entry *nhe;

	list_del(&e->encap_list);
	nhe = mlx5e_rep_neigh_entry_lookup(priv, &e->m_neigh);

	if (list_empty(&nhe->encap_list))
		mlx5e_rep_neigh_entry_destroy(priv, nhe);
}