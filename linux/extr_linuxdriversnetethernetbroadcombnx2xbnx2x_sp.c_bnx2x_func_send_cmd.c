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
struct bnx2x_func_state_params {int cmd; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_ERR (char*,int) ; 
#define  BNX2X_F_CMD_AFEX_UPDATE 137 
#define  BNX2X_F_CMD_AFEX_VIFLISTS 136 
#define  BNX2X_F_CMD_HW_INIT 135 
#define  BNX2X_F_CMD_HW_RESET 134 
#define  BNX2X_F_CMD_SET_TIMESYNC 133 
#define  BNX2X_F_CMD_START 132 
#define  BNX2X_F_CMD_STOP 131 
#define  BNX2X_F_CMD_SWITCH_UPDATE 130 
#define  BNX2X_F_CMD_TX_START 129 
#define  BNX2X_F_CMD_TX_STOP 128 
 int EINVAL ; 
 int bnx2x_func_hw_init (struct bnx2x*,struct bnx2x_func_state_params*) ; 
 int bnx2x_func_hw_reset (struct bnx2x*,struct bnx2x_func_state_params*) ; 
 int bnx2x_func_send_afex_update (struct bnx2x*,struct bnx2x_func_state_params*) ; 
 int bnx2x_func_send_afex_viflists (struct bnx2x*,struct bnx2x_func_state_params*) ; 
 int bnx2x_func_send_set_timesync (struct bnx2x*,struct bnx2x_func_state_params*) ; 
 int bnx2x_func_send_start (struct bnx2x*,struct bnx2x_func_state_params*) ; 
 int bnx2x_func_send_stop (struct bnx2x*,struct bnx2x_func_state_params*) ; 
 int bnx2x_func_send_switch_update (struct bnx2x*,struct bnx2x_func_state_params*) ; 
 int bnx2x_func_send_tx_start (struct bnx2x*,struct bnx2x_func_state_params*) ; 
 int bnx2x_func_send_tx_stop (struct bnx2x*,struct bnx2x_func_state_params*) ; 

__attribute__((used)) static int bnx2x_func_send_cmd(struct bnx2x *bp,
			       struct bnx2x_func_state_params *params)
{
	switch (params->cmd) {
	case BNX2X_F_CMD_HW_INIT:
		return bnx2x_func_hw_init(bp, params);
	case BNX2X_F_CMD_START:
		return bnx2x_func_send_start(bp, params);
	case BNX2X_F_CMD_STOP:
		return bnx2x_func_send_stop(bp, params);
	case BNX2X_F_CMD_HW_RESET:
		return bnx2x_func_hw_reset(bp, params);
	case BNX2X_F_CMD_AFEX_UPDATE:
		return bnx2x_func_send_afex_update(bp, params);
	case BNX2X_F_CMD_AFEX_VIFLISTS:
		return bnx2x_func_send_afex_viflists(bp, params);
	case BNX2X_F_CMD_TX_STOP:
		return bnx2x_func_send_tx_stop(bp, params);
	case BNX2X_F_CMD_TX_START:
		return bnx2x_func_send_tx_start(bp, params);
	case BNX2X_F_CMD_SWITCH_UPDATE:
		return bnx2x_func_send_switch_update(bp, params);
	case BNX2X_F_CMD_SET_TIMESYNC:
		return bnx2x_func_send_set_timesync(bp, params);
	default:
		BNX2X_ERR("Unknown command: %d\n", params->cmd);
		return -EINVAL;
	}
}