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
typedef  int u32 ;
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 int MLX5_ACCEL_IPSEC_CAP_DEVICE ; 
 int MLX5_ACCEL_IPSEC_CAP_ESP ; 
 int MLX5_ACCEL_IPSEC_CAP_IPV6 ; 
 int MLX5_MATCH_OUTER_HEADERS ; 
 int mlx5_accel_ipsec_device_caps (struct mlx5_core_dev*) ; 
 scalar_t__ mlx5_fs_is_outer_ipsec_flow (int const*) ; 
 scalar_t__ mlx5_fs_is_outer_ipv4_flow (struct mlx5_core_dev*,int const*,int const*) ; 
 int mlx5_fs_is_outer_ipv6_flow (struct mlx5_core_dev*,int const*,int const*) ; 
 scalar_t__ mlx5_fs_is_outer_tcp_flow (int const*,int const*) ; 
 scalar_t__ mlx5_fs_is_outer_udp_flow (int const*,int const*) ; 
 scalar_t__ mlx5_fs_is_vxlan_flow (int const*) ; 
 int /*<<< orphan*/  validate_fpga_full_mask (struct mlx5_core_dev*,int const*,int const*) ; 

__attribute__((used)) static bool mlx5_is_fpga_ipsec_rule(struct mlx5_core_dev *dev,
				    u8 match_criteria_enable,
				    const u32 *match_c,
				    const u32 *match_v)
{
	u32 ipsec_dev_caps = mlx5_accel_ipsec_device_caps(dev);
	bool ipv6_flow;

	ipv6_flow = mlx5_fs_is_outer_ipv6_flow(dev, match_c, match_v);

	if (!(match_criteria_enable & MLX5_MATCH_OUTER_HEADERS) ||
	    mlx5_fs_is_outer_udp_flow(match_c, match_v) ||
	    mlx5_fs_is_outer_tcp_flow(match_c, match_v) ||
	    mlx5_fs_is_vxlan_flow(match_c) ||
	    !(mlx5_fs_is_outer_ipv4_flow(dev, match_c, match_v) ||
	      ipv6_flow))
		return false;

	if (!(ipsec_dev_caps & MLX5_ACCEL_IPSEC_CAP_DEVICE))
		return false;

	if (!(ipsec_dev_caps & MLX5_ACCEL_IPSEC_CAP_ESP) &&
	    mlx5_fs_is_outer_ipsec_flow(match_c))
		return false;

	if (!(ipsec_dev_caps & MLX5_ACCEL_IPSEC_CAP_IPV6) &&
	    ipv6_flow)
		return false;

	if (!validate_fpga_full_mask(dev, match_c, match_v))
		return false;

	return true;
}