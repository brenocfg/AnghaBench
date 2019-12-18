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
union devlink_param_value {scalar_t__ vu8; } ;
struct mlxsw_sp {char* fw_filename; TYPE_1__* bus_info; int /*<<< orphan*/  core; struct mlxsw_fw_rev* req_rev; } ;
struct mlxsw_fw_rev {scalar_t__ major; scalar_t__ minor; scalar_t__ subminor; scalar_t__ can_reset_minor; } ;
struct firmware {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; struct mlxsw_fw_rev fw_rev; } ;

/* Variables and functions */
 scalar_t__ DEVLINK_PARAM_FW_LOAD_POLICY_VALUE_FLASH ; 
 int /*<<< orphan*/  DEVLINK_PARAM_GENERIC_ID_FW_LOAD_POLICY ; 
 int EAGAIN ; 
 int EINVAL ; 
 scalar_t__ MLXSW_SP_FWREV_MINOR_TO_BRANCH (scalar_t__) ; 
 int /*<<< orphan*/  WARN (int,char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,char const*,...) ; 
 int devlink_param_driverinit_value_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ,union devlink_param_value*) ; 
 int mlxsw_sp_firmware_flash (struct mlxsw_sp*,struct firmware const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  priv_to_devlink (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int request_firmware_direct (struct firmware const**,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mlxsw_sp_fw_rev_validate(struct mlxsw_sp *mlxsw_sp)
{
	const struct mlxsw_fw_rev *rev = &mlxsw_sp->bus_info->fw_rev;
	const struct mlxsw_fw_rev *req_rev = mlxsw_sp->req_rev;
	const char *fw_filename = mlxsw_sp->fw_filename;
	union devlink_param_value value;
	const struct firmware *firmware;
	int err;

	/* Don't check if driver does not require it */
	if (!req_rev || !fw_filename)
		return 0;

	/* Don't check if devlink 'fw_load_policy' param is 'flash' */
	err = devlink_param_driverinit_value_get(priv_to_devlink(mlxsw_sp->core),
						 DEVLINK_PARAM_GENERIC_ID_FW_LOAD_POLICY,
						 &value);
	if (err)
		return err;
	if (value.vu8 == DEVLINK_PARAM_FW_LOAD_POLICY_VALUE_FLASH)
		return 0;

	/* Validate driver & FW are compatible */
	if (rev->major != req_rev->major) {
		WARN(1, "Mismatch in major FW version [%d:%d] is never expected; Please contact support\n",
		     rev->major, req_rev->major);
		return -EINVAL;
	}
	if (MLXSW_SP_FWREV_MINOR_TO_BRANCH(rev->minor) ==
	    MLXSW_SP_FWREV_MINOR_TO_BRANCH(req_rev->minor) &&
	    (rev->minor > req_rev->minor ||
	     (rev->minor == req_rev->minor &&
	      rev->subminor >= req_rev->subminor)))
		return 0;

	dev_info(mlxsw_sp->bus_info->dev, "The firmware version %d.%d.%d is incompatible with the driver\n",
		 rev->major, rev->minor, rev->subminor);
	dev_info(mlxsw_sp->bus_info->dev, "Flashing firmware using file %s\n",
		 fw_filename);

	err = request_firmware_direct(&firmware, fw_filename,
				      mlxsw_sp->bus_info->dev);
	if (err) {
		dev_err(mlxsw_sp->bus_info->dev, "Could not request firmware file %s\n",
			fw_filename);
		return err;
	}

	err = mlxsw_sp_firmware_flash(mlxsw_sp, firmware, NULL);
	release_firmware(firmware);
	if (err)
		dev_err(mlxsw_sp->bus_info->dev, "Could not upgrade firmware\n");

	/* On FW flash success, tell the caller FW reset is needed
	 * if current FW supports it.
	 */
	if (rev->minor >= req_rev->can_reset_minor)
		return err ? err : -EAGAIN;
	else
		return 0;
}