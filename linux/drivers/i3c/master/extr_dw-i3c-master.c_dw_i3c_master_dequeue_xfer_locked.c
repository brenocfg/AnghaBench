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
struct dw_i3c_xfer {int /*<<< orphan*/  node; } ;
struct TYPE_2__ {struct dw_i3c_xfer* cur; } ;
struct dw_i3c_master {scalar_t__ regs; TYPE_1__ xferqueue; } ;

/* Variables and functions */
 scalar_t__ RESET_CTRL ; 
 int RESET_CTRL_CMD_QUEUE ; 
 int RESET_CTRL_RESP_QUEUE ; 
 int RESET_CTRL_RX_FIFO ; 
 int RESET_CTRL_TX_FIFO ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  readl_poll_timeout_atomic (scalar_t__,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void dw_i3c_master_dequeue_xfer_locked(struct dw_i3c_master *master,
					      struct dw_i3c_xfer *xfer)
{
	if (master->xferqueue.cur == xfer) {
		u32 status;

		master->xferqueue.cur = NULL;

		writel(RESET_CTRL_RX_FIFO | RESET_CTRL_TX_FIFO |
		       RESET_CTRL_RESP_QUEUE | RESET_CTRL_CMD_QUEUE,
		       master->regs + RESET_CTRL);

		readl_poll_timeout_atomic(master->regs + RESET_CTRL, status,
					  !status, 10, 1000000);
	} else {
		list_del_init(&xfer->node);
	}
}