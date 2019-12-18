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
typedef  int u32 ;
struct axxia_i2c_dev {scalar_t__ msg_xfrd_r; scalar_t__ base; int /*<<< orphan*/  msg_complete; int /*<<< orphan*/  msg_err; TYPE_1__* msg_r; scalar_t__ last; TYPE_1__* msg; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {scalar_t__ len; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  EAGAIN ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  ENXIO ; 
 int /*<<< orphan*/  ETIMEDOUT ; 
 scalar_t__ INTERRUPT_STATUS ; 
 int INT_MST ; 
 int INT_SLV ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 scalar_t__ MST_INT_STATUS ; 
 scalar_t__ MST_RX_BYTES_XFRD ; 
 scalar_t__ MST_RX_XFER ; 
 int MST_STATUS_AL ; 
 int MST_STATUS_ERR ; 
 int MST_STATUS_NAK ; 
 int MST_STATUS_RFL ; 
 int MST_STATUS_SCC ; 
 int MST_STATUS_SNS ; 
 int MST_STATUS_SS ; 
 int MST_STATUS_TFL ; 
 int MST_STATUS_TSS ; 
 scalar_t__ MST_TX_BYTES_XFRD ; 
 scalar_t__ MST_TX_XFER ; 
 int /*<<< orphan*/  axxia_i2c_empty_rx_fifo (struct axxia_i2c_dev*) ; 
 scalar_t__ axxia_i2c_fill_tx_fifo (struct axxia_i2c_dev*) ; 
 int /*<<< orphan*/  axxia_i2c_slv_isr (struct axxia_i2c_dev*) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int,int,int,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  i2c_int_disable (struct axxia_i2c_dev*,int) ; 
 scalar_t__ i2c_m_rd (TYPE_1__*) ; 
 int readl (scalar_t__) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static irqreturn_t axxia_i2c_isr(int irq, void *_dev)
{
	struct axxia_i2c_dev *idev = _dev;
	irqreturn_t ret = IRQ_NONE;
	u32 status;

	status = readl(idev->base + INTERRUPT_STATUS);

	if (status & INT_SLV)
		ret = axxia_i2c_slv_isr(idev);
	if (!(status & INT_MST))
		return ret;

	/* Read interrupt status bits */
	status = readl(idev->base + MST_INT_STATUS);

	if (!idev->msg) {
		dev_warn(idev->dev, "unexpected interrupt\n");
		goto out;
	}

	/* RX FIFO needs service? */
	if (i2c_m_rd(idev->msg_r) && (status & MST_STATUS_RFL))
		axxia_i2c_empty_rx_fifo(idev);

	/* TX FIFO needs service? */
	if (!i2c_m_rd(idev->msg) && (status & MST_STATUS_TFL)) {
		if (axxia_i2c_fill_tx_fifo(idev) == 0)
			i2c_int_disable(idev, MST_STATUS_TFL);
	}

	if (unlikely(status & MST_STATUS_ERR)) {
		/* Transfer error */
		i2c_int_disable(idev, ~0);
		if (status & MST_STATUS_AL)
			idev->msg_err = -EAGAIN;
		else if (status & MST_STATUS_NAK)
			idev->msg_err = -ENXIO;
		else
			idev->msg_err = -EIO;
		dev_dbg(idev->dev, "error %#x, addr=%#x rx=%u/%u tx=%u/%u\n",
			status,
			idev->msg->addr,
			readl(idev->base + MST_RX_BYTES_XFRD),
			readl(idev->base + MST_RX_XFER),
			readl(idev->base + MST_TX_BYTES_XFRD),
			readl(idev->base + MST_TX_XFER));
		complete(&idev->msg_complete);
	} else if (status & MST_STATUS_SCC) {
		/* Stop completed */
		i2c_int_disable(idev, ~MST_STATUS_TSS);
		complete(&idev->msg_complete);
	} else if (status & (MST_STATUS_SNS | MST_STATUS_SS)) {
		/* Transfer done */
		int mask = idev->last ? ~0 : ~MST_STATUS_TSS;

		i2c_int_disable(idev, mask);
		if (i2c_m_rd(idev->msg_r) && idev->msg_xfrd_r < idev->msg_r->len)
			axxia_i2c_empty_rx_fifo(idev);
		complete(&idev->msg_complete);
	} else if (status & MST_STATUS_TSS) {
		/* Transfer timeout */
		idev->msg_err = -ETIMEDOUT;
		i2c_int_disable(idev, ~MST_STATUS_TSS);
		complete(&idev->msg_complete);
	}

out:
	/* Clear interrupt */
	writel(INT_MST, idev->base + INTERRUPT_STATUS);

	return IRQ_HANDLED;
}