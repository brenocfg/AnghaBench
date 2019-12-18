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
struct driver_data {int /*<<< orphan*/  controller; int /*<<< orphan*/  clear_sr; } ;

/* Variables and functions */
 int /*<<< orphan*/  SSTO ; 
 int /*<<< orphan*/  pxa25x_ssp_comp (struct driver_data*) ; 
 int /*<<< orphan*/  pxa2xx_spi_write (struct driver_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_sccr1 (struct driver_data*) ; 
 int /*<<< orphan*/  spi_finalize_current_transfer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_SSSR_CS (struct driver_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void int_transfer_complete(struct driver_data *drv_data)
{
	/* Clear and disable interrupts */
	write_SSSR_CS(drv_data, drv_data->clear_sr);
	reset_sccr1(drv_data);
	if (!pxa25x_ssp_comp(drv_data))
		pxa2xx_spi_write(drv_data, SSTO, 0);

	spi_finalize_current_transfer(drv_data->controller);
}