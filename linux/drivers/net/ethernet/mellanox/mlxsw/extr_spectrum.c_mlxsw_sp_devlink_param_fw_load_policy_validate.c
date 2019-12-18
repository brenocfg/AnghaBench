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
union devlink_param_value {scalar_t__ vu8; } ;
typedef  int /*<<< orphan*/  u32 ;
struct netlink_ext_ack {int dummy; } ;
struct devlink {int dummy; } ;

/* Variables and functions */
 scalar_t__ DEVLINK_PARAM_FW_LOAD_POLICY_VALUE_DRIVER ; 
 scalar_t__ DEVLINK_PARAM_FW_LOAD_POLICY_VALUE_FLASH ; 
 int EINVAL ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG_MOD (struct netlink_ext_ack*,char*) ; 

__attribute__((used)) static int
mlxsw_sp_devlink_param_fw_load_policy_validate(struct devlink *devlink, u32 id,
					       union devlink_param_value val,
					       struct netlink_ext_ack *extack)
{
	if ((val.vu8 != DEVLINK_PARAM_FW_LOAD_POLICY_VALUE_DRIVER) &&
	    (val.vu8 != DEVLINK_PARAM_FW_LOAD_POLICY_VALUE_FLASH)) {
		NL_SET_ERR_MSG_MOD(extack, "'fw_load_policy' must be 'driver' or 'flash'");
		return -EINVAL;
	}

	return 0;
}