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
struct i3c_master_controller {int dummy; } ;
struct i2c_msg {scalar_t__ len; int flags; int /*<<< orphan*/  buf; int /*<<< orphan*/  addr; } ;
struct i2c_dev_desc {int dummy; } ;
struct cdns_i3c_xfer {int ret; int /*<<< orphan*/  comp; struct cdns_i3c_cmd* cmds; } ;
struct TYPE_2__ {int cmdfifodepth; unsigned int txfifodepth; unsigned int rxfifodepth; } ;
struct cdns_i3c_master {TYPE_1__ caps; } ;
struct cdns_i3c_cmd {int cmd0; scalar_t__ rx_len; scalar_t__ tx_len; int /*<<< orphan*/  tx_buf; int /*<<< orphan*/  rx_buf; } ;

/* Variables and functions */
 int CMD0_FIFO_DEV_ADDR (int /*<<< orphan*/ ) ; 
 int CMD0_FIFO_IS_10B ; 
 int CMD0_FIFO_PL_LEN (scalar_t__) ; 
 scalar_t__ CMD0_FIFO_PL_LEN_MAX ; 
 int CMD0_FIFO_PRIV_XMIT_MODE (int /*<<< orphan*/ ) ; 
 int CMD0_FIFO_RNW ; 
 scalar_t__ DIV_ROUND_UP (scalar_t__,int) ; 
 int ENOMEM ; 
 int ENOTSUPP ; 
 int I2C_M_RD ; 
 int I2C_M_TEN ; 
 int /*<<< orphan*/  XMIT_BURST_WITHOUT_SUBADDR ; 
 struct cdns_i3c_xfer* cdns_i3c_master_alloc_xfer (struct cdns_i3c_master*,int) ; 
 int /*<<< orphan*/  cdns_i3c_master_free_xfer (struct cdns_i3c_xfer*) ; 
 int /*<<< orphan*/  cdns_i3c_master_queue_xfer (struct cdns_i3c_master*,struct cdns_i3c_xfer*) ; 
 int /*<<< orphan*/  cdns_i3c_master_unqueue_xfer (struct cdns_i3c_master*,struct cdns_i3c_xfer*) ; 
 struct i3c_master_controller* i2c_dev_get_master (struct i2c_dev_desc*) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 struct cdns_i3c_master* to_cdns_i3c_master (struct i3c_master_controller*) ; 
 int /*<<< orphan*/  wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cdns_i3c_master_i2c_xfers(struct i2c_dev_desc *dev,
				     const struct i2c_msg *xfers, int nxfers)
{
	struct i3c_master_controller *m = i2c_dev_get_master(dev);
	struct cdns_i3c_master *master = to_cdns_i3c_master(m);
	unsigned int nrxwords = 0, ntxwords = 0;
	struct cdns_i3c_xfer *xfer;
	int i, ret = 0;

	if (nxfers > master->caps.cmdfifodepth)
		return -ENOTSUPP;

	for (i = 0; i < nxfers; i++) {
		if (xfers[i].len > CMD0_FIFO_PL_LEN_MAX)
			return -ENOTSUPP;

		if (xfers[i].flags & I2C_M_RD)
			nrxwords += DIV_ROUND_UP(xfers[i].len, 4);
		else
			ntxwords += DIV_ROUND_UP(xfers[i].len, 4);
	}

	if (ntxwords > master->caps.txfifodepth ||
	    nrxwords > master->caps.rxfifodepth)
		return -ENOTSUPP;

	xfer = cdns_i3c_master_alloc_xfer(master, nxfers);
	if (!xfer)
		return -ENOMEM;

	for (i = 0; i < nxfers; i++) {
		struct cdns_i3c_cmd *ccmd = &xfer->cmds[i];

		ccmd->cmd0 = CMD0_FIFO_DEV_ADDR(xfers[i].addr) |
			CMD0_FIFO_PL_LEN(xfers[i].len) |
			CMD0_FIFO_PRIV_XMIT_MODE(XMIT_BURST_WITHOUT_SUBADDR);

		if (xfers[i].flags & I2C_M_TEN)
			ccmd->cmd0 |= CMD0_FIFO_IS_10B;

		if (xfers[i].flags & I2C_M_RD) {
			ccmd->cmd0 |= CMD0_FIFO_RNW;
			ccmd->rx_buf = xfers[i].buf;
			ccmd->rx_len = xfers[i].len;
		} else {
			ccmd->tx_buf = xfers[i].buf;
			ccmd->tx_len = xfers[i].len;
		}
	}

	cdns_i3c_master_queue_xfer(master, xfer);
	if (!wait_for_completion_timeout(&xfer->comp, msecs_to_jiffies(1000)))
		cdns_i3c_master_unqueue_xfer(master, xfer);

	ret = xfer->ret;
	cdns_i3c_master_free_xfer(xfer);

	return ret;
}