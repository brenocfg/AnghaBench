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
struct mlx4_dev_cap {int flags2; } ;
struct TYPE_2__ {scalar_t__ steering_mode; scalar_t__ tunnel_offload_mode; } ;
struct mlx4_dev {TYPE_1__ caps; } ;

/* Variables and functions */
 int MLX4_DEV_CAP_FLAG2_VXLAN_OFFLOADS ; 
 scalar_t__ MLX4_STEERING_MODE_DEVICE_MANAGED ; 
 scalar_t__ MLX4_TUNNEL_OFFLOAD_MODE_NONE ; 
 scalar_t__ MLX4_TUNNEL_OFFLOAD_MODE_VXLAN ; 
 int /*<<< orphan*/  mlx4_dbg (struct mlx4_dev*,char*,char*) ; 

__attribute__((used)) static void choose_tunnel_offload_mode(struct mlx4_dev *dev,
				       struct mlx4_dev_cap *dev_cap)
{
	if (dev->caps.steering_mode == MLX4_STEERING_MODE_DEVICE_MANAGED &&
	    dev_cap->flags2 & MLX4_DEV_CAP_FLAG2_VXLAN_OFFLOADS)
		dev->caps.tunnel_offload_mode = MLX4_TUNNEL_OFFLOAD_MODE_VXLAN;
	else
		dev->caps.tunnel_offload_mode = MLX4_TUNNEL_OFFLOAD_MODE_NONE;

	mlx4_dbg(dev, "Tunneling offload mode is: %s\n",  (dev->caps.tunnel_offload_mode
		 == MLX4_TUNNEL_OFFLOAD_MODE_VXLAN) ? "vxlan" : "none");
}