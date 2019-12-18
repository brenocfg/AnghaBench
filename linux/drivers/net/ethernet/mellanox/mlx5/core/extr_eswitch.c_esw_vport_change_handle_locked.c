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
typedef  int /*<<< orphan*/  u8 ;
struct mlx5_vport {int enabled_events; int /*<<< orphan*/  vport; scalar_t__ enabled; int /*<<< orphan*/  allmulti_rule; struct mlx5_core_dev* dev; } ;
struct mlx5_eswitch {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {struct mlx5_eswitch* eswitch; } ;
struct mlx5_core_dev {TYPE_1__ priv; } ;

/* Variables and functions */
 int ETH_ALEN ; 
 int /*<<< orphan*/  IS_ERR_OR_NULL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_NVPRT_LIST_TYPE_MC ; 
 int /*<<< orphan*/  MLX5_NVPRT_LIST_TYPE_UC ; 
 int MLX5_VPORT_MC_ADDR_CHANGE ; 
 int MLX5_VPORT_PROMISC_CHANGE ; 
 int MLX5_VPORT_UC_ADDR_CHANGE ; 
 int /*<<< orphan*/  arm_vport_context_events_cmd (struct mlx5_core_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  esw_apply_vport_addr_list (struct mlx5_eswitch*,struct mlx5_vport*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esw_debug (struct mlx5_core_dev*,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  esw_update_vport_addr_list (struct mlx5_eswitch*,struct mlx5_vport*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esw_update_vport_mc_promisc (struct mlx5_eswitch*,struct mlx5_vport*) ; 
 int /*<<< orphan*/  esw_update_vport_rx_mode (struct mlx5_eswitch*,struct mlx5_vport*) ; 
 int /*<<< orphan*/  mlx5_query_nic_vport_mac_address (struct mlx5_core_dev*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void esw_vport_change_handle_locked(struct mlx5_vport *vport)
{
	struct mlx5_core_dev *dev = vport->dev;
	struct mlx5_eswitch *esw = dev->priv.eswitch;
	u8 mac[ETH_ALEN];

	mlx5_query_nic_vport_mac_address(dev, vport->vport, true, mac);
	esw_debug(dev, "vport[%d] Context Changed: perm mac: %pM\n",
		  vport->vport, mac);

	if (vport->enabled_events & MLX5_VPORT_UC_ADDR_CHANGE) {
		esw_update_vport_addr_list(esw, vport, MLX5_NVPRT_LIST_TYPE_UC);
		esw_apply_vport_addr_list(esw, vport, MLX5_NVPRT_LIST_TYPE_UC);
	}

	if (vport->enabled_events & MLX5_VPORT_MC_ADDR_CHANGE)
		esw_update_vport_addr_list(esw, vport, MLX5_NVPRT_LIST_TYPE_MC);

	if (vport->enabled_events & MLX5_VPORT_PROMISC_CHANGE) {
		esw_update_vport_rx_mode(esw, vport);
		if (!IS_ERR_OR_NULL(vport->allmulti_rule))
			esw_update_vport_mc_promisc(esw, vport);
	}

	if (vport->enabled_events & (MLX5_VPORT_PROMISC_CHANGE | MLX5_VPORT_MC_ADDR_CHANGE))
		esw_apply_vport_addr_list(esw, vport, MLX5_NVPRT_LIST_TYPE_MC);

	esw_debug(esw->dev, "vport[%d] Context Changed: Done\n", vport->vport);
	if (vport->enabled)
		arm_vport_context_events_cmd(dev, vport->vport,
					     vport->enabled_events);
}