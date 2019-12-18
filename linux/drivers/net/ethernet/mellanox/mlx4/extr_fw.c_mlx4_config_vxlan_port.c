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
struct mlx4_dev {int dummy; } ;
struct mlx4_config_dev {int /*<<< orphan*/  vxlan_udp_dport; int /*<<< orphan*/  update_flags; } ;
typedef  int /*<<< orphan*/  config_dev ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  MLX4_VXLAN_UDP_DPORT ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct mlx4_config_dev*,int /*<<< orphan*/ ,int) ; 
 int mlx4_CONFIG_DEV_set (struct mlx4_dev*,struct mlx4_config_dev*) ; 

int mlx4_config_vxlan_port(struct mlx4_dev *dev, __be16 udp_port)
{
	struct mlx4_config_dev config_dev;

	memset(&config_dev, 0, sizeof(config_dev));
	config_dev.update_flags    = cpu_to_be32(MLX4_VXLAN_UDP_DPORT);
	config_dev.vxlan_udp_dport = udp_port;

	return mlx4_CONFIG_DEV_set(dev, &config_dev);
}