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
struct bcm_qspi_soc_intc {int /*<<< orphan*/  (* bcm_qspi_int_ack ) (struct bcm_qspi_soc_intc*,int /*<<< orphan*/ ) ;} ;
struct bcm_qspi_dev_id {struct bcm_qspi* dev; } ;
struct bcm_qspi {int /*<<< orphan*/  bspi_done; struct bcm_qspi_soc_intc* soc_intc; int /*<<< orphan*/  bspi_rf_op_status; TYPE_1__* pdev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BSPI_ERR ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  stub1 (struct bcm_qspi_soc_intc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t bcm_qspi_bspi_lr_err_l2_isr(int irq, void *dev_id)
{
	struct bcm_qspi_dev_id *qspi_dev_id = dev_id;
	struct bcm_qspi *qspi = qspi_dev_id->dev;
	struct bcm_qspi_soc_intc *soc_intc = qspi->soc_intc;

	dev_err(&qspi->pdev->dev, "BSPI INT error\n");
	qspi->bspi_rf_op_status = -EIO;
	if (qspi->soc_intc)
		/* clear soc interrupt */
		soc_intc->bcm_qspi_int_ack(soc_intc, BSPI_ERR);

	complete(&qspi->bspi_done);
	return IRQ_HANDLED;
}