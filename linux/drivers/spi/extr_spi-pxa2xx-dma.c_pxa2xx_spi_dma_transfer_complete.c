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
struct spi_message {int /*<<< orphan*/  status; } ;
struct driver_data {int mask_sr; int dma_cr1; TYPE_1__* controller; int /*<<< orphan*/  clear_sr; int /*<<< orphan*/  dma_running; } ;
struct TYPE_2__ {struct spi_message* cur_msg; } ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  SSCR0 ; 
 int SSCR0_SSE ; 
 int /*<<< orphan*/  SSCR1 ; 
 int /*<<< orphan*/  SSSR ; 
 int SSSR_ROR ; 
 int /*<<< orphan*/  SSTO ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pxa25x_ssp_comp (struct driver_data*) ; 
 int pxa2xx_spi_read (struct driver_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pxa2xx_spi_write (struct driver_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spi_finalize_current_transfer (TYPE_1__*) ; 
 int /*<<< orphan*/  write_SSSR_CS (struct driver_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pxa2xx_spi_dma_transfer_complete(struct driver_data *drv_data,
					     bool error)
{
	struct spi_message *msg = drv_data->controller->cur_msg;

	/*
	 * It is possible that one CPU is handling ROR interrupt and other
	 * just gets DMA completion. Calling pump_transfers() twice for the
	 * same transfer leads to problems thus we prevent concurrent calls
	 * by using ->dma_running.
	 */
	if (atomic_dec_and_test(&drv_data->dma_running)) {
		/*
		 * If the other CPU is still handling the ROR interrupt we
		 * might not know about the error yet. So we re-check the
		 * ROR bit here before we clear the status register.
		 */
		if (!error) {
			u32 status = pxa2xx_spi_read(drv_data, SSSR)
				     & drv_data->mask_sr;
			error = status & SSSR_ROR;
		}

		/* Clear status & disable interrupts */
		pxa2xx_spi_write(drv_data, SSCR1,
				 pxa2xx_spi_read(drv_data, SSCR1)
				 & ~drv_data->dma_cr1);
		write_SSSR_CS(drv_data, drv_data->clear_sr);
		if (!pxa25x_ssp_comp(drv_data))
			pxa2xx_spi_write(drv_data, SSTO, 0);

		if (error) {
			/* In case we got an error we disable the SSP now */
			pxa2xx_spi_write(drv_data, SSCR0,
					 pxa2xx_spi_read(drv_data, SSCR0)
					 & ~SSCR0_SSE);
			msg->status = -EIO;
		}

		spi_finalize_current_transfer(drv_data->controller);
	}
}