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
struct mod_hdr_tbl {int /*<<< orphan*/  lock; } ;
struct mlx5e_priv {int /*<<< orphan*/  mdev; } ;
struct mlx5e_mod_hdr_entry {scalar_t__ compl_result; int /*<<< orphan*/  modify_hdr; int /*<<< orphan*/  flows; int /*<<< orphan*/  mod_hdr_hlist; int /*<<< orphan*/  refcnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct mod_hdr_tbl* get_mod_hdr_table (struct mlx5e_priv*,int) ; 
 int /*<<< orphan*/  hash_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct mlx5e_mod_hdr_entry*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5_modify_header_dealloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refcount_dec_and_mutex_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mlx5e_mod_hdr_put(struct mlx5e_priv *priv,
			      struct mlx5e_mod_hdr_entry *mh,
			      int namespace)
{
	struct mod_hdr_tbl *tbl = get_mod_hdr_table(priv, namespace);

	if (!refcount_dec_and_mutex_lock(&mh->refcnt, &tbl->lock))
		return;
	hash_del(&mh->mod_hdr_hlist);
	mutex_unlock(&tbl->lock);

	WARN_ON(!list_empty(&mh->flows));
	if (mh->compl_result > 0)
		mlx5_modify_header_dealloc(priv->mdev, mh->modify_hdr);

	kfree(mh);
}