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
struct i3c_master_controller {int dummy; } ;
struct i3c_ccc_cmd {int id; int /*<<< orphan*/  err; TYPE_2__* dests; scalar_t__ rnw; } ;
struct cdns_i3c_xfer {int ret; struct cdns_i3c_cmd* cmds; int /*<<< orphan*/  comp; } ;
struct cdns_i3c_master {int dummy; } ;
struct cdns_i3c_cmd {int cmd0; int /*<<< orphan*/  tx_len; int /*<<< orphan*/  tx_buf; int /*<<< orphan*/  rx_len; int /*<<< orphan*/  rx_buf; int /*<<< orphan*/  cmd1; } ;
struct TYPE_3__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct TYPE_4__ {TYPE_1__ payload; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int CMD0_FIFO_DEV_ADDR (int /*<<< orphan*/ ) ; 
 int CMD0_FIFO_IS_CCC ; 
 int CMD0_FIFO_PL_LEN (int /*<<< orphan*/ ) ; 
 int CMD0_FIFO_RNW ; 
 int /*<<< orphan*/  CMD1_FIFO_CCC (int) ; 
 int ENOMEM ; 
 int I3C_CCC_DIRECT ; 
 int /*<<< orphan*/  cdns_i3c_cmd_get_err (struct cdns_i3c_cmd*) ; 
 struct cdns_i3c_xfer* cdns_i3c_master_alloc_xfer (struct cdns_i3c_master*,int) ; 
 int /*<<< orphan*/  cdns_i3c_master_free_xfer (struct cdns_i3c_xfer*) ; 
 int /*<<< orphan*/  cdns_i3c_master_queue_xfer (struct cdns_i3c_master*,struct cdns_i3c_xfer*) ; 
 int /*<<< orphan*/  cdns_i3c_master_unqueue_xfer (struct cdns_i3c_master*,struct cdns_i3c_xfer*) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 struct cdns_i3c_master* to_cdns_i3c_master (struct i3c_master_controller*) ; 
 int /*<<< orphan*/  wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cdns_i3c_master_send_ccc_cmd(struct i3c_master_controller *m,
					struct i3c_ccc_cmd *cmd)
{
	struct cdns_i3c_master *master = to_cdns_i3c_master(m);
	struct cdns_i3c_xfer *xfer;
	struct cdns_i3c_cmd *ccmd;
	int ret;

	xfer = cdns_i3c_master_alloc_xfer(master, 1);
	if (!xfer)
		return -ENOMEM;

	ccmd = xfer->cmds;
	ccmd->cmd1 = CMD1_FIFO_CCC(cmd->id);
	ccmd->cmd0 = CMD0_FIFO_IS_CCC |
		     CMD0_FIFO_PL_LEN(cmd->dests[0].payload.len);

	if (cmd->id & I3C_CCC_DIRECT)
		ccmd->cmd0 |= CMD0_FIFO_DEV_ADDR(cmd->dests[0].addr);

	if (cmd->rnw) {
		ccmd->cmd0 |= CMD0_FIFO_RNW;
		ccmd->rx_buf = cmd->dests[0].payload.data;
		ccmd->rx_len = cmd->dests[0].payload.len;
	} else {
		ccmd->tx_buf = cmd->dests[0].payload.data;
		ccmd->tx_len = cmd->dests[0].payload.len;
	}

	cdns_i3c_master_queue_xfer(master, xfer);
	if (!wait_for_completion_timeout(&xfer->comp, msecs_to_jiffies(1000)))
		cdns_i3c_master_unqueue_xfer(master, xfer);

	ret = xfer->ret;
	cmd->err = cdns_i3c_cmd_get_err(&xfer->cmds[0]);
	cdns_i3c_master_free_xfer(xfer);

	return ret;
}