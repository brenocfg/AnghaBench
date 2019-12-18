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
struct net_device {int dummy; } ;
struct mlx5e_tc_tunnel {scalar_t__ (* can_offload ) (struct mlx5e_priv*) ;} ;
struct mlx5e_priv {int dummy; } ;

/* Variables and functions */
 struct mlx5e_tc_tunnel* mlx5e_get_tc_tun (struct net_device*) ; 
 scalar_t__ stub1 (struct mlx5e_priv*) ; 

bool mlx5e_tc_tun_device_to_offload(struct mlx5e_priv *priv,
				    struct net_device *netdev)
{
	struct mlx5e_tc_tunnel *tunnel = mlx5e_get_tc_tun(netdev);

	if (tunnel && tunnel->can_offload(priv))
		return true;
	else
		return false;
}