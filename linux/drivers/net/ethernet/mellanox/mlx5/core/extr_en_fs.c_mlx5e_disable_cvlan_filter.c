#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int cvlan_filter_disabled; } ;
struct TYPE_5__ {TYPE_1__ vlan; } ;
struct mlx5e_priv {TYPE_3__* netdev; TYPE_2__ fs; } ;
struct TYPE_6__ {int flags; } ;

/* Variables and functions */
 int IFF_PROMISC ; 
 int /*<<< orphan*/  MLX5E_VLAN_RULE_TYPE_ANY_CTAG_VID ; 
 int /*<<< orphan*/  mlx5e_add_vlan_rule (struct mlx5e_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void mlx5e_disable_cvlan_filter(struct mlx5e_priv *priv)
{
	if (priv->fs.vlan.cvlan_filter_disabled)
		return;

	priv->fs.vlan.cvlan_filter_disabled = true;
	if (priv->netdev->flags & IFF_PROMISC)
		return;
	mlx5e_add_vlan_rule(priv, MLX5E_VLAN_RULE_TYPE_ANY_CTAG_VID, 0);
}