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
struct sun4i_spi {int /*<<< orphan*/  len; int /*<<< orphan*/  done; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  SUN4I_FIFO_DEPTH ; 
 int SUN4I_INT_CTL_RF_F34 ; 
 int SUN4I_INT_CTL_TC ; 
 int SUN4I_INT_CTL_TF_E34 ; 
 int /*<<< orphan*/  SUN4I_INT_STA_REG ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sun4i_spi_disable_interrupt (struct sun4i_spi*,int) ; 
 int /*<<< orphan*/  sun4i_spi_drain_fifo (struct sun4i_spi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sun4i_spi_fill_fifo (struct sun4i_spi*,int /*<<< orphan*/ ) ; 
 int sun4i_spi_read (struct sun4i_spi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sun4i_spi_write (struct sun4i_spi*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static irqreturn_t sun4i_spi_handler(int irq, void *dev_id)
{
	struct sun4i_spi *sspi = dev_id;
	u32 status = sun4i_spi_read(sspi, SUN4I_INT_STA_REG);

	/* Transfer complete */
	if (status & SUN4I_INT_CTL_TC) {
		sun4i_spi_write(sspi, SUN4I_INT_STA_REG, SUN4I_INT_CTL_TC);
		sun4i_spi_drain_fifo(sspi, SUN4I_FIFO_DEPTH);
		complete(&sspi->done);
		return IRQ_HANDLED;
	}

	/* Receive FIFO 3/4 full */
	if (status & SUN4I_INT_CTL_RF_F34) {
		sun4i_spi_drain_fifo(sspi, SUN4I_FIFO_DEPTH);
		/* Only clear the interrupt _after_ draining the FIFO */
		sun4i_spi_write(sspi, SUN4I_INT_STA_REG, SUN4I_INT_CTL_RF_F34);
		return IRQ_HANDLED;
	}

	/* Transmit FIFO 3/4 empty */
	if (status & SUN4I_INT_CTL_TF_E34) {
		sun4i_spi_fill_fifo(sspi, SUN4I_FIFO_DEPTH);

		if (!sspi->len)
			/* nothing left to transmit */
			sun4i_spi_disable_interrupt(sspi, SUN4I_INT_CTL_TF_E34);

		/* Only clear the interrupt _after_ re-seeding the FIFO */
		sun4i_spi_write(sspi, SUN4I_INT_STA_REG, SUN4I_INT_CTL_TF_E34);

		return IRQ_HANDLED;
	}

	return IRQ_NONE;
}