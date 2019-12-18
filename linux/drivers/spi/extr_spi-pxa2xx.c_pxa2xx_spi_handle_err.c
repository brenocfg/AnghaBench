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
struct spi_message {int dummy; } ;
struct spi_controller {int dummy; } ;
struct driver_data {int int_cr1; int dma_cr1; int /*<<< orphan*/  dma_running; int /*<<< orphan*/  clear_sr; } ;

/* Variables and functions */
 int /*<<< orphan*/  SSCR0 ; 
 int SSCR0_SSE ; 
 int /*<<< orphan*/  SSCR1 ; 
 int /*<<< orphan*/  SSTO ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pxa25x_ssp_comp (struct driver_data*) ; 
 int /*<<< orphan*/  pxa2xx_spi_dma_stop (struct driver_data*) ; 
 int pxa2xx_spi_read (struct driver_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pxa2xx_spi_write (struct driver_data*,int /*<<< orphan*/ ,int) ; 
 struct driver_data* spi_controller_get_devdata (struct spi_controller*) ; 
 int /*<<< orphan*/  write_SSSR_CS (struct driver_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pxa2xx_spi_handle_err(struct spi_controller *controller,
				 struct spi_message *msg)
{
	struct driver_data *drv_data = spi_controller_get_devdata(controller);

	/* Disable the SSP */
	pxa2xx_spi_write(drv_data, SSCR0,
			 pxa2xx_spi_read(drv_data, SSCR0) & ~SSCR0_SSE);
	/* Clear and disable interrupts and service requests */
	write_SSSR_CS(drv_data, drv_data->clear_sr);
	pxa2xx_spi_write(drv_data, SSCR1,
			 pxa2xx_spi_read(drv_data, SSCR1)
			 & ~(drv_data->int_cr1 | drv_data->dma_cr1));
	if (!pxa25x_ssp_comp(drv_data))
		pxa2xx_spi_write(drv_data, SSTO, 0);

	/*
	 * Stop the DMA if running. Note DMA callback handler may have unset
	 * the dma_running already, which is fine as stopping is not needed
	 * then but we shouldn't rely this flag for anything else than
	 * stopping. For instance to differentiate between PIO and DMA
	 * transfers.
	 */
	if (atomic_read(&drv_data->dma_running))
		pxa2xx_spi_dma_stop(drv_data);
}