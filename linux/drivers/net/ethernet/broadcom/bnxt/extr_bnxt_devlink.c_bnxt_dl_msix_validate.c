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
typedef  scalar_t__ u32 ;
struct netlink_ext_ack {int dummy; } ;
struct devlink {int dummy; } ;

/* Variables and functions */
 int BNXT_MSIX_VEC_MAX ; 
 int BNXT_MSIX_VEC_MIN_MAX ; 
 scalar_t__ DEVLINK_PARAM_GENERIC_ID_MSIX_VEC_PER_PF_MAX ; 
 scalar_t__ DEVLINK_PARAM_GENERIC_ID_MSIX_VEC_PER_PF_MIN ; 
 int EINVAL ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG_MOD (struct netlink_ext_ack*,char*) ; 

__attribute__((used)) static int bnxt_dl_msix_validate(struct devlink *dl, u32 id,
				 union devlink_param_value val,
				 struct netlink_ext_ack *extack)
{
	int max_val = -1;

	if (id == DEVLINK_PARAM_GENERIC_ID_MSIX_VEC_PER_PF_MAX)
		max_val = BNXT_MSIX_VEC_MAX;

	if (id == DEVLINK_PARAM_GENERIC_ID_MSIX_VEC_PER_PF_MIN)
		max_val = BNXT_MSIX_VEC_MIN_MAX;

	if (val.vu32 > max_val) {
		NL_SET_ERR_MSG_MOD(extack, "MSIX value is exceeding the range");
		return -EINVAL;
	}

	return 0;
}