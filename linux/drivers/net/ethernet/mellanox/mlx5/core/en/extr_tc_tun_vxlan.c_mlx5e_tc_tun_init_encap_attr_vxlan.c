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
struct netlink_ext_ack {int dummy; } ;
struct net_device {int dummy; } ;
struct mlx5e_priv {int /*<<< orphan*/  netdev; TYPE_3__* mdev; } ;
struct mlx5e_encap_entry {int /*<<< orphan*/  reformat_type; int /*<<< orphan*/ * tunnel; TYPE_2__* tun_info; } ;
struct TYPE_6__ {int /*<<< orphan*/  vxlan; } ;
struct TYPE_4__ {int /*<<< orphan*/  tp_dst; } ;
struct TYPE_5__ {TYPE_1__ key; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  MLX5_REFORMAT_TYPE_L2_TO_VXLAN ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG_MOD (struct netlink_ext_ack*,char*) ; 
 int be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_vxlan_lookup_port (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netdev_warn (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  vxlan_tunnel ; 

__attribute__((used)) static int mlx5e_tc_tun_init_encap_attr_vxlan(struct net_device *tunnel_dev,
					      struct mlx5e_priv *priv,
					      struct mlx5e_encap_entry *e,
					      struct netlink_ext_ack *extack)
{
	int dst_port = be16_to_cpu(e->tun_info->key.tp_dst);

	e->tunnel = &vxlan_tunnel;

	if (!mlx5_vxlan_lookup_port(priv->mdev->vxlan, dst_port)) {
		NL_SET_ERR_MSG_MOD(extack,
				   "vxlan udp dport was not registered with the HW");
		netdev_warn(priv->netdev,
			    "%d isn't an offloaded vxlan udp dport\n",
			    dst_port);
		return -EOPNOTSUPP;
	}

	e->reformat_type = MLX5_REFORMAT_TYPE_L2_TO_VXLAN;
	return 0;
}