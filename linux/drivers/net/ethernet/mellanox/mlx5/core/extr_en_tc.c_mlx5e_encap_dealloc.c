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
struct mlx5e_priv {int /*<<< orphan*/  mdev; } ;
struct mlx5e_encap_entry {scalar_t__ compl_result; int flags; int /*<<< orphan*/  encap_header; int /*<<< orphan*/  tun_info; int /*<<< orphan*/  pkt_reformat; int /*<<< orphan*/  out_dev; int /*<<< orphan*/  flows; } ;

/* Variables and functions */
 int MLX5_ENCAP_ENTRY_VALID ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_rcu (struct mlx5e_encap_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5_packet_reformat_dealloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5e_rep_encap_entry_detach (int /*<<< orphan*/ ,struct mlx5e_encap_entry*) ; 
 int /*<<< orphan*/  netdev_priv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu ; 

__attribute__((used)) static void mlx5e_encap_dealloc(struct mlx5e_priv *priv, struct mlx5e_encap_entry *e)
{
	WARN_ON(!list_empty(&e->flows));

	if (e->compl_result > 0) {
		mlx5e_rep_encap_entry_detach(netdev_priv(e->out_dev), e);

		if (e->flags & MLX5_ENCAP_ENTRY_VALID)
			mlx5_packet_reformat_dealloc(priv->mdev, e->pkt_reformat);
	}

	kfree(e->tun_info);
	kfree(e->encap_header);
	kfree_rcu(e, rcu);
}