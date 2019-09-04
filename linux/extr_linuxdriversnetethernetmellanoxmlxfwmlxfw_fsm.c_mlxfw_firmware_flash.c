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
typedef  int /*<<< orphan*/  u32 ;
struct mlxfw_mfa2_file {int dummy; } ;
struct mlxfw_dev {TYPE_1__* ops; } ;
struct firmware {int dummy; } ;
struct TYPE_2__ {int (* fsm_lock ) (struct mlxfw_dev*,int /*<<< orphan*/ *) ;int (* fsm_activate ) (struct mlxfw_dev*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* fsm_release ) (struct mlxfw_dev*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (struct mlxfw_mfa2_file*) ; 
 int /*<<< orphan*/  MLXFW_FSM_STATE_LOCKED ; 
 int PTR_ERR (struct mlxfw_mfa2_file*) ; 
 int mlxfw_flash_components (struct mlxfw_dev*,int /*<<< orphan*/ ,struct mlxfw_mfa2_file*) ; 
 int mlxfw_fsm_state_wait (struct mlxfw_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxfw_mfa2_check (struct firmware const*) ; 
 int /*<<< orphan*/  mlxfw_mfa2_file_fini (struct mlxfw_mfa2_file*) ; 
 struct mlxfw_mfa2_file* mlxfw_mfa2_file_init (struct firmware const*) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int stub1 (struct mlxfw_dev*,int /*<<< orphan*/ *) ; 
 int stub2 (struct mlxfw_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (struct mlxfw_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (struct mlxfw_dev*,int /*<<< orphan*/ ) ; 

int mlxfw_firmware_flash(struct mlxfw_dev *mlxfw_dev,
			 const struct firmware *firmware)
{
	struct mlxfw_mfa2_file *mfa2_file;
	u32 fwhandle;
	int err;

	if (!mlxfw_mfa2_check(firmware)) {
		pr_err("Firmware file is not MFA2\n");
		return -EINVAL;
	}

	mfa2_file = mlxfw_mfa2_file_init(firmware);
	if (IS_ERR(mfa2_file))
		return PTR_ERR(mfa2_file);

	pr_info("Initialize firmware flash process\n");
	err = mlxfw_dev->ops->fsm_lock(mlxfw_dev, &fwhandle);
	if (err) {
		pr_err("Could not lock the firmware FSM\n");
		goto err_fsm_lock;
	}

	err = mlxfw_fsm_state_wait(mlxfw_dev, fwhandle,
				   MLXFW_FSM_STATE_LOCKED);
	if (err)
		goto err_state_wait_idle_to_locked;

	err = mlxfw_flash_components(mlxfw_dev, fwhandle, mfa2_file);
	if (err)
		goto err_flash_components;

	pr_debug("Activate image\n");
	err = mlxfw_dev->ops->fsm_activate(mlxfw_dev, fwhandle);
	if (err) {
		pr_err("Could not activate the downloaded image\n");
		goto err_fsm_activate;
	}

	err = mlxfw_fsm_state_wait(mlxfw_dev, fwhandle, MLXFW_FSM_STATE_LOCKED);
	if (err)
		goto err_state_wait_activate_to_locked;

	pr_debug("Handle release\n");
	mlxfw_dev->ops->fsm_release(mlxfw_dev, fwhandle);

	pr_info("Firmware flash done.\n");
	mlxfw_mfa2_file_fini(mfa2_file);
	return 0;

err_state_wait_activate_to_locked:
err_fsm_activate:
err_flash_components:
err_state_wait_idle_to_locked:
	mlxfw_dev->ops->fsm_release(mlxfw_dev, fwhandle);
err_fsm_lock:
	mlxfw_mfa2_file_fini(mfa2_file);
	return err;
}