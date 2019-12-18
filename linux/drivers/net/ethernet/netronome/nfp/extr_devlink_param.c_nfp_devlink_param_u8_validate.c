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
typedef  size_t u32 ;
struct nfp_devlink_param_u8_arg {scalar_t__ max_dl_val; scalar_t__ invalid_dl_val; } ;
struct netlink_ext_ack {int dummy; } ;
struct devlink {int dummy; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (struct nfp_devlink_param_u8_arg*) ; 
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG_MOD (struct netlink_ext_ack*,char*) ; 
 struct nfp_devlink_param_u8_arg* nfp_devlink_u8_args ; 

__attribute__((used)) static int
nfp_devlink_param_u8_validate(struct devlink *devlink, u32 id,
			      union devlink_param_value val,
			      struct netlink_ext_ack *extack)
{
	const struct nfp_devlink_param_u8_arg *arg;

	if (id >= ARRAY_SIZE(nfp_devlink_u8_args))
		return -EOPNOTSUPP;

	arg = &nfp_devlink_u8_args[id];

	if (val.vu8 > arg->max_dl_val) {
		NL_SET_ERR_MSG_MOD(extack, "parameter out of range");
		return -EINVAL;
	}

	if (val.vu8 == arg->invalid_dl_val) {
		NL_SET_ERR_MSG_MOD(extack, "unknown/invalid value specified");
		return -EINVAL;
	}

	return 0;
}