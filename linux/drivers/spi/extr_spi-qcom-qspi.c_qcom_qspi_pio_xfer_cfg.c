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
typedef  int /*<<< orphan*/  u32 ;
struct qspi_xfer {int /*<<< orphan*/  buswidth; scalar_t__ is_last; int /*<<< orphan*/  dir; } ;
struct qcom_qspi {scalar_t__ base; struct qspi_xfer xfer; } ;

/* Variables and functions */
 int /*<<< orphan*/  MULTI_IO_MODE_MSK ; 
 scalar_t__ PIO_XFER_CFG ; 
 int /*<<< orphan*/  TRANSFER_DIRECTION ; 
 int /*<<< orphan*/  TRANSFER_FRAGMENT ; 
 int /*<<< orphan*/  qspi_buswidth_to_iomode (struct qcom_qspi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void qcom_qspi_pio_xfer_cfg(struct qcom_qspi *ctrl)
{
	u32 pio_xfer_cfg;
	const struct qspi_xfer *xfer;

	xfer = &ctrl->xfer;
	pio_xfer_cfg = readl(ctrl->base + PIO_XFER_CFG);
	pio_xfer_cfg &= ~TRANSFER_DIRECTION;
	pio_xfer_cfg |= xfer->dir;
	if (xfer->is_last)
		pio_xfer_cfg &= ~TRANSFER_FRAGMENT;
	else
		pio_xfer_cfg |= TRANSFER_FRAGMENT;
	pio_xfer_cfg &= ~MULTI_IO_MODE_MSK;
	pio_xfer_cfg |= qspi_buswidth_to_iomode(ctrl, xfer->buswidth);

	writel(pio_xfer_cfg, ctrl->base + PIO_XFER_CFG);
}