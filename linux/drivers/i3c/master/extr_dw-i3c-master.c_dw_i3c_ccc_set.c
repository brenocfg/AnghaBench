#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct i3c_ccc_cmd {int id; int /*<<< orphan*/  err; TYPE_2__* dests; } ;
struct dw_i3c_xfer {int ret; struct dw_i3c_cmd* cmds; int /*<<< orphan*/  comp; } ;
struct dw_i3c_master {int dummy; } ;
struct dw_i3c_cmd {int cmd_hi; int cmd_lo; scalar_t__ error; int /*<<< orphan*/  tx_len; int /*<<< orphan*/  tx_buf; } ;
struct TYPE_3__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct TYPE_4__ {TYPE_1__ payload; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int COMMAND_PORT_ARG_DATA_LEN (int /*<<< orphan*/ ) ; 
 int COMMAND_PORT_CMD (int) ; 
 int COMMAND_PORT_CP ; 
 int COMMAND_PORT_DEV_INDEX (int) ; 
 int COMMAND_PORT_ROC ; 
 int COMMAND_PORT_TOC ; 
 int COMMAND_PORT_TRANSFER_ARG ; 
 int ENOMEM ; 
 int I3C_CCC_DIRECT ; 
 int /*<<< orphan*/  I3C_ERROR_M2 ; 
 scalar_t__ RESPONSE_ERROR_IBA_NACK ; 
 int /*<<< orphan*/  XFER_TIMEOUT ; 
 struct dw_i3c_xfer* dw_i3c_master_alloc_xfer (struct dw_i3c_master*,int) ; 
 int /*<<< orphan*/  dw_i3c_master_dequeue_xfer (struct dw_i3c_master*,struct dw_i3c_xfer*) ; 
 int /*<<< orphan*/  dw_i3c_master_enqueue_xfer (struct dw_i3c_master*,struct dw_i3c_xfer*) ; 
 int /*<<< orphan*/  dw_i3c_master_free_xfer (struct dw_i3c_xfer*) ; 
 int dw_i3c_master_get_addr_pos (struct dw_i3c_master*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dw_i3c_ccc_set(struct dw_i3c_master *master,
			  struct i3c_ccc_cmd *ccc)
{
	struct dw_i3c_xfer *xfer;
	struct dw_i3c_cmd *cmd;
	int ret, pos = 0;

	if (ccc->id & I3C_CCC_DIRECT) {
		pos = dw_i3c_master_get_addr_pos(master, ccc->dests[0].addr);
		if (pos < 0)
			return pos;
	}

	xfer = dw_i3c_master_alloc_xfer(master, 1);
	if (!xfer)
		return -ENOMEM;

	cmd = xfer->cmds;
	cmd->tx_buf = ccc->dests[0].payload.data;
	cmd->tx_len = ccc->dests[0].payload.len;

	cmd->cmd_hi = COMMAND_PORT_ARG_DATA_LEN(ccc->dests[0].payload.len) |
		      COMMAND_PORT_TRANSFER_ARG;

	cmd->cmd_lo = COMMAND_PORT_CP |
		      COMMAND_PORT_DEV_INDEX(pos) |
		      COMMAND_PORT_CMD(ccc->id) |
		      COMMAND_PORT_TOC |
		      COMMAND_PORT_ROC;

	dw_i3c_master_enqueue_xfer(master, xfer);
	if (!wait_for_completion_timeout(&xfer->comp, XFER_TIMEOUT))
		dw_i3c_master_dequeue_xfer(master, xfer);

	ret = xfer->ret;
	if (xfer->cmds[0].error == RESPONSE_ERROR_IBA_NACK)
		ccc->err = I3C_ERROR_M2;

	dw_i3c_master_free_xfer(xfer);

	return ret;
}