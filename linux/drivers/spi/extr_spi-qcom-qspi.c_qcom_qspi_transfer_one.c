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
struct spi_transfer {long speed_hz; int /*<<< orphan*/  len; int /*<<< orphan*/  transfer_list; int /*<<< orphan*/  tx_buf; int /*<<< orphan*/  tx_nbits; scalar_t__ rx_buf; int /*<<< orphan*/  rx_nbits; } ;
struct spi_master {TYPE_2__* cur_msg; } ;
struct spi_device {unsigned long max_speed_hz; } ;
struct TYPE_6__ {int /*<<< orphan*/  rem_bytes; int /*<<< orphan*/  is_last; int /*<<< orphan*/  tx_buf; int /*<<< orphan*/  buswidth; int /*<<< orphan*/  dir; scalar_t__ rx_buf; } ;
struct qcom_qspi {int /*<<< orphan*/  lock; TYPE_3__ xfer; int /*<<< orphan*/  dev; TYPE_1__* clks; } ;
struct TYPE_5__ {int /*<<< orphan*/  transfers; } ;
struct TYPE_4__ {int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 size_t QSPI_CLK_CORE ; 
 int /*<<< orphan*/  QSPI_READ ; 
 int /*<<< orphan*/  QSPI_WRITE ; 
 int clk_set_rate (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  list_is_last (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qcom_qspi_pio_xfer (struct qcom_qspi*) ; 
 struct qcom_qspi* spi_master_get_devdata (struct spi_master*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int qcom_qspi_transfer_one(struct spi_master *master,
				  struct spi_device *slv,
				  struct spi_transfer *xfer)
{
	struct qcom_qspi *ctrl = spi_master_get_devdata(master);
	int ret;
	unsigned long speed_hz;
	unsigned long flags;

	speed_hz = slv->max_speed_hz;
	if (xfer->speed_hz)
		speed_hz = xfer->speed_hz;

	/* In regular operation (SBL_EN=1) core must be 4x transfer clock */
	ret = clk_set_rate(ctrl->clks[QSPI_CLK_CORE].clk, speed_hz * 4);
	if (ret) {
		dev_err(ctrl->dev, "Failed to set core clk %d\n", ret);
		return ret;
	}

	spin_lock_irqsave(&ctrl->lock, flags);

	/* We are half duplex, so either rx or tx will be set */
	if (xfer->rx_buf) {
		ctrl->xfer.dir = QSPI_READ;
		ctrl->xfer.buswidth = xfer->rx_nbits;
		ctrl->xfer.rx_buf = xfer->rx_buf;
	} else {
		ctrl->xfer.dir = QSPI_WRITE;
		ctrl->xfer.buswidth = xfer->tx_nbits;
		ctrl->xfer.tx_buf = xfer->tx_buf;
	}
	ctrl->xfer.is_last = list_is_last(&xfer->transfer_list,
					  &master->cur_msg->transfers);
	ctrl->xfer.rem_bytes = xfer->len;
	qcom_qspi_pio_xfer(ctrl);

	spin_unlock_irqrestore(&ctrl->lock, flags);

	/* We'll call spi_finalize_current_transfer() when done */
	return 1;
}