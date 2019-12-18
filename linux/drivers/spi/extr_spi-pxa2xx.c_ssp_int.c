#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct driver_data {int mask_sr; int int_cr1; int /*<<< orphan*/  (* transfer_handler ) (struct driver_data*) ;TYPE_2__* controller; TYPE_1__* pdev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_4__ {int /*<<< orphan*/  cur_msg; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  SSCR1 ; 
 int SSCR1_TIE ; 
 int SSCR1_TINTE ; 
 int /*<<< orphan*/  SSSR ; 
 int SSSR_TFS ; 
 int SSSR_TINT ; 
 int /*<<< orphan*/  handle_bad_msg (struct driver_data*) ; 
 scalar_t__ pm_runtime_suspended (int /*<<< orphan*/ *) ; 
 int pxa2xx_spi_read (struct driver_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pxa2xx_spi_write (struct driver_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct driver_data*) ; 

__attribute__((used)) static irqreturn_t ssp_int(int irq, void *dev_id)
{
	struct driver_data *drv_data = dev_id;
	u32 sccr1_reg;
	u32 mask = drv_data->mask_sr;
	u32 status;

	/*
	 * The IRQ might be shared with other peripherals so we must first
	 * check that are we RPM suspended or not. If we are we assume that
	 * the IRQ was not for us (we shouldn't be RPM suspended when the
	 * interrupt is enabled).
	 */
	if (pm_runtime_suspended(&drv_data->pdev->dev))
		return IRQ_NONE;

	/*
	 * If the device is not yet in RPM suspended state and we get an
	 * interrupt that is meant for another device, check if status bits
	 * are all set to one. That means that the device is already
	 * powered off.
	 */
	status = pxa2xx_spi_read(drv_data, SSSR);
	if (status == ~0)
		return IRQ_NONE;

	sccr1_reg = pxa2xx_spi_read(drv_data, SSCR1);

	/* Ignore possible writes if we don't need to write */
	if (!(sccr1_reg & SSCR1_TIE))
		mask &= ~SSSR_TFS;

	/* Ignore RX timeout interrupt if it is disabled */
	if (!(sccr1_reg & SSCR1_TINTE))
		mask &= ~SSSR_TINT;

	if (!(status & mask))
		return IRQ_NONE;

	pxa2xx_spi_write(drv_data, SSCR1, sccr1_reg & ~drv_data->int_cr1);
	pxa2xx_spi_write(drv_data, SSCR1, sccr1_reg);

	if (!drv_data->controller->cur_msg) {
		handle_bad_msg(drv_data);
		/* Never fail */
		return IRQ_HANDLED;
	}

	return drv_data->transfer_handler(drv_data);
}