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
struct TYPE_2__ {scalar_t__ dir; int /*<<< orphan*/  rem_bytes; } ;
struct qcom_qspi {int /*<<< orphan*/  lock; int /*<<< orphan*/  dev; scalar_t__ base; TYPE_1__ xfer; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int HRESP_FROM_NOC_ERR ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 scalar_t__ MSTR_INT_EN ; 
 scalar_t__ MSTR_INT_STATUS ; 
 int QSPI_ERR_IRQS ; 
 scalar_t__ QSPI_WRITE ; 
 int RESP_FIFO_RDY ; 
 int RESP_FIFO_UNDERRUN ; 
 int WR_FIFO_EMPTY ; 
 int WR_FIFO_OVERRUN ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pio_read (struct qcom_qspi*) ; 
 int /*<<< orphan*/  pio_write (struct qcom_qspi*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  spi_finalize_current_transfer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static irqreturn_t qcom_qspi_irq(int irq, void *dev_id)
{
	u32 int_status;
	struct qcom_qspi *ctrl = dev_id;
	irqreturn_t ret = IRQ_NONE;
	unsigned long flags;

	spin_lock_irqsave(&ctrl->lock, flags);

	int_status = readl(ctrl->base + MSTR_INT_STATUS);
	writel(int_status, ctrl->base + MSTR_INT_STATUS);

	if (ctrl->xfer.dir == QSPI_WRITE) {
		if (int_status & WR_FIFO_EMPTY)
			ret = pio_write(ctrl);
	} else {
		if (int_status & RESP_FIFO_RDY)
			ret = pio_read(ctrl);
	}

	if (int_status & QSPI_ERR_IRQS) {
		if (int_status & RESP_FIFO_UNDERRUN)
			dev_err(ctrl->dev, "IRQ error: FIFO underrun\n");
		if (int_status & WR_FIFO_OVERRUN)
			dev_err(ctrl->dev, "IRQ error: FIFO overrun\n");
		if (int_status & HRESP_FROM_NOC_ERR)
			dev_err(ctrl->dev, "IRQ error: NOC response error\n");
		ret = IRQ_HANDLED;
	}

	if (!ctrl->xfer.rem_bytes) {
		writel(0, ctrl->base + MSTR_INT_EN);
		spi_finalize_current_transfer(dev_get_drvdata(ctrl->dev));
	}

	spin_unlock_irqrestore(&ctrl->lock, flags);
	return ret;
}