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
typedef  int u32 ;
struct cx23885_tsport {size_t sram_chno; int /*<<< orphan*/  reg_ts_int_stat; int /*<<< orphan*/  slock; int /*<<< orphan*/  mpegq; int /*<<< orphan*/  dma_ctl_val; int /*<<< orphan*/  reg_dma_ctl; int /*<<< orphan*/  reg_ts_int_msk; int /*<<< orphan*/  reg_gpcnt; } ;
struct cx23885_dev {int /*<<< orphan*/ * sram_channels; int /*<<< orphan*/  name; struct cx23885_tsport ts1; } ;

/* Variables and functions */
 int VID_B_MSK_BAD_PKT ; 
 int VID_B_MSK_OF ; 
 int VID_B_MSK_OPC_ERR ; 
 int VID_B_MSK_RISCI1 ; 
 int VID_B_MSK_SYNC ; 
 int VID_B_MSK_VBI_OF ; 
 int VID_B_MSK_VBI_OPC_ERR ; 
 int VID_B_MSK_VBI_SYNC ; 
 int /*<<< orphan*/  cx23885_417_check_encoder (struct cx23885_dev*) ; 
 int /*<<< orphan*/  cx23885_sram_channel_dump (struct cx23885_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cx23885_wakeup (struct cx23885_tsport*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  cx_clear (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int cx_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cx_write (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dprintk (int,char*,...) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int cx23885_irq_417(struct cx23885_dev *dev, u32 status)
{
	/* FIXME: port1 assumption here. */
	struct cx23885_tsport *port = &dev->ts1;
	int count = 0;
	int handled = 0;

	if (status == 0)
		return handled;

	count = cx_read(port->reg_gpcnt);
	dprintk(7, "status: 0x%08x  mask: 0x%08x count: 0x%x\n",
		status, cx_read(port->reg_ts_int_msk), count);

	if ((status & VID_B_MSK_BAD_PKT)         ||
		(status & VID_B_MSK_OPC_ERR)     ||
		(status & VID_B_MSK_VBI_OPC_ERR) ||
		(status & VID_B_MSK_SYNC)        ||
		(status & VID_B_MSK_VBI_SYNC)    ||
		(status & VID_B_MSK_OF)          ||
		(status & VID_B_MSK_VBI_OF)) {
		pr_err("%s: V4L mpeg risc op code error, status = 0x%x\n",
		       dev->name, status);
		if (status & VID_B_MSK_BAD_PKT)
			dprintk(1, "        VID_B_MSK_BAD_PKT\n");
		if (status & VID_B_MSK_OPC_ERR)
			dprintk(1, "        VID_B_MSK_OPC_ERR\n");
		if (status & VID_B_MSK_VBI_OPC_ERR)
			dprintk(1, "        VID_B_MSK_VBI_OPC_ERR\n");
		if (status & VID_B_MSK_SYNC)
			dprintk(1, "        VID_B_MSK_SYNC\n");
		if (status & VID_B_MSK_VBI_SYNC)
			dprintk(1, "        VID_B_MSK_VBI_SYNC\n");
		if (status & VID_B_MSK_OF)
			dprintk(1, "        VID_B_MSK_OF\n");
		if (status & VID_B_MSK_VBI_OF)
			dprintk(1, "        VID_B_MSK_VBI_OF\n");

		cx_clear(port->reg_dma_ctl, port->dma_ctl_val);
		cx23885_sram_channel_dump(dev,
			&dev->sram_channels[port->sram_chno]);
		cx23885_417_check_encoder(dev);
	} else if (status & VID_B_MSK_RISCI1) {
		dprintk(7, "        VID_B_MSK_RISCI1\n");
		spin_lock(&port->slock);
		cx23885_wakeup(port, &port->mpegq, count);
		spin_unlock(&port->slock);
	}
	if (status) {
		cx_write(port->reg_ts_int_stat, status);
		handled = 1;
	}

	return handled;
}