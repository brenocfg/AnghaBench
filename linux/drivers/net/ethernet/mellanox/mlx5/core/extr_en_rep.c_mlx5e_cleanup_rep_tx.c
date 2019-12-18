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
struct TYPE_4__ {int /*<<< orphan*/  unready_flows_lock; int /*<<< orphan*/  tc_ht; int /*<<< orphan*/  netdevice_nb; } ;
struct mlx5e_rep_priv {TYPE_2__ uplink_priv; TYPE_1__* rep; } ;
struct mlx5e_priv {struct mlx5e_rep_priv* ppriv; } ;
struct TYPE_3__ {scalar_t__ vport; } ;

/* Variables and functions */
 scalar_t__ MLX5_VPORT_UPLINK ; 
 int /*<<< orphan*/  mlx5e_destroy_tises (struct mlx5e_priv*) ; 
 int /*<<< orphan*/  mlx5e_rep_indr_clean_block_privs (struct mlx5e_rep_priv*) ; 
 int /*<<< orphan*/  mlx5e_tc_esw_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_netdevice_notifier (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mlx5e_cleanup_rep_tx(struct mlx5e_priv *priv)
{
	struct mlx5e_rep_priv *rpriv = priv->ppriv;

	mlx5e_destroy_tises(priv);

	if (rpriv->rep->vport == MLX5_VPORT_UPLINK) {
		/* clean indirect TC block notifications */
		unregister_netdevice_notifier(&rpriv->uplink_priv.netdevice_nb);
		mlx5e_rep_indr_clean_block_privs(rpriv);

		/* delete shared tc flow table */
		mlx5e_tc_esw_cleanup(&rpriv->uplink_priv.tc_ht);
		mutex_destroy(&rpriv->uplink_priv.unready_flows_lock);
	}
}