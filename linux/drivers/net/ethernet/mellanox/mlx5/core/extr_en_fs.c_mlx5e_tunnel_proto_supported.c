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
typedef  int u8 ;
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
#define  IPPROTO_GRE 130 
#define  IPPROTO_IPIP 129 
#define  IPPROTO_IPV6 128 
 int MLX5_CAP_ETH (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tunnel_stateless_gre ; 
 int /*<<< orphan*/  tunnel_stateless_ip_over_ip ; 

bool mlx5e_tunnel_proto_supported(struct mlx5_core_dev *mdev, u8 proto_type)
{
	switch (proto_type) {
	case IPPROTO_GRE:
		return MLX5_CAP_ETH(mdev, tunnel_stateless_gre);
	case IPPROTO_IPIP:
	case IPPROTO_IPV6:
		return MLX5_CAP_ETH(mdev, tunnel_stateless_ip_over_ip);
	default:
		return false;
	}
}