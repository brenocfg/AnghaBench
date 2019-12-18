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
struct netlink_ext_ack {int dummy; } ;
struct net_device {int dummy; } ;
struct mlx5e_tc_tunnel {int (* init_encap_attr ) (struct net_device*,struct mlx5e_priv*,struct mlx5e_encap_entry*,struct netlink_ext_ack*) ;} ;
struct mlx5e_priv {int dummy; } ;
struct mlx5e_encap_entry {int reformat_type; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 struct mlx5e_tc_tunnel* mlx5e_get_tc_tun (struct net_device*) ; 
 int stub1 (struct net_device*,struct mlx5e_priv*,struct mlx5e_encap_entry*,struct netlink_ext_ack*) ; 

int mlx5e_tc_tun_init_encap_attr(struct net_device *tunnel_dev,
				 struct mlx5e_priv *priv,
				 struct mlx5e_encap_entry *e,
				 struct netlink_ext_ack *extack)
{
	struct mlx5e_tc_tunnel *tunnel = mlx5e_get_tc_tun(tunnel_dev);

	if (!tunnel) {
		e->reformat_type = -1;
		return -EOPNOTSUPP;
	}

	return tunnel->init_encap_attr(tunnel_dev, priv, e, extack);
}