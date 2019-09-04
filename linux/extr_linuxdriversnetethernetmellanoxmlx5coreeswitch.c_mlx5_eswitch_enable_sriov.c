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
struct mlx5_eswitch {int mode; int /*<<< orphan*/  dev; int /*<<< orphan*/  enabled_vports; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  ESW_ALLOWED (struct mlx5_eswitch*) ; 
 int /*<<< orphan*/  MLX5_CAP_ESW_EGRESS_ACL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_CAP_ESW_FLOWTABLE_FDB (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_CAP_ESW_INGRESS_ACL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_INTERFACE_PROTOCOL_IB ; 
 int SRIOV_LEGACY ; 
 int SRIOV_NONE ; 
 int SRIOV_OFFLOADS ; 
 int SRIOV_VPORT_EVENTS ; 
 int esw_create_legacy_fdb_table (struct mlx5_eswitch*) ; 
 int esw_create_tsar (struct mlx5_eswitch*) ; 
 int /*<<< orphan*/  esw_enable_vport (struct mlx5_eswitch*,int,int) ; 
 int /*<<< orphan*/  esw_info (int /*<<< orphan*/ ,char*,int,...) ; 
 int esw_offloads_init (struct mlx5_eswitch*,int) ; 
 int /*<<< orphan*/  esw_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ft_support ; 
 int /*<<< orphan*/  mlx5_reload_interface (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int mlx5_eswitch_enable_sriov(struct mlx5_eswitch *esw, int nvfs, int mode)
{
	int err;
	int i, enabled_events;

	if (!ESW_ALLOWED(esw) ||
	    !MLX5_CAP_ESW_FLOWTABLE_FDB(esw->dev, ft_support)) {
		esw_warn(esw->dev, "E-Switch FDB is not supported, aborting ...\n");
		return -EOPNOTSUPP;
	}

	if (!MLX5_CAP_ESW_INGRESS_ACL(esw->dev, ft_support))
		esw_warn(esw->dev, "E-Switch ingress ACL is not supported by FW\n");

	if (!MLX5_CAP_ESW_EGRESS_ACL(esw->dev, ft_support))
		esw_warn(esw->dev, "E-Switch engress ACL is not supported by FW\n");

	esw_info(esw->dev, "E-Switch enable SRIOV: nvfs(%d) mode (%d)\n", nvfs, mode);
	esw->mode = mode;

	if (mode == SRIOV_LEGACY) {
		err = esw_create_legacy_fdb_table(esw);
	} else {
		mlx5_reload_interface(esw->dev, MLX5_INTERFACE_PROTOCOL_IB);

		err = esw_offloads_init(esw, nvfs + 1);
	}

	if (err)
		goto abort;

	err = esw_create_tsar(esw);
	if (err)
		esw_warn(esw->dev, "Failed to create eswitch TSAR");

	/* Don't enable vport events when in SRIOV_OFFLOADS mode, since:
	 * 1. L2 table (MPFS) is programmed by PF/VF representors netdevs set_rx_mode
	 * 2. FDB/Eswitch is programmed by user space tools
	 */
	enabled_events = (mode == SRIOV_LEGACY) ? SRIOV_VPORT_EVENTS : 0;
	for (i = 0; i <= nvfs; i++)
		esw_enable_vport(esw, i, enabled_events);

	esw_info(esw->dev, "SRIOV enabled: active vports(%d)\n",
		 esw->enabled_vports);
	return 0;

abort:
	esw->mode = SRIOV_NONE;

	if (mode == SRIOV_OFFLOADS)
		mlx5_reload_interface(esw->dev, MLX5_INTERFACE_PROTOCOL_IB);

	return err;
}