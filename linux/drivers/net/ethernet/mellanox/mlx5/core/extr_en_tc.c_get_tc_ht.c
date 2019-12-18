#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct rhashtable {int dummy; } ;
struct TYPE_8__ {struct rhashtable tc_ht; } ;
struct mlx5e_rep_priv {TYPE_3__ uplink_priv; } ;
struct TYPE_9__ {struct rhashtable ht; } ;
struct TYPE_10__ {TYPE_4__ tc; } ;
struct mlx5e_priv {TYPE_5__ fs; TYPE_2__* mdev; } ;
struct mlx5_eswitch {int dummy; } ;
struct TYPE_6__ {struct mlx5_eswitch* eswitch; } ;
struct TYPE_7__ {TYPE_1__ priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESW_OFFLOAD ; 
 unsigned long MLX5_TC_FLAG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REP_ETH ; 
 struct mlx5e_rep_priv* mlx5_eswitch_get_uplink_priv (struct mlx5_eswitch*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct rhashtable *get_tc_ht(struct mlx5e_priv *priv,
				    unsigned long flags)
{
	struct mlx5_eswitch *esw = priv->mdev->priv.eswitch;
	struct mlx5e_rep_priv *uplink_rpriv;

	if (flags & MLX5_TC_FLAG(ESW_OFFLOAD)) {
		uplink_rpriv = mlx5_eswitch_get_uplink_priv(esw, REP_ETH);
		return &uplink_rpriv->uplink_priv.tc_ht;
	} else /* NIC offload */
		return &priv->fs.tc.ht;
}