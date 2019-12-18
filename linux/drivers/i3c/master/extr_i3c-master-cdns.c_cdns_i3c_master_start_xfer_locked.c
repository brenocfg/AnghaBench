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
struct cdns_i3c_xfer {unsigned int ncmds; struct cdns_i3c_cmd* cmds; } ;
struct TYPE_2__ {struct cdns_i3c_xfer* cur; } ;
struct cdns_i3c_master {scalar_t__ regs; TYPE_1__ xferqueue; } ;
struct cdns_i3c_cmd {int cmd1; int cmd0; int /*<<< orphan*/  tx_len; int /*<<< orphan*/  tx_buf; } ;

/* Variables and functions */
 scalar_t__ CMD0_FIFO ; 
 scalar_t__ CMD1_FIFO ; 
 int CMD1_FIFO_CMDID (unsigned int) ; 
 scalar_t__ CTRL ; 
 int CTRL_MCS ; 
 scalar_t__ MST_ICR ; 
 scalar_t__ MST_IER ; 
 int MST_INT_CMDD_EMP ; 
 int /*<<< orphan*/  cdns_i3c_master_wr_to_tx_fifo (struct cdns_i3c_master*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void cdns_i3c_master_start_xfer_locked(struct cdns_i3c_master *master)
{
	struct cdns_i3c_xfer *xfer = master->xferqueue.cur;
	unsigned int i;

	if (!xfer)
		return;

	writel(MST_INT_CMDD_EMP, master->regs + MST_ICR);
	for (i = 0; i < xfer->ncmds; i++) {
		struct cdns_i3c_cmd *cmd = &xfer->cmds[i];

		cdns_i3c_master_wr_to_tx_fifo(master, cmd->tx_buf,
					      cmd->tx_len);
	}

	for (i = 0; i < xfer->ncmds; i++) {
		struct cdns_i3c_cmd *cmd = &xfer->cmds[i];

		writel(cmd->cmd1 | CMD1_FIFO_CMDID(i),
		       master->regs + CMD1_FIFO);
		writel(cmd->cmd0, master->regs + CMD0_FIFO);
	}

	writel(readl(master->regs + CTRL) | CTRL_MCS,
	       master->regs + CTRL);
	writel(MST_INT_CMDD_EMP, master->regs + MST_IER);
}