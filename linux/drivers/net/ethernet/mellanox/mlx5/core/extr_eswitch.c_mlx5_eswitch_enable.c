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
struct TYPE_2__ {int /*<<< orphan*/  num_vfs; } ;
struct mlx5_eswitch {int mode; int /*<<< orphan*/  dev; int /*<<< orphan*/  enabled_vports; TYPE_1__ esw_funcs; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  ESW_ALLOWED (struct mlx5_eswitch*) ; 
 int /*<<< orphan*/  MLX5_CAP_ESW_EGRESS_ACL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_CAP_ESW_FLOWTABLE_FDB (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_CAP_ESW_INGRESS_ACL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MLX5_ESWITCH_LEGACY ; 
 int MLX5_ESWITCH_NONE ; 
 int MLX5_ESWITCH_OFFLOADS ; 
 int /*<<< orphan*/  MLX5_INTERFACE_PROTOCOL_ETH ; 
 int /*<<< orphan*/  MLX5_INTERFACE_PROTOCOL_IB ; 
 int /*<<< orphan*/  esw_create_tsar (struct mlx5_eswitch*) ; 
 int /*<<< orphan*/  esw_info (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int esw_legacy_enable (struct mlx5_eswitch*) ; 
 int esw_offloads_enable (struct mlx5_eswitch*) ; 
 int /*<<< orphan*/  esw_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ft_support ; 
 int /*<<< orphan*/  mlx5_eswitch_event_handlers_register (struct mlx5_eswitch*) ; 
 int /*<<< orphan*/  mlx5_lag_update (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_reload_interface (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int mlx5_eswitch_enable(struct mlx5_eswitch *esw, int mode)
{
	int err;

	if (!ESW_ALLOWED(esw) ||
	    !MLX5_CAP_ESW_FLOWTABLE_FDB(esw->dev, ft_support)) {
		esw_warn(esw->dev, "FDB is not supported, aborting ...\n");
		return -EOPNOTSUPP;
	}

	if (!MLX5_CAP_ESW_INGRESS_ACL(esw->dev, ft_support))
		esw_warn(esw->dev, "ingress ACL is not supported by FW\n");

	if (!MLX5_CAP_ESW_EGRESS_ACL(esw->dev, ft_support))
		esw_warn(esw->dev, "engress ACL is not supported by FW\n");

	esw_create_tsar(esw);

	esw->mode = mode;

	mlx5_lag_update(esw->dev);

	if (mode == MLX5_ESWITCH_LEGACY) {
		err = esw_legacy_enable(esw);
	} else {
		mlx5_reload_interface(esw->dev, MLX5_INTERFACE_PROTOCOL_ETH);
		mlx5_reload_interface(esw->dev, MLX5_INTERFACE_PROTOCOL_IB);
		err = esw_offloads_enable(esw);
	}

	if (err)
		goto abort;

	mlx5_eswitch_event_handlers_register(esw);

	esw_info(esw->dev, "Enable: mode(%s), nvfs(%d), active vports(%d)\n",
		 mode == MLX5_ESWITCH_LEGACY ? "LEGACY" : "OFFLOADS",
		 esw->esw_funcs.num_vfs, esw->enabled_vports);

	return 0;

abort:
	esw->mode = MLX5_ESWITCH_NONE;

	if (mode == MLX5_ESWITCH_OFFLOADS) {
		mlx5_reload_interface(esw->dev, MLX5_INTERFACE_PROTOCOL_IB);
		mlx5_reload_interface(esw->dev, MLX5_INTERFACE_PROTOCOL_ETH);
	}

	return err;
}