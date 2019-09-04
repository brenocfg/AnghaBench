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
struct bnx2x_queue_state_params {int cmd; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_ERR (char*,int) ; 
#define  BNX2X_Q_CMD_ACTIVATE 138 
#define  BNX2X_Q_CMD_CFC_DEL 137 
#define  BNX2X_Q_CMD_DEACTIVATE 136 
#define  BNX2X_Q_CMD_EMPTY 135 
#define  BNX2X_Q_CMD_HALT 134 
#define  BNX2X_Q_CMD_INIT 133 
#define  BNX2X_Q_CMD_SETUP 132 
#define  BNX2X_Q_CMD_SETUP_TX_ONLY 131 
#define  BNX2X_Q_CMD_TERMINATE 130 
#define  BNX2X_Q_CMD_UPDATE 129 
#define  BNX2X_Q_CMD_UPDATE_TPA 128 
 int EINVAL ; 
 int bnx2x_q_send_setup_e2 (struct bnx2x*,struct bnx2x_queue_state_params*) ; 
 int bnx2x_queue_send_cmd_cmn (struct bnx2x*,struct bnx2x_queue_state_params*) ; 

__attribute__((used)) static int bnx2x_queue_send_cmd_e2(struct bnx2x *bp,
				   struct bnx2x_queue_state_params *params)
{
	switch (params->cmd) {
	case BNX2X_Q_CMD_SETUP:
		return bnx2x_q_send_setup_e2(bp, params);
	case BNX2X_Q_CMD_INIT:
	case BNX2X_Q_CMD_SETUP_TX_ONLY:
	case BNX2X_Q_CMD_DEACTIVATE:
	case BNX2X_Q_CMD_ACTIVATE:
	case BNX2X_Q_CMD_UPDATE:
	case BNX2X_Q_CMD_UPDATE_TPA:
	case BNX2X_Q_CMD_HALT:
	case BNX2X_Q_CMD_CFC_DEL:
	case BNX2X_Q_CMD_TERMINATE:
	case BNX2X_Q_CMD_EMPTY:
		return bnx2x_queue_send_cmd_cmn(bp, params);
	default:
		BNX2X_ERR("Unknown command: %d\n", params->cmd);
		return -EINVAL;
	}
}