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
typedef  int u8 ;
struct TYPE_2__ {scalar_t__ steering_mode; } ;
struct mlx4_dev {TYPE_1__ caps; } ;
typedef  enum mlx4_protocol { ____Placeholder_mlx4_protocol } mlx4_protocol ;

/* Variables and functions */
 int EINVAL ; 
 int MLX4_PROT_ETH ; 
 scalar_t__ MLX4_STEERING_MODE_B0 ; 
 scalar_t__ MLX4_STEERING_MODE_DEVICE_MANAGED ; 
 int mlx4_slave_convert_port (struct mlx4_dev*,int,int) ; 

__attribute__((used)) static int mlx4_adjust_port(struct mlx4_dev *dev, int slave,
			    u8 *gid, enum mlx4_protocol prot)
{
	int real_port;

	if (prot != MLX4_PROT_ETH)
		return 0;

	if (dev->caps.steering_mode == MLX4_STEERING_MODE_B0 ||
	    dev->caps.steering_mode == MLX4_STEERING_MODE_DEVICE_MANAGED) {
		real_port = mlx4_slave_convert_port(dev, slave, gid[5]);
		if (real_port < 0)
			return -EINVAL;
		gid[5] = real_port;
	}

	return 0;
}