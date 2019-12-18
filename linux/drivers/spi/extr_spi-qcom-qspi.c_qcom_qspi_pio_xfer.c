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
struct TYPE_2__ {scalar_t__ dir; } ;
struct qcom_qspi {scalar_t__ base; TYPE_1__ xfer; } ;

/* Variables and functions */
 scalar_t__ MSTR_INT_EN ; 
 scalar_t__ MSTR_INT_STATUS ; 
 int QSPI_ALL_IRQS ; 
 int QSPI_ERR_IRQS ; 
 scalar_t__ QSPI_WRITE ; 
 int RESP_FIFO_RDY ; 
 int WR_FIFO_EMPTY ; 
 int /*<<< orphan*/  qcom_qspi_pio_xfer_cfg (struct qcom_qspi*) ; 
 int /*<<< orphan*/  qcom_qspi_pio_xfer_ctrl (struct qcom_qspi*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void qcom_qspi_pio_xfer(struct qcom_qspi *ctrl)
{
	u32 ints;

	qcom_qspi_pio_xfer_cfg(ctrl);

	/* Ack any previous interrupts that might be hanging around */
	writel(QSPI_ALL_IRQS, ctrl->base + MSTR_INT_STATUS);

	/* Setup new interrupts */
	if (ctrl->xfer.dir == QSPI_WRITE)
		ints = QSPI_ERR_IRQS | WR_FIFO_EMPTY;
	else
		ints = QSPI_ERR_IRQS | RESP_FIFO_RDY;
	writel(ints, ctrl->base + MSTR_INT_EN);

	/* Kick off the transfer */
	qcom_qspi_pio_xfer_ctrl(ctrl);
}