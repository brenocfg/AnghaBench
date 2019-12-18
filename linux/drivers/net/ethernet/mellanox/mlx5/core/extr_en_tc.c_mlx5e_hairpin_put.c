#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  hairpin_tbl_lock; } ;
struct TYPE_9__ {TYPE_4__ tc; } ;
struct mlx5e_priv {int /*<<< orphan*/  netdev; TYPE_3__ fs; } ;
struct mlx5e_hairpin_entry {int /*<<< orphan*/  flows; TYPE_5__* hp; int /*<<< orphan*/  hairpin_hlist; int /*<<< orphan*/  refcnt; } ;
struct TYPE_11__ {TYPE_2__* pair; } ;
struct TYPE_8__ {TYPE_1__* peer_mdev; } ;
struct TYPE_7__ {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR_OR_NULL (TYPE_5__*) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hash_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct mlx5e_hairpin_entry*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5e_hairpin_destroy (TYPE_5__*) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  refcount_dec_and_mutex_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mlx5e_hairpin_put(struct mlx5e_priv *priv,
			      struct mlx5e_hairpin_entry *hpe)
{
	/* no more hairpin flows for us, release the hairpin pair */
	if (!refcount_dec_and_mutex_lock(&hpe->refcnt, &priv->fs.tc.hairpin_tbl_lock))
		return;
	hash_del(&hpe->hairpin_hlist);
	mutex_unlock(&priv->fs.tc.hairpin_tbl_lock);

	if (!IS_ERR_OR_NULL(hpe->hp)) {
		netdev_dbg(priv->netdev, "del hairpin: peer %s\n",
			   dev_name(hpe->hp->pair->peer_mdev->device));

		mlx5e_hairpin_destroy(hpe->hp);
	}

	WARN_ON(!list_empty(&hpe->flows));
	kfree(hpe);
}