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
struct mlx5e_tc_tunnel {int dummy; } ;

/* Variables and functions */
 struct mlx5e_tc_tunnel geneve_tunnel ; 
 struct mlx5e_tc_tunnel gre_tunnel ; 
 scalar_t__ netif_is_geneve (struct net_device*) ; 
 scalar_t__ netif_is_gretap (struct net_device*) ; 
 scalar_t__ netif_is_ip6gretap (struct net_device*) ; 
 scalar_t__ netif_is_vxlan (struct net_device*) ; 
 struct mlx5e_tc_tunnel vxlan_tunnel ; 

struct mlx5e_tc_tunnel *mlx5e_get_tc_tun(struct net_device *tunnel_dev)
{
	if (netif_is_vxlan(tunnel_dev))
		return &vxlan_tunnel;
	else if (netif_is_geneve(tunnel_dev))
		return &geneve_tunnel;
	else if (netif_is_gretap(tunnel_dev) ||
		 netif_is_ip6gretap(tunnel_dev))
		return &gre_tunnel;
	else
		return NULL;
}