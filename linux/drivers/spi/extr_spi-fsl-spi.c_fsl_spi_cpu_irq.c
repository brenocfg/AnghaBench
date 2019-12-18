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
struct mpc8xxx_spi {int (* get_tx ) (struct mpc8xxx_spi*) ;int /*<<< orphan*/  done; scalar_t__ count; int /*<<< orphan*/  (* get_rx ) (int,struct mpc8xxx_spi*) ;scalar_t__ rx; struct fsl_spi_reg* reg_base; } ;
struct fsl_spi_reg {int /*<<< orphan*/  transmit; int /*<<< orphan*/  event; int /*<<< orphan*/  receive; } ;

/* Variables and functions */
 int SPIE_NE ; 
 int SPIE_NF ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int mpc8xxx_spi_read_reg (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mpc8xxx_spi_write_reg (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub1 (int,struct mpc8xxx_spi*) ; 
 int stub2 (struct mpc8xxx_spi*) ; 

__attribute__((used)) static void fsl_spi_cpu_irq(struct mpc8xxx_spi *mspi, u32 events)
{
	struct fsl_spi_reg *reg_base = mspi->reg_base;

	/* We need handle RX first */
	if (events & SPIE_NE) {
		u32 rx_data = mpc8xxx_spi_read_reg(&reg_base->receive);

		if (mspi->rx)
			mspi->get_rx(rx_data, mspi);
	}

	if ((events & SPIE_NF) == 0)
		/* spin until TX is done */
		while (((events =
			mpc8xxx_spi_read_reg(&reg_base->event)) &
						SPIE_NF) == 0)
			cpu_relax();

	/* Clear the events */
	mpc8xxx_spi_write_reg(&reg_base->event, events);

	mspi->count -= 1;
	if (mspi->count) {
		u32 word = mspi->get_tx(mspi);

		mpc8xxx_spi_write_reg(&reg_base->transmit, word);
	} else {
		complete(&mspi->done);
	}
}