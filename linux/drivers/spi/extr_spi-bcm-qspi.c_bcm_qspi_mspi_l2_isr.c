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
struct bcm_qspi_soc_intc {int /*<<< orphan*/  (* bcm_qspi_int_ack ) (struct bcm_qspi_soc_intc*,int /*<<< orphan*/ ) ;} ;
struct bcm_qspi_dev_id {struct bcm_qspi* dev; } ;
struct bcm_qspi {int /*<<< orphan*/  mspi_done; struct bcm_qspi_soc_intc* soc_intc; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  MSPI ; 
 int /*<<< orphan*/  MSPI_DONE ; 
 int /*<<< orphan*/  MSPI_MSPI_STATUS ; 
 int MSPI_MSPI_STATUS_SPIF ; 
 int bcm_qspi_read (struct bcm_qspi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcm_qspi_write (struct bcm_qspi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct bcm_qspi_soc_intc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t bcm_qspi_mspi_l2_isr(int irq, void *dev_id)
{
	struct bcm_qspi_dev_id *qspi_dev_id = dev_id;
	struct bcm_qspi *qspi = qspi_dev_id->dev;
	u32 status = bcm_qspi_read(qspi, MSPI, MSPI_MSPI_STATUS);

	if (status & MSPI_MSPI_STATUS_SPIF) {
		struct bcm_qspi_soc_intc *soc_intc = qspi->soc_intc;
		/* clear interrupt */
		status &= ~MSPI_MSPI_STATUS_SPIF;
		bcm_qspi_write(qspi, MSPI, MSPI_MSPI_STATUS, status);
		if (qspi->soc_intc)
			soc_intc->bcm_qspi_int_ack(soc_intc, MSPI_DONE);
		complete(&qspi->mspi_done);
		return IRQ_HANDLED;
	}

	return IRQ_NONE;
}