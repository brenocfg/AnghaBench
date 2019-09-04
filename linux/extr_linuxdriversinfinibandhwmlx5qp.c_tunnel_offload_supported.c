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
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 scalar_t__ MLX5_CAP_ETH (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tunnel_stateless_geneve_rx ; 
 int /*<<< orphan*/  tunnel_stateless_gre ; 
 int /*<<< orphan*/  tunnel_stateless_vxlan ; 

__attribute__((used)) static bool tunnel_offload_supported(struct mlx5_core_dev *dev)
{
	return  (MLX5_CAP_ETH(dev, tunnel_stateless_vxlan) ||
		 MLX5_CAP_ETH(dev, tunnel_stateless_gre) ||
		 MLX5_CAP_ETH(dev, tunnel_stateless_geneve_rx));
}