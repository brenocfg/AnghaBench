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
struct netlink_ext_ack {int dummy; } ;
struct mlxfw_dev {TYPE_1__* ops; } ;
typedef  enum mlxfw_fsm_state_err { ____Placeholder_mlxfw_fsm_state_err } mlxfw_fsm_state_err ;
typedef  enum mlxfw_fsm_state { ____Placeholder_mlxfw_fsm_state } mlxfw_fsm_state ;
struct TYPE_2__ {int (* fsm_query_state ) (struct mlxfw_dev*,int /*<<< orphan*/ ,int*,int*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int ETIMEDOUT ; 
 int MLXFW_FSM_STATE_ERR_OK ; 
 int /*<<< orphan*/  MLXFW_FSM_STATE_WAIT_CYCLE_MS ; 
 int MLXFW_FSM_STATE_WAIT_ROUNDS ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG_MOD (struct netlink_ext_ack*,char*) ; 
 int /*<<< orphan*/ * mlxfw_fsm_state_err_str ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int stub1 (struct mlxfw_dev*,int /*<<< orphan*/ ,int*,int*) ; 

__attribute__((used)) static int mlxfw_fsm_state_wait(struct mlxfw_dev *mlxfw_dev, u32 fwhandle,
				enum mlxfw_fsm_state fsm_state,
				struct netlink_ext_ack *extack)
{
	enum mlxfw_fsm_state_err fsm_state_err;
	enum mlxfw_fsm_state curr_fsm_state;
	int times;
	int err;

	times = MLXFW_FSM_STATE_WAIT_ROUNDS;
retry:
	err = mlxfw_dev->ops->fsm_query_state(mlxfw_dev, fwhandle,
					      &curr_fsm_state, &fsm_state_err);
	if (err)
		return err;

	if (fsm_state_err != MLXFW_FSM_STATE_ERR_OK) {
		pr_err("Firmware flash failed: %s\n",
		       mlxfw_fsm_state_err_str[fsm_state_err]);
		NL_SET_ERR_MSG_MOD(extack, "Firmware flash failed");
		return -EINVAL;
	}
	if (curr_fsm_state != fsm_state) {
		if (--times == 0) {
			pr_err("Timeout reached on FSM state change");
			NL_SET_ERR_MSG_MOD(extack, "Timeout reached on FSM state change");
			return -ETIMEDOUT;
		}
		msleep(MLXFW_FSM_STATE_WAIT_CYCLE_MS);
		goto retry;
	}
	return 0;
}