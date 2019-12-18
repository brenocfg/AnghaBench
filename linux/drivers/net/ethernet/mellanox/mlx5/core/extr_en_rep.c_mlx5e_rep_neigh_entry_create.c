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
struct mlx5e_neigh_hash_entry {int /*<<< orphan*/  refcnt; int /*<<< orphan*/  encap_list; int /*<<< orphan*/  encap_list_lock; int /*<<< orphan*/  neigh_update_work; int /*<<< orphan*/  m_neigh; struct mlx5e_priv* priv; } ;
struct mlx5e_encap_entry {int /*<<< orphan*/  m_neigh; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct mlx5e_neigh_hash_entry*) ; 
 struct mlx5e_neigh_hash_entry* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int mlx5e_rep_neigh_entry_insert (struct mlx5e_priv*,struct mlx5e_neigh_hash_entry*) ; 
 int /*<<< orphan*/  mlx5e_rep_neigh_update ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mlx5e_rep_neigh_entry_create(struct mlx5e_priv *priv,
					struct mlx5e_encap_entry *e,
					struct mlx5e_neigh_hash_entry **nhe)
{
	int err;

	*nhe = kzalloc(sizeof(**nhe), GFP_KERNEL);
	if (!*nhe)
		return -ENOMEM;

	(*nhe)->priv = priv;
	memcpy(&(*nhe)->m_neigh, &e->m_neigh, sizeof(e->m_neigh));
	INIT_WORK(&(*nhe)->neigh_update_work, mlx5e_rep_neigh_update);
	spin_lock_init(&(*nhe)->encap_list_lock);
	INIT_LIST_HEAD(&(*nhe)->encap_list);
	refcount_set(&(*nhe)->refcnt, 1);

	err = mlx5e_rep_neigh_entry_insert(priv, *nhe);
	if (err)
		goto out_free;
	return 0;

out_free:
	kfree(*nhe);
	return err;
}