#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_6__ {int /*<<< orphan*/  out; int /*<<< orphan*/  in; } ;
struct i3c_priv_xfer {scalar_t__ len; int /*<<< orphan*/  err; TYPE_3__ data; scalar_t__ rnw; } ;
struct i3c_master_controller {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  dyn_addr; } ;
struct i3c_dev_desc {TYPE_2__ info; } ;
struct cdns_i3c_xfer {int ret; struct cdns_i3c_cmd* cmds; int /*<<< orphan*/  comp; } ;
struct TYPE_4__ {int cmdfifodepth; int cmdrfifodepth; int rxfifodepth; int txfifodepth; } ;
struct cdns_i3c_master {TYPE_1__ caps; } ;
struct cdns_i3c_cmd {int cmd0; scalar_t__ rx_len; scalar_t__ tx_len; int /*<<< orphan*/  tx_buf; int /*<<< orphan*/  rx_buf; } ;

/* Variables and functions */
 int CMD0_FIFO_BCH ; 
 int CMD0_FIFO_DEV_ADDR (int /*<<< orphan*/ ) ; 
 int CMD0_FIFO_PL_LEN (scalar_t__) ; 
 scalar_t__ CMD0_FIFO_PL_LEN_MAX ; 
 int CMD0_FIFO_PRIV_XMIT_MODE (int /*<<< orphan*/ ) ; 
 int CMD0_FIFO_RNW ; 
 int CMD0_FIFO_RSBC ; 
 scalar_t__ DIV_ROUND_UP (scalar_t__,int) ; 
 int ENOMEM ; 
 int ENOTSUPP ; 
 int /*<<< orphan*/  XMIT_BURST_WITHOUT_SUBADDR ; 
 int /*<<< orphan*/  cdns_i3c_cmd_get_err (struct cdns_i3c_cmd*) ; 
 struct cdns_i3c_xfer* cdns_i3c_master_alloc_xfer (struct cdns_i3c_master*,int) ; 
 int /*<<< orphan*/  cdns_i3c_master_free_xfer (struct cdns_i3c_xfer*) ; 
 int /*<<< orphan*/  cdns_i3c_master_queue_xfer (struct cdns_i3c_master*,struct cdns_i3c_xfer*) ; 
 int /*<<< orphan*/  cdns_i3c_master_unqueue_xfer (struct cdns_i3c_master*,struct cdns_i3c_xfer*) ; 
 struct i3c_master_controller* i3c_dev_get_master (struct i3c_dev_desc*) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 struct cdns_i3c_master* to_cdns_i3c_master (struct i3c_master_controller*) ; 
 int /*<<< orphan*/  wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cdns_i3c_master_priv_xfers(struct i3c_dev_desc *dev,
				      struct i3c_priv_xfer *xfers,
				      int nxfers)
{
	struct i3c_master_controller *m = i3c_dev_get_master(dev);
	struct cdns_i3c_master *master = to_cdns_i3c_master(m);
	int txslots = 0, rxslots = 0, i, ret;
	struct cdns_i3c_xfer *cdns_xfer;

	for (i = 0; i < nxfers; i++) {
		if (xfers[i].len > CMD0_FIFO_PL_LEN_MAX)
			return -ENOTSUPP;
	}

	if (!nxfers)
		return 0;

	if (nxfers > master->caps.cmdfifodepth ||
	    nxfers > master->caps.cmdrfifodepth)
		return -ENOTSUPP;

	/*
	 * First make sure that all transactions (block of transfers separated
	 * by a STOP marker) fit in the FIFOs.
	 */
	for (i = 0; i < nxfers; i++) {
		if (xfers[i].rnw)
			rxslots += DIV_ROUND_UP(xfers[i].len, 4);
		else
			txslots += DIV_ROUND_UP(xfers[i].len, 4);
	}

	if (rxslots > master->caps.rxfifodepth ||
	    txslots > master->caps.txfifodepth)
		return -ENOTSUPP;

	cdns_xfer = cdns_i3c_master_alloc_xfer(master, nxfers);
	if (!cdns_xfer)
		return -ENOMEM;

	for (i = 0; i < nxfers; i++) {
		struct cdns_i3c_cmd *ccmd = &cdns_xfer->cmds[i];
		u32 pl_len = xfers[i].len;

		ccmd->cmd0 = CMD0_FIFO_DEV_ADDR(dev->info.dyn_addr) |
			CMD0_FIFO_PRIV_XMIT_MODE(XMIT_BURST_WITHOUT_SUBADDR);

		if (xfers[i].rnw) {
			ccmd->cmd0 |= CMD0_FIFO_RNW;
			ccmd->rx_buf = xfers[i].data.in;
			ccmd->rx_len = xfers[i].len;
			pl_len++;
		} else {
			ccmd->tx_buf = xfers[i].data.out;
			ccmd->tx_len = xfers[i].len;
		}

		ccmd->cmd0 |= CMD0_FIFO_PL_LEN(pl_len);

		if (i < nxfers - 1)
			ccmd->cmd0 |= CMD0_FIFO_RSBC;

		if (!i)
			ccmd->cmd0 |= CMD0_FIFO_BCH;
	}

	cdns_i3c_master_queue_xfer(master, cdns_xfer);
	if (!wait_for_completion_timeout(&cdns_xfer->comp,
					 msecs_to_jiffies(1000)))
		cdns_i3c_master_unqueue_xfer(master, cdns_xfer);

	ret = cdns_xfer->ret;

	for (i = 0; i < nxfers; i++)
		xfers[i].err = cdns_i3c_cmd_get_err(&cdns_xfer->cmds[i]);

	cdns_i3c_master_free_xfer(cdns_xfer);

	return ret;
}