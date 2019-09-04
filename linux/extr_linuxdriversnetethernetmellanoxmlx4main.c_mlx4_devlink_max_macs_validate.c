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
union devlink_param_value {int vu32; } ;
typedef  int u32 ;
struct netlink_ext_ack {int dummy; } ;
struct devlink {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ERANGE ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG_MOD (struct netlink_ext_ack*,char*) ; 
 int /*<<< orphan*/  is_power_of_2 (int) ; 

__attribute__((used)) static int
mlx4_devlink_max_macs_validate(struct devlink *devlink, u32 id,
			       union devlink_param_value val,
			       struct netlink_ext_ack *extack)
{
	u32 value = val.vu32;

	if (value < 1 || value > 128)
		return -ERANGE;

	if (!is_power_of_2(value)) {
		NL_SET_ERR_MSG_MOD(extack, "max_macs supported must be power of 2");
		return -EINVAL;
	}

	return 0;
}