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
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct mlx5_priv {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  eswitch; } ;
struct mlx5_core_dev {int /*<<< orphan*/  vxlan; TYPE_1__ priv; int /*<<< orphan*/  tracer; struct pci_dev* pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  mlx5_cleanup_mkey_table (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_cleanup_qp_table (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_cleanup_rl_table (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_cleanup_srq_table (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_cq_debugfs_cleanup (struct mlx5_core_dev*) ; 
 int mlx5_cq_debugfs_init (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_eq_cleanup (struct mlx5_core_dev*) ; 
 int mlx5_eq_init (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_eswitch_cleanup (int /*<<< orphan*/ ) ; 
 int mlx5_eswitch_init (struct mlx5_core_dev*) ; 
 int mlx5_fpga_init (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_fw_tracer_create (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_init_clock (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_init_mkey_table (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_init_qp_table (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_init_reserved_gids (struct mlx5_core_dev*) ; 
 int mlx5_init_rl_table (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_init_srq_table (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_mpfs_cleanup (struct mlx5_core_dev*) ; 
 int mlx5_mpfs_init (struct mlx5_core_dev*) ; 
 int mlx5_query_board_id (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_sriov_cleanup (struct mlx5_core_dev*) ; 
 int mlx5_sriov_init (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_vxlan_create (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_vxlan_destroy (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mlx5_init_once(struct mlx5_core_dev *dev, struct mlx5_priv *priv)
{
	struct pci_dev *pdev = dev->pdev;
	int err;

	err = mlx5_query_board_id(dev);
	if (err) {
		dev_err(&pdev->dev, "query board id failed\n");
		goto out;
	}

	err = mlx5_eq_init(dev);
	if (err) {
		dev_err(&pdev->dev, "failed to initialize eq\n");
		goto out;
	}

	err = mlx5_cq_debugfs_init(dev);
	if (err) {
		dev_err(&pdev->dev, "failed to initialize cq debugfs\n");
		goto err_eq_cleanup;
	}

	mlx5_init_qp_table(dev);

	mlx5_init_srq_table(dev);

	mlx5_init_mkey_table(dev);

	mlx5_init_reserved_gids(dev);

	mlx5_init_clock(dev);

	dev->vxlan = mlx5_vxlan_create(dev);

	err = mlx5_init_rl_table(dev);
	if (err) {
		dev_err(&pdev->dev, "Failed to init rate limiting\n");
		goto err_tables_cleanup;
	}

	err = mlx5_mpfs_init(dev);
	if (err) {
		dev_err(&pdev->dev, "Failed to init l2 table %d\n", err);
		goto err_rl_cleanup;
	}

	err = mlx5_eswitch_init(dev);
	if (err) {
		dev_err(&pdev->dev, "Failed to init eswitch %d\n", err);
		goto err_mpfs_cleanup;
	}

	err = mlx5_sriov_init(dev);
	if (err) {
		dev_err(&pdev->dev, "Failed to init sriov %d\n", err);
		goto err_eswitch_cleanup;
	}

	err = mlx5_fpga_init(dev);
	if (err) {
		dev_err(&pdev->dev, "Failed to init fpga device %d\n", err);
		goto err_sriov_cleanup;
	}

	dev->tracer = mlx5_fw_tracer_create(dev);

	return 0;

err_sriov_cleanup:
	mlx5_sriov_cleanup(dev);
err_eswitch_cleanup:
	mlx5_eswitch_cleanup(dev->priv.eswitch);
err_mpfs_cleanup:
	mlx5_mpfs_cleanup(dev);
err_rl_cleanup:
	mlx5_cleanup_rl_table(dev);
err_tables_cleanup:
	mlx5_vxlan_destroy(dev->vxlan);
	mlx5_cleanup_mkey_table(dev);
	mlx5_cleanup_srq_table(dev);
	mlx5_cleanup_qp_table(dev);
	mlx5_cq_debugfs_cleanup(dev);

err_eq_cleanup:
	mlx5_eq_cleanup(dev);

out:
	return err;
}