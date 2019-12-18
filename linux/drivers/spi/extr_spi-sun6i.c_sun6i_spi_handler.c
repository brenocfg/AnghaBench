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
struct sun6i_spi {int /*<<< orphan*/  len; int /*<<< orphan*/  done; int /*<<< orphan*/  fifo_depth; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  SUN6I_FIFO_DEPTH ; 
 int SUN6I_INT_CTL_RF_RDY ; 
 int SUN6I_INT_CTL_TC ; 
 int SUN6I_INT_CTL_TF_ERQ ; 
 int /*<<< orphan*/  SUN6I_INT_STA_REG ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sun6i_spi_disable_interrupt (struct sun6i_spi*,int) ; 
 int /*<<< orphan*/  sun6i_spi_drain_fifo (struct sun6i_spi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sun6i_spi_fill_fifo (struct sun6i_spi*,int /*<<< orphan*/ ) ; 
 int sun6i_spi_read (struct sun6i_spi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sun6i_spi_write (struct sun6i_spi*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static irqreturn_t sun6i_spi_handler(int irq, void *dev_id)
{
	struct sun6i_spi *sspi = dev_id;
	u32 status = sun6i_spi_read(sspi, SUN6I_INT_STA_REG);

	/* Transfer complete */
	if (status & SUN6I_INT_CTL_TC) {
		sun6i_spi_write(sspi, SUN6I_INT_STA_REG, SUN6I_INT_CTL_TC);
		sun6i_spi_drain_fifo(sspi, sspi->fifo_depth);
		complete(&sspi->done);
		return IRQ_HANDLED;
	}

	/* Receive FIFO 3/4 full */
	if (status & SUN6I_INT_CTL_RF_RDY) {
		sun6i_spi_drain_fifo(sspi, SUN6I_FIFO_DEPTH);
		/* Only clear the interrupt _after_ draining the FIFO */
		sun6i_spi_write(sspi, SUN6I_INT_STA_REG, SUN6I_INT_CTL_RF_RDY);
		return IRQ_HANDLED;
	}

	/* Transmit FIFO 3/4 empty */
	if (status & SUN6I_INT_CTL_TF_ERQ) {
		sun6i_spi_fill_fifo(sspi, SUN6I_FIFO_DEPTH);

		if (!sspi->len)
			/* nothing left to transmit */
			sun6i_spi_disable_interrupt(sspi, SUN6I_INT_CTL_TF_ERQ);

		/* Only clear the interrupt _after_ re-seeding the FIFO */
		sun6i_spi_write(sspi, SUN6I_INT_STA_REG, SUN6I_INT_CTL_TF_ERQ);

		return IRQ_HANDLED;
	}

	return IRQ_NONE;
}