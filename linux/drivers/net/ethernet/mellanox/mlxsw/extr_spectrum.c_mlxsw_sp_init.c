#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  notifier_call; } ;
struct mlxsw_sp {scalar_t__ clock; TYPE_1__* ptp_ops; scalar_t__ ptp_state; TYPE_2__ netdevice_nb; struct mlxsw_bus_info const* bus_info; struct mlxsw_core* core; } ;
struct mlxsw_core {int dummy; } ;
struct mlxsw_bus_info {int /*<<< orphan*/  dev; scalar_t__ read_frc_capable; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* clock_fini ) (scalar_t__) ;int /*<<< orphan*/  (* fini ) (scalar_t__) ;scalar_t__ (* init ) (struct mlxsw_sp*) ;scalar_t__ (* clock_init ) (struct mlxsw_sp*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 scalar_t__ IS_ERR (scalar_t__) ; 
 int PTR_ERR (scalar_t__) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct mlxsw_sp* mlxsw_core_driver_priv (struct mlxsw_core*) ; 
 int /*<<< orphan*/  mlxsw_sp_acl_fini (struct mlxsw_sp*) ; 
 int mlxsw_sp_acl_init (struct mlxsw_sp*) ; 
 int /*<<< orphan*/  mlxsw_sp_afa_fini (struct mlxsw_sp*) ; 
 int mlxsw_sp_afa_init (struct mlxsw_sp*) ; 
 int mlxsw_sp_base_mac_get (struct mlxsw_sp*) ; 
 int /*<<< orphan*/  mlxsw_sp_buffers_fini (struct mlxsw_sp*) ; 
 int mlxsw_sp_buffers_init (struct mlxsw_sp*) ; 
 int /*<<< orphan*/  mlxsw_sp_counter_pool_fini (struct mlxsw_sp*) ; 
 int mlxsw_sp_counter_pool_init (struct mlxsw_sp*) ; 
 int /*<<< orphan*/  mlxsw_sp_devlink_traps_fini (struct mlxsw_sp*) ; 
 int mlxsw_sp_devlink_traps_init (struct mlxsw_sp*) ; 
 int /*<<< orphan*/  mlxsw_sp_dpipe_fini (struct mlxsw_sp*) ; 
 int mlxsw_sp_dpipe_init (struct mlxsw_sp*) ; 
 int /*<<< orphan*/  mlxsw_sp_fids_fini (struct mlxsw_sp*) ; 
 int mlxsw_sp_fids_init (struct mlxsw_sp*) ; 
 int mlxsw_sp_fw_rev_validate (struct mlxsw_sp*) ; 
 int /*<<< orphan*/  mlxsw_sp_kvdl_fini (struct mlxsw_sp*) ; 
 int mlxsw_sp_kvdl_init (struct mlxsw_sp*) ; 
 int /*<<< orphan*/  mlxsw_sp_lag_fini (struct mlxsw_sp*) ; 
 int mlxsw_sp_lag_init (struct mlxsw_sp*) ; 
 int /*<<< orphan*/  mlxsw_sp_netdevice_event ; 
 int /*<<< orphan*/  mlxsw_sp_nve_fini (struct mlxsw_sp*) ; 
 int mlxsw_sp_nve_init (struct mlxsw_sp*) ; 
 int mlxsw_sp_ports_create (struct mlxsw_sp*) ; 
 int /*<<< orphan*/  mlxsw_sp_router_fini (struct mlxsw_sp*) ; 
 int mlxsw_sp_router_init (struct mlxsw_sp*) ; 
 int /*<<< orphan*/  mlxsw_sp_span_fini (struct mlxsw_sp*) ; 
 int mlxsw_sp_span_init (struct mlxsw_sp*) ; 
 int /*<<< orphan*/  mlxsw_sp_switchdev_fini (struct mlxsw_sp*) ; 
 int mlxsw_sp_switchdev_init (struct mlxsw_sp*) ; 
 int /*<<< orphan*/  mlxsw_sp_traps_fini (struct mlxsw_sp*) ; 
 int mlxsw_sp_traps_init (struct mlxsw_sp*) ; 
 int register_netdevice_notifier (TYPE_2__*) ; 
 scalar_t__ stub1 (struct mlxsw_sp*,int /*<<< orphan*/ ) ; 
 scalar_t__ stub2 (struct mlxsw_sp*) ; 
 int /*<<< orphan*/  stub3 (scalar_t__) ; 
 int /*<<< orphan*/  stub4 (scalar_t__) ; 
 int /*<<< orphan*/  unregister_netdevice_notifier (TYPE_2__*) ; 

__attribute__((used)) static int mlxsw_sp_init(struct mlxsw_core *mlxsw_core,
			 const struct mlxsw_bus_info *mlxsw_bus_info)
{
	struct mlxsw_sp *mlxsw_sp = mlxsw_core_driver_priv(mlxsw_core);
	int err;

	mlxsw_sp->core = mlxsw_core;
	mlxsw_sp->bus_info = mlxsw_bus_info;

	err = mlxsw_sp_fw_rev_validate(mlxsw_sp);
	if (err)
		return err;

	err = mlxsw_sp_base_mac_get(mlxsw_sp);
	if (err) {
		dev_err(mlxsw_sp->bus_info->dev, "Failed to get base mac\n");
		return err;
	}

	err = mlxsw_sp_kvdl_init(mlxsw_sp);
	if (err) {
		dev_err(mlxsw_sp->bus_info->dev, "Failed to initialize KVDL\n");
		return err;
	}

	err = mlxsw_sp_fids_init(mlxsw_sp);
	if (err) {
		dev_err(mlxsw_sp->bus_info->dev, "Failed to initialize FIDs\n");
		goto err_fids_init;
	}

	err = mlxsw_sp_traps_init(mlxsw_sp);
	if (err) {
		dev_err(mlxsw_sp->bus_info->dev, "Failed to set traps\n");
		goto err_traps_init;
	}

	err = mlxsw_sp_devlink_traps_init(mlxsw_sp);
	if (err) {
		dev_err(mlxsw_sp->bus_info->dev, "Failed to initialize devlink traps\n");
		goto err_devlink_traps_init;
	}

	err = mlxsw_sp_buffers_init(mlxsw_sp);
	if (err) {
		dev_err(mlxsw_sp->bus_info->dev, "Failed to initialize buffers\n");
		goto err_buffers_init;
	}

	err = mlxsw_sp_lag_init(mlxsw_sp);
	if (err) {
		dev_err(mlxsw_sp->bus_info->dev, "Failed to initialize LAG\n");
		goto err_lag_init;
	}

	/* Initialize SPAN before router and switchdev, so that those components
	 * can call mlxsw_sp_span_respin().
	 */
	err = mlxsw_sp_span_init(mlxsw_sp);
	if (err) {
		dev_err(mlxsw_sp->bus_info->dev, "Failed to init span system\n");
		goto err_span_init;
	}

	err = mlxsw_sp_switchdev_init(mlxsw_sp);
	if (err) {
		dev_err(mlxsw_sp->bus_info->dev, "Failed to initialize switchdev\n");
		goto err_switchdev_init;
	}

	err = mlxsw_sp_counter_pool_init(mlxsw_sp);
	if (err) {
		dev_err(mlxsw_sp->bus_info->dev, "Failed to init counter pool\n");
		goto err_counter_pool_init;
	}

	err = mlxsw_sp_afa_init(mlxsw_sp);
	if (err) {
		dev_err(mlxsw_sp->bus_info->dev, "Failed to initialize ACL actions\n");
		goto err_afa_init;
	}

	err = mlxsw_sp_nve_init(mlxsw_sp);
	if (err) {
		dev_err(mlxsw_sp->bus_info->dev, "Failed to initialize NVE\n");
		goto err_nve_init;
	}

	err = mlxsw_sp_acl_init(mlxsw_sp);
	if (err) {
		dev_err(mlxsw_sp->bus_info->dev, "Failed to initialize ACL\n");
		goto err_acl_init;
	}

	err = mlxsw_sp_router_init(mlxsw_sp);
	if (err) {
		dev_err(mlxsw_sp->bus_info->dev, "Failed to initialize router\n");
		goto err_router_init;
	}

	if (mlxsw_sp->bus_info->read_frc_capable) {
		/* NULL is a valid return value from clock_init */
		mlxsw_sp->clock =
			mlxsw_sp->ptp_ops->clock_init(mlxsw_sp,
						      mlxsw_sp->bus_info->dev);
		if (IS_ERR(mlxsw_sp->clock)) {
			err = PTR_ERR(mlxsw_sp->clock);
			dev_err(mlxsw_sp->bus_info->dev, "Failed to init ptp clock\n");
			goto err_ptp_clock_init;
		}
	}

	if (mlxsw_sp->clock) {
		/* NULL is a valid return value from ptp_ops->init */
		mlxsw_sp->ptp_state = mlxsw_sp->ptp_ops->init(mlxsw_sp);
		if (IS_ERR(mlxsw_sp->ptp_state)) {
			err = PTR_ERR(mlxsw_sp->ptp_state);
			dev_err(mlxsw_sp->bus_info->dev, "Failed to initialize PTP\n");
			goto err_ptp_init;
		}
	}

	/* Initialize netdevice notifier after router and SPAN is initialized,
	 * so that the event handler can use router structures and call SPAN
	 * respin.
	 */
	mlxsw_sp->netdevice_nb.notifier_call = mlxsw_sp_netdevice_event;
	err = register_netdevice_notifier(&mlxsw_sp->netdevice_nb);
	if (err) {
		dev_err(mlxsw_sp->bus_info->dev, "Failed to register netdev notifier\n");
		goto err_netdev_notifier;
	}

	err = mlxsw_sp_dpipe_init(mlxsw_sp);
	if (err) {
		dev_err(mlxsw_sp->bus_info->dev, "Failed to init pipeline debug\n");
		goto err_dpipe_init;
	}

	err = mlxsw_sp_ports_create(mlxsw_sp);
	if (err) {
		dev_err(mlxsw_sp->bus_info->dev, "Failed to create ports\n");
		goto err_ports_create;
	}

	return 0;

err_ports_create:
	mlxsw_sp_dpipe_fini(mlxsw_sp);
err_dpipe_init:
	unregister_netdevice_notifier(&mlxsw_sp->netdevice_nb);
err_netdev_notifier:
	if (mlxsw_sp->clock)
		mlxsw_sp->ptp_ops->fini(mlxsw_sp->ptp_state);
err_ptp_init:
	if (mlxsw_sp->clock)
		mlxsw_sp->ptp_ops->clock_fini(mlxsw_sp->clock);
err_ptp_clock_init:
	mlxsw_sp_router_fini(mlxsw_sp);
err_router_init:
	mlxsw_sp_acl_fini(mlxsw_sp);
err_acl_init:
	mlxsw_sp_nve_fini(mlxsw_sp);
err_nve_init:
	mlxsw_sp_afa_fini(mlxsw_sp);
err_afa_init:
	mlxsw_sp_counter_pool_fini(mlxsw_sp);
err_counter_pool_init:
	mlxsw_sp_switchdev_fini(mlxsw_sp);
err_switchdev_init:
	mlxsw_sp_span_fini(mlxsw_sp);
err_span_init:
	mlxsw_sp_lag_fini(mlxsw_sp);
err_lag_init:
	mlxsw_sp_buffers_fini(mlxsw_sp);
err_buffers_init:
	mlxsw_sp_devlink_traps_fini(mlxsw_sp);
err_devlink_traps_init:
	mlxsw_sp_traps_fini(mlxsw_sp);
err_traps_init:
	mlxsw_sp_fids_fini(mlxsw_sp);
err_fids_init:
	mlxsw_sp_kvdl_fini(mlxsw_sp);
	return err;
}