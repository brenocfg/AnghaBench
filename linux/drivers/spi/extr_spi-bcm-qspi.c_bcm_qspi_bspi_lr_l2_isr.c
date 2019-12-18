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
struct bcm_qspi_soc_intc {int /*<<< orphan*/  (* bcm_qspi_int_ack ) (struct bcm_qspi_soc_intc*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* bcm_qspi_int_set ) (struct bcm_qspi_soc_intc*,int /*<<< orphan*/ ,int) ;} ;
struct bcm_qspi_dev_id {TYPE_1__* irqp; struct bcm_qspi* dev; } ;
struct bcm_qspi {scalar_t__ bspi_rf_op_len; int /*<<< orphan*/  bspi_done; scalar_t__ bspi_enabled; struct bcm_qspi_soc_intc* soc_intc; scalar_t__ bspi_rf_op_status; int /*<<< orphan*/ * bspi_rf_op; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  BSPI_DONE ; 
 int /*<<< orphan*/  INTR_BSPI_LR_SESSION_DONE_MASK ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  bcm_qspi_bspi_flush_prefetch_buffers (struct bcm_qspi*) ; 
 int /*<<< orphan*/  bcm_qspi_bspi_lr_clear (struct bcm_qspi*) ; 
 int /*<<< orphan*/  bcm_qspi_bspi_lr_data_read (struct bcm_qspi*) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct bcm_qspi_soc_intc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub2 (struct bcm_qspi_soc_intc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t bcm_qspi_bspi_lr_l2_isr(int irq, void *dev_id)
{
	struct bcm_qspi_dev_id *qspi_dev_id = dev_id;
	struct bcm_qspi *qspi = qspi_dev_id->dev;
	struct bcm_qspi_soc_intc *soc_intc = qspi->soc_intc;
	u32 status = qspi_dev_id->irqp->mask;

	if (qspi->bspi_enabled && qspi->bspi_rf_op) {
		bcm_qspi_bspi_lr_data_read(qspi);
		if (qspi->bspi_rf_op_len == 0) {
			qspi->bspi_rf_op = NULL;
			if (qspi->soc_intc) {
				/* disable soc BSPI interrupt */
				soc_intc->bcm_qspi_int_set(soc_intc, BSPI_DONE,
							   false);
				/* indicate done */
				status = INTR_BSPI_LR_SESSION_DONE_MASK;
			}

			if (qspi->bspi_rf_op_status)
				bcm_qspi_bspi_lr_clear(qspi);
			else
				bcm_qspi_bspi_flush_prefetch_buffers(qspi);
		}

		if (qspi->soc_intc)
			/* clear soc BSPI interrupt */
			soc_intc->bcm_qspi_int_ack(soc_intc, BSPI_DONE);
	}

	status &= INTR_BSPI_LR_SESSION_DONE_MASK;
	if (qspi->bspi_enabled && status && qspi->bspi_rf_op_len == 0)
		complete(&qspi->bspi_done);

	return IRQ_HANDLED;
}