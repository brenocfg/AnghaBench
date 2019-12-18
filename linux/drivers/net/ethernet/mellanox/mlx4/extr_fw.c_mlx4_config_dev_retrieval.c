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
typedef  size_t u8 ;
struct TYPE_2__ {int flags2; } ;
struct mlx4_dev {TYPE_1__ caps; } ;
struct mlx4_config_dev_params {int /*<<< orphan*/  vxlan_udp_dport; void* rx_csum_flags_port_2; void* rx_csum_flags_port_1; } ;
struct mlx4_config_dev {size_t rx_checksum_val; int /*<<< orphan*/  vxlan_udp_dport; int /*<<< orphan*/  member_0; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (void**) ; 
 size_t CONFIG_DEV_RX_CSUM_MODE_MASK ; 
 size_t CONFIG_DEV_RX_CSUM_MODE_PORT1_BIT_OFFSET ; 
 size_t CONFIG_DEV_RX_CSUM_MODE_PORT2_BIT_OFFSET ; 
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int MLX4_DEV_CAP_FLAG2_CONFIG_DEV ; 
 int /*<<< orphan*/  be16_to_cpu (int /*<<< orphan*/ ) ; 
 void** config_dev_csum_flags ; 
 int mlx4_CONFIG_DEV_get (struct mlx4_dev*,struct mlx4_config_dev*) ; 

int mlx4_config_dev_retrieval(struct mlx4_dev *dev,
			      struct mlx4_config_dev_params *params)
{
	struct mlx4_config_dev config_dev = {0};
	int err;
	u8 csum_mask;

#define CONFIG_DEV_RX_CSUM_MODE_MASK			0x7
#define CONFIG_DEV_RX_CSUM_MODE_PORT1_BIT_OFFSET	0
#define CONFIG_DEV_RX_CSUM_MODE_PORT2_BIT_OFFSET	4

	if (!(dev->caps.flags2 & MLX4_DEV_CAP_FLAG2_CONFIG_DEV))
		return -EOPNOTSUPP;

	err = mlx4_CONFIG_DEV_get(dev, &config_dev);
	if (err)
		return err;

	csum_mask = (config_dev.rx_checksum_val >> CONFIG_DEV_RX_CSUM_MODE_PORT1_BIT_OFFSET) &
			CONFIG_DEV_RX_CSUM_MODE_MASK;

	if (csum_mask >= ARRAY_SIZE(config_dev_csum_flags))
		return -EINVAL;
	params->rx_csum_flags_port_1 = config_dev_csum_flags[csum_mask];

	csum_mask = (config_dev.rx_checksum_val >> CONFIG_DEV_RX_CSUM_MODE_PORT2_BIT_OFFSET) &
			CONFIG_DEV_RX_CSUM_MODE_MASK;

	if (csum_mask >= ARRAY_SIZE(config_dev_csum_flags))
		return -EINVAL;
	params->rx_csum_flags_port_2 = config_dev_csum_flags[csum_mask];

	params->vxlan_udp_dport = be16_to_cpu(config_dev.vxlan_udp_dport);

	return 0;
}