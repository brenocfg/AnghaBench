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
struct TYPE_2__ {int /*<<< orphan*/  rem_bytes; } ;
struct qcom_qspi {scalar_t__ base; TYPE_1__ xfer; } ;

/* Variables and functions */
 scalar_t__ PIO_XFER_CTRL ; 
 int /*<<< orphan*/  REQUEST_COUNT_MSK ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void qcom_qspi_pio_xfer_ctrl(struct qcom_qspi *ctrl)
{
	u32 pio_xfer_ctrl;

	pio_xfer_ctrl = readl(ctrl->base + PIO_XFER_CTRL);
	pio_xfer_ctrl &= ~REQUEST_COUNT_MSK;
	pio_xfer_ctrl |= ctrl->xfer.rem_bytes;
	writel(pio_xfer_ctrl, ctrl->base + PIO_XFER_CTRL);
}