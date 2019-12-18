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
struct TYPE_2__ {int devcom; int /*<<< orphan*/  eswitch; } ;
struct mlx5_core_dev {int dm; TYPE_1__ priv; int /*<<< orphan*/  vxlan; int /*<<< orphan*/  geneve; int /*<<< orphan*/  hv_vhca; int /*<<< orphan*/  tracer; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int) ; 
 int /*<<< orphan*/  mlx5_cleanup_mkey_table (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_cleanup_qp_table (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_cleanup_rl_table (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_core_err (struct mlx5_core_dev*,char*,...) ; 
 int /*<<< orphan*/  mlx5_core_warn (struct mlx5_core_dev*,char*,int) ; 
 int /*<<< orphan*/  mlx5_cq_debugfs_cleanup (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_cq_debugfs_init (struct mlx5_core_dev*) ; 
 int mlx5_devcom_register_device (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_devcom_unregister_device (int) ; 
 int mlx5_dm_create (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_eq_table_cleanup (struct mlx5_core_dev*) ; 
 int mlx5_eq_table_init (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_eswitch_cleanup (int /*<<< orphan*/ ) ; 
 int mlx5_eswitch_init (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_events_cleanup (struct mlx5_core_dev*) ; 
 int mlx5_events_init (struct mlx5_core_dev*) ; 
 int mlx5_fpga_init (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_fw_tracer_create (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_geneve_create (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_geneve_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_hv_vhca_create (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_init_clock (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_init_mkey_table (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_init_qp_table (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_init_reserved_gids (struct mlx5_core_dev*) ; 
 int mlx5_init_rl_table (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_irq_table_cleanup (struct mlx5_core_dev*) ; 
 int mlx5_irq_table_init (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_mpfs_cleanup (struct mlx5_core_dev*) ; 
 int mlx5_mpfs_init (struct mlx5_core_dev*) ; 
 int mlx5_query_board_id (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_sriov_cleanup (struct mlx5_core_dev*) ; 
 int mlx5_sriov_init (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_vxlan_create (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_vxlan_destroy (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mlx5_init_once(struct mlx5_core_dev *dev)
{
	int err;

	dev->priv.devcom = mlx5_devcom_register_device(dev);
	if (IS_ERR(dev->priv.devcom))
		mlx5_core_err(dev, "failed to register with devcom (0x%p)\n",
			      dev->priv.devcom);

	err = mlx5_query_board_id(dev);
	if (err) {
		mlx5_core_err(dev, "query board id failed\n");
		goto err_devcom;
	}

	err = mlx5_irq_table_init(dev);
	if (err) {
		mlx5_core_err(dev, "failed to initialize irq table\n");
		goto err_devcom;
	}

	err = mlx5_eq_table_init(dev);
	if (err) {
		mlx5_core_err(dev, "failed to initialize eq\n");
		goto err_irq_cleanup;
	}

	err = mlx5_events_init(dev);
	if (err) {
		mlx5_core_err(dev, "failed to initialize events\n");
		goto err_eq_cleanup;
	}

	mlx5_cq_debugfs_init(dev);

	mlx5_init_qp_table(dev);

	mlx5_init_mkey_table(dev);

	mlx5_init_reserved_gids(dev);

	mlx5_init_clock(dev);

	dev->vxlan = mlx5_vxlan_create(dev);
	dev->geneve = mlx5_geneve_create(dev);

	err = mlx5_init_rl_table(dev);
	if (err) {
		mlx5_core_err(dev, "Failed to init rate limiting\n");
		goto err_tables_cleanup;
	}

	err = mlx5_mpfs_init(dev);
	if (err) {
		mlx5_core_err(dev, "Failed to init l2 table %d\n", err);
		goto err_rl_cleanup;
	}

	err = mlx5_sriov_init(dev);
	if (err) {
		mlx5_core_err(dev, "Failed to init sriov %d\n", err);
		goto err_mpfs_cleanup;
	}

	err = mlx5_eswitch_init(dev);
	if (err) {
		mlx5_core_err(dev, "Failed to init eswitch %d\n", err);
		goto err_sriov_cleanup;
	}

	err = mlx5_fpga_init(dev);
	if (err) {
		mlx5_core_err(dev, "Failed to init fpga device %d\n", err);
		goto err_eswitch_cleanup;
	}

	dev->dm = mlx5_dm_create(dev);
	if (IS_ERR(dev->dm))
		mlx5_core_warn(dev, "Failed to init device memory%d\n", err);

	dev->tracer = mlx5_fw_tracer_create(dev);
	dev->hv_vhca = mlx5_hv_vhca_create(dev);

	return 0;

err_eswitch_cleanup:
	mlx5_eswitch_cleanup(dev->priv.eswitch);
err_sriov_cleanup:
	mlx5_sriov_cleanup(dev);
err_mpfs_cleanup:
	mlx5_mpfs_cleanup(dev);
err_rl_cleanup:
	mlx5_cleanup_rl_table(dev);
err_tables_cleanup:
	mlx5_geneve_destroy(dev->geneve);
	mlx5_vxlan_destroy(dev->vxlan);
	mlx5_cleanup_mkey_table(dev);
	mlx5_cleanup_qp_table(dev);
	mlx5_cq_debugfs_cleanup(dev);
	mlx5_events_cleanup(dev);
err_eq_cleanup:
	mlx5_eq_table_cleanup(dev);
err_irq_cleanup:
	mlx5_irq_table_cleanup(dev);
err_devcom:
	mlx5_devcom_unregister_device(dev->priv.devcom);

	return err;
}