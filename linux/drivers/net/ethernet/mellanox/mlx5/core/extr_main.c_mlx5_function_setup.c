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
struct mlx5_core_dev {int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  FW_INIT_TIMEOUT_MILI ; 
 int /*<<< orphan*/  FW_INIT_WARN_MESSAGE_INTERVAL ; 
 int /*<<< orphan*/  FW_PRE_INIT_TIMEOUT_MILI ; 
 int /*<<< orphan*/  fw_rev_maj (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  fw_rev_min (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  fw_rev_sub (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_cmd_cleanup (struct mlx5_core_dev*) ; 
 int mlx5_cmd_init (struct mlx5_core_dev*) ; 
 int mlx5_cmd_init_hca (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_core_disable_hca (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 int mlx5_core_enable_hca (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_core_err (struct mlx5_core_dev*,char*,...) ; 
 int /*<<< orphan*/  mlx5_core_info (struct mlx5_core_dev*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ mlx5_core_is_pf (struct mlx5_core_dev*) ; 
 int mlx5_core_set_issi (struct mlx5_core_dev*) ; 
 int mlx5_query_hca_caps (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_reclaim_startup_pages (struct mlx5_core_dev*) ; 
 int mlx5_satisfy_startup_pages (struct mlx5_core_dev*,int) ; 
 int /*<<< orphan*/  mlx5_set_driver_version (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_start_health_poll (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_stop_health_poll (struct mlx5_core_dev*,int) ; 
 int /*<<< orphan*/  pcie_print_link_status (int /*<<< orphan*/ ) ; 
 int set_hca_cap (struct mlx5_core_dev*) ; 
 int set_hca_ctrl (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  sw_owner_id ; 
 int wait_fw_init (struct mlx5_core_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mlx5_function_setup(struct mlx5_core_dev *dev, bool boot)
{
	int err;

	mlx5_core_info(dev, "firmware version: %d.%d.%d\n", fw_rev_maj(dev),
		       fw_rev_min(dev), fw_rev_sub(dev));

	/* Only PFs hold the relevant PCIe information for this query */
	if (mlx5_core_is_pf(dev))
		pcie_print_link_status(dev->pdev);

	/* wait for firmware to accept initialization segments configurations
	 */
	err = wait_fw_init(dev, FW_PRE_INIT_TIMEOUT_MILI, FW_INIT_WARN_MESSAGE_INTERVAL);
	if (err) {
		mlx5_core_err(dev, "Firmware over %d MS in pre-initializing state, aborting\n",
			      FW_PRE_INIT_TIMEOUT_MILI);
		return err;
	}

	err = mlx5_cmd_init(dev);
	if (err) {
		mlx5_core_err(dev, "Failed initializing command interface, aborting\n");
		return err;
	}

	err = wait_fw_init(dev, FW_INIT_TIMEOUT_MILI, 0);
	if (err) {
		mlx5_core_err(dev, "Firmware over %d MS in initializing state, aborting\n",
			      FW_INIT_TIMEOUT_MILI);
		goto err_cmd_cleanup;
	}

	err = mlx5_core_enable_hca(dev, 0);
	if (err) {
		mlx5_core_err(dev, "enable hca failed\n");
		goto err_cmd_cleanup;
	}

	err = mlx5_core_set_issi(dev);
	if (err) {
		mlx5_core_err(dev, "failed to set issi\n");
		goto err_disable_hca;
	}

	err = mlx5_satisfy_startup_pages(dev, 1);
	if (err) {
		mlx5_core_err(dev, "failed to allocate boot pages\n");
		goto err_disable_hca;
	}

	err = set_hca_ctrl(dev);
	if (err) {
		mlx5_core_err(dev, "set_hca_ctrl failed\n");
		goto reclaim_boot_pages;
	}

	err = set_hca_cap(dev);
	if (err) {
		mlx5_core_err(dev, "set_hca_cap failed\n");
		goto reclaim_boot_pages;
	}

	err = mlx5_satisfy_startup_pages(dev, 0);
	if (err) {
		mlx5_core_err(dev, "failed to allocate init pages\n");
		goto reclaim_boot_pages;
	}

	err = mlx5_cmd_init_hca(dev, sw_owner_id);
	if (err) {
		mlx5_core_err(dev, "init hca failed\n");
		goto reclaim_boot_pages;
	}

	mlx5_set_driver_version(dev);

	mlx5_start_health_poll(dev);

	err = mlx5_query_hca_caps(dev);
	if (err) {
		mlx5_core_err(dev, "query hca failed\n");
		goto stop_health;
	}

	return 0;

stop_health:
	mlx5_stop_health_poll(dev, boot);
reclaim_boot_pages:
	mlx5_reclaim_startup_pages(dev);
err_disable_hca:
	mlx5_core_disable_hca(dev, 0);
err_cmd_cleanup:
	mlx5_cmd_cleanup(dev);

	return err;
}