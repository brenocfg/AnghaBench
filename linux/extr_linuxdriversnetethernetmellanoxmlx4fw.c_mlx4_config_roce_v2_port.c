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
typedef  int /*<<< orphan*/  u16 ;
struct mlx4_dev {int dummy; } ;
struct mlx4_config_dev {int /*<<< orphan*/  roce_v2_udp_dport; int /*<<< orphan*/  update_flags; } ;
typedef  int /*<<< orphan*/  config_dev ;

/* Variables and functions */
 int /*<<< orphan*/  MLX4_ROCE_V2_UDP_DPORT ; 
 int /*<<< orphan*/  cpu_to_be16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct mlx4_config_dev*,int /*<<< orphan*/ ,int) ; 
 int mlx4_CONFIG_DEV_set (struct mlx4_dev*,struct mlx4_config_dev*) ; 

int mlx4_config_roce_v2_port(struct mlx4_dev *dev, u16 udp_port)
{
	struct mlx4_config_dev config_dev;

	memset(&config_dev, 0, sizeof(config_dev));
	config_dev.update_flags    = cpu_to_be32(MLX4_ROCE_V2_UDP_DPORT);
	config_dev.roce_v2_udp_dport = cpu_to_be16(udp_port);

	return mlx4_CONFIG_DEV_set(dev, &config_dev);
}