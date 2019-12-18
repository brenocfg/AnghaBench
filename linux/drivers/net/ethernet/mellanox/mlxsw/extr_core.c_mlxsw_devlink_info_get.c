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
typedef  int u32 ;
struct netlink_ext_ack {int dummy; } ;
struct mlxsw_core {TYPE_1__* bus_info; } ;
struct devlink_info_req {int dummy; } ;
struct devlink {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  device_kind; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_REG (int /*<<< orphan*/ ) ; 
 int MLXSW_REG_MGIR_FW_INFO_PSID_SIZE ; 
 int MLXSW_REG_MGIR_LEN ; 
 int devlink_info_driver_name_put (struct devlink_info_req*,int /*<<< orphan*/ ) ; 
 int devlink_info_version_fixed_put (struct devlink_info_req*,char*,char*) ; 
 int devlink_info_version_running_put (struct devlink_info_req*,char*,char*) ; 
 struct mlxsw_core* devlink_priv (struct devlink*) ; 
 int /*<<< orphan*/  mgir ; 
 int /*<<< orphan*/  mlxsw_reg_mgir_pack (char*) ; 
 int /*<<< orphan*/  mlxsw_reg_mgir_unpack (char*,int*,char*,int*,int*,int*) ; 
 int mlxsw_reg_query (struct mlxsw_core*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,...) ; 

__attribute__((used)) static int
mlxsw_devlink_info_get(struct devlink *devlink, struct devlink_info_req *req,
		       struct netlink_ext_ack *extack)
{
	struct mlxsw_core *mlxsw_core = devlink_priv(devlink);
	char fw_info_psid[MLXSW_REG_MGIR_FW_INFO_PSID_SIZE];
	u32 hw_rev, fw_major, fw_minor, fw_sub_minor;
	char mgir_pl[MLXSW_REG_MGIR_LEN];
	char buf[32];
	int err;

	err = devlink_info_driver_name_put(req,
					   mlxsw_core->bus_info->device_kind);
	if (err)
		return err;

	mlxsw_reg_mgir_pack(mgir_pl);
	err = mlxsw_reg_query(mlxsw_core, MLXSW_REG(mgir), mgir_pl);
	if (err)
		return err;
	mlxsw_reg_mgir_unpack(mgir_pl, &hw_rev, fw_info_psid, &fw_major,
			      &fw_minor, &fw_sub_minor);

	sprintf(buf, "%X", hw_rev);
	err = devlink_info_version_fixed_put(req, "hw.revision", buf);
	if (err)
		return err;

	err = devlink_info_version_fixed_put(req, "fw.psid", fw_info_psid);
	if (err)
		return err;

	sprintf(buf, "%d.%d.%d", fw_major, fw_minor, fw_sub_minor);
	err = devlink_info_version_running_put(req, "fw.version", buf);
	if (err)
		return err;

	return 0;
}