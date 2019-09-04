#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct rhashtable {int dummy; } ;
struct mlx5e_rep_priv {struct rhashtable tc_ht; } ;
struct TYPE_6__ {struct rhashtable ht; } ;
struct TYPE_7__ {TYPE_2__ tc; } ;
struct mlx5e_priv {TYPE_3__ fs; TYPE_4__* mdev; } ;
struct mlx5_eswitch {scalar_t__ mode; } ;
struct TYPE_5__ {struct mlx5_eswitch* eswitch; } ;
struct TYPE_8__ {TYPE_1__ priv; } ;

/* Variables and functions */
 scalar_t__ MLX5_VPORT_MANAGER (TYPE_4__*) ; 
 int /*<<< orphan*/  REP_ETH ; 
 scalar_t__ SRIOV_OFFLOADS ; 
 struct mlx5e_rep_priv* mlx5_eswitch_get_uplink_priv (struct mlx5_eswitch*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct rhashtable *get_tc_ht(struct mlx5e_priv *priv)
{
	struct mlx5_eswitch *esw = priv->mdev->priv.eswitch;
	struct mlx5e_rep_priv *uplink_rpriv;

	if (MLX5_VPORT_MANAGER(priv->mdev) && esw->mode == SRIOV_OFFLOADS) {
		uplink_rpriv = mlx5_eswitch_get_uplink_priv(esw, REP_ETH);
		return &uplink_rpriv->tc_ht;
	} else
		return &priv->fs.tc.ht;
}