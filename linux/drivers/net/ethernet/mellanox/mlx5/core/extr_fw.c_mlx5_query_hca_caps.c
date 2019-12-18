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
 int /*<<< orphan*/  MLX5_CAP_ATOMIC ; 
 int /*<<< orphan*/  MLX5_CAP_DEBUG ; 
 int /*<<< orphan*/  MLX5_CAP_DEV_EVENT ; 
 int /*<<< orphan*/  MLX5_CAP_DEV_MEM ; 
 int /*<<< orphan*/  MLX5_CAP_ESWITCH ; 
 int /*<<< orphan*/  MLX5_CAP_ESWITCH_FLOW_TABLE ; 
 int /*<<< orphan*/  MLX5_CAP_ETHERNET_OFFLOADS ; 
 int /*<<< orphan*/  MLX5_CAP_FLOW_TABLE ; 
 scalar_t__ MLX5_CAP_GEN (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_CAP_GENERAL ; 
 int /*<<< orphan*/  MLX5_CAP_IPOIB_ENHANCED_OFFLOADS ; 
 int /*<<< orphan*/  MLX5_CAP_ODP ; 
 int /*<<< orphan*/  MLX5_CAP_QOS ; 
 int /*<<< orphan*/  MLX5_CAP_ROCE ; 
 int /*<<< orphan*/  MLX5_CAP_TLS ; 
 int /*<<< orphan*/  MLX5_CAP_VECTOR_CALC ; 
 scalar_t__ MLX5_ESWITCH_MANAGER (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  atomic ; 
 int /*<<< orphan*/  debug ; 
 int /*<<< orphan*/  device_memory ; 
 int /*<<< orphan*/  eth_net_offloads ; 
 int /*<<< orphan*/  event_cap ; 
 int /*<<< orphan*/  ipoib_enhanced_offloads ; 
 int /*<<< orphan*/  mcam_reg ; 
 int mlx5_core_get_caps (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_get_mcam_reg (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_get_pcam_reg (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_get_qcam_reg (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  nic_flow_table ; 
 int /*<<< orphan*/  pcam_reg ; 
 int /*<<< orphan*/  pg ; 
 int /*<<< orphan*/  qcam_reg ; 
 int /*<<< orphan*/  qos ; 
 int /*<<< orphan*/  roce ; 
 int /*<<< orphan*/  tls ; 
 int /*<<< orphan*/  vector_calc ; 
 int /*<<< orphan*/  vport_group_manager ; 

int mlx5_query_hca_caps(struct mlx5_core_dev *dev)
{
	int err;

	err = mlx5_core_get_caps(dev, MLX5_CAP_GENERAL);
	if (err)
		return err;

	if (MLX5_CAP_GEN(dev, eth_net_offloads)) {
		err = mlx5_core_get_caps(dev, MLX5_CAP_ETHERNET_OFFLOADS);
		if (err)
			return err;
	}

	if (MLX5_CAP_GEN(dev, ipoib_enhanced_offloads)) {
		err = mlx5_core_get_caps(dev, MLX5_CAP_IPOIB_ENHANCED_OFFLOADS);
		if (err)
			return err;
	}

	if (MLX5_CAP_GEN(dev, pg)) {
		err = mlx5_core_get_caps(dev, MLX5_CAP_ODP);
		if (err)
			return err;
	}

	if (MLX5_CAP_GEN(dev, atomic)) {
		err = mlx5_core_get_caps(dev, MLX5_CAP_ATOMIC);
		if (err)
			return err;
	}

	if (MLX5_CAP_GEN(dev, roce)) {
		err = mlx5_core_get_caps(dev, MLX5_CAP_ROCE);
		if (err)
			return err;
	}

	if (MLX5_CAP_GEN(dev, nic_flow_table) ||
	    MLX5_CAP_GEN(dev, ipoib_enhanced_offloads)) {
		err = mlx5_core_get_caps(dev, MLX5_CAP_FLOW_TABLE);
		if (err)
			return err;
	}

	if (MLX5_CAP_GEN(dev, vport_group_manager) &&
	    MLX5_ESWITCH_MANAGER(dev)) {
		err = mlx5_core_get_caps(dev, MLX5_CAP_ESWITCH_FLOW_TABLE);
		if (err)
			return err;
	}

	if (MLX5_ESWITCH_MANAGER(dev)) {
		err = mlx5_core_get_caps(dev, MLX5_CAP_ESWITCH);
		if (err)
			return err;
	}

	if (MLX5_CAP_GEN(dev, vector_calc)) {
		err = mlx5_core_get_caps(dev, MLX5_CAP_VECTOR_CALC);
		if (err)
			return err;
	}

	if (MLX5_CAP_GEN(dev, qos)) {
		err = mlx5_core_get_caps(dev, MLX5_CAP_QOS);
		if (err)
			return err;
	}

	if (MLX5_CAP_GEN(dev, debug))
		mlx5_core_get_caps(dev, MLX5_CAP_DEBUG);

	if (MLX5_CAP_GEN(dev, pcam_reg))
		mlx5_get_pcam_reg(dev);

	if (MLX5_CAP_GEN(dev, mcam_reg))
		mlx5_get_mcam_reg(dev);

	if (MLX5_CAP_GEN(dev, qcam_reg))
		mlx5_get_qcam_reg(dev);

	if (MLX5_CAP_GEN(dev, device_memory)) {
		err = mlx5_core_get_caps(dev, MLX5_CAP_DEV_MEM);
		if (err)
			return err;
	}

	if (MLX5_CAP_GEN(dev, event_cap)) {
		err = mlx5_core_get_caps(dev, MLX5_CAP_DEV_EVENT);
		if (err)
			return err;
	}

	if (MLX5_CAP_GEN(dev, tls)) {
		err = mlx5_core_get_caps(dev, MLX5_CAP_TLS);
		if (err)
			return err;
	}

	return 0;
}