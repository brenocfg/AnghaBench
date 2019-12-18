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
typedef  int /*<<< orphan*/  version_str ;
typedef  scalar_t__ u32 ;
struct netlink_ext_ack {int dummy; } ;
struct mlx5_core_dev {int /*<<< orphan*/  board_id; } ;
struct devlink_info_req {int dummy; } ;
struct devlink {int dummy; } ;

/* Variables and functions */
 int DEVLINK_FW_STRING_LEN ; 
 int /*<<< orphan*/  DRIVER_NAME ; 
 int devlink_info_driver_name_put (struct devlink_info_req*,int /*<<< orphan*/ ) ; 
 int devlink_info_version_fixed_put (struct devlink_info_req*,char*,int /*<<< orphan*/ ) ; 
 int devlink_info_version_running_put (struct devlink_info_req*,char*,char*) ; 
 int devlink_info_version_stored_put (struct devlink_info_req*,char*,char*) ; 
 struct mlx5_core_dev* devlink_priv (struct devlink*) ; 
 int mlx5_fw_ver_major (scalar_t__) ; 
 int mlx5_fw_ver_minor (scalar_t__) ; 
 int mlx5_fw_ver_subminor (scalar_t__) ; 
 int mlx5_fw_version_query (struct mlx5_core_dev*,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,int,int) ; 

__attribute__((used)) static int
mlx5_devlink_info_get(struct devlink *devlink, struct devlink_info_req *req,
		      struct netlink_ext_ack *extack)
{
	struct mlx5_core_dev *dev = devlink_priv(devlink);
	char version_str[DEVLINK_FW_STRING_LEN];
	u32 running_fw, stored_fw;
	int err;

	err = devlink_info_driver_name_put(req, DRIVER_NAME);
	if (err)
		return err;

	err = devlink_info_version_fixed_put(req, "fw.psid", dev->board_id);
	if (err)
		return err;

	err = mlx5_fw_version_query(dev, &running_fw, &stored_fw);
	if (err)
		return err;

	snprintf(version_str, sizeof(version_str), "%d.%d.%04d",
		 mlx5_fw_ver_major(running_fw), mlx5_fw_ver_minor(running_fw),
		 mlx5_fw_ver_subminor(running_fw));
	err = devlink_info_version_running_put(req, "fw.version", version_str);
	if (err)
		return err;

	/* no pending version, return running (stored) version */
	if (stored_fw == 0)
		stored_fw = running_fw;

	snprintf(version_str, sizeof(version_str), "%d.%d.%04d",
		 mlx5_fw_ver_major(stored_fw), mlx5_fw_ver_minor(stored_fw),
		 mlx5_fw_ver_subminor(stored_fw));
	err = devlink_info_version_stored_put(req, "fw.version", version_str);
	if (err)
		return err;

	return 0;
}