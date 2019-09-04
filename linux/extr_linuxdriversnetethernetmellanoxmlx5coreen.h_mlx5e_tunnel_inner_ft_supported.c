#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mlx5_core_dev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  inner_ip_version; } ;

/* Variables and functions */
 scalar_t__ MLX5_CAP_ETH (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ MLX5_CAP_FLOWTABLE_NIC_RX (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 TYPE_1__ ft_field_support ; 
 int /*<<< orphan*/  tunnel_stateless_gre ; 

__attribute__((used)) static inline bool mlx5e_tunnel_inner_ft_supported(struct mlx5_core_dev *mdev)
{
	return (MLX5_CAP_ETH(mdev, tunnel_stateless_gre) &&
		MLX5_CAP_FLOWTABLE_NIC_RX(mdev, ft_field_support.inner_ip_version));
}