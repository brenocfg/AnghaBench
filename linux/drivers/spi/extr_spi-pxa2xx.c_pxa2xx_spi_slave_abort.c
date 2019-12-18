#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct spi_controller {int dummy; } ;
struct driver_data {TYPE_3__* controller; TYPE_2__* pdev; int /*<<< orphan*/  clear_sr; } ;
struct TYPE_6__ {TYPE_1__* cur_msg; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINTR ; 
 int /*<<< orphan*/  SSCR0 ; 
 int SSCR0_SSE ; 
 int /*<<< orphan*/  SSTO ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  pxa25x_ssp_comp (struct driver_data*) ; 
 int /*<<< orphan*/  pxa2xx_spi_flush (struct driver_data*) ; 
 int pxa2xx_spi_read (struct driver_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pxa2xx_spi_write (struct driver_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  reset_sccr1 (struct driver_data*) ; 
 struct driver_data* spi_controller_get_devdata (struct spi_controller*) ; 
 int /*<<< orphan*/  spi_finalize_current_transfer (TYPE_3__*) ; 
 int /*<<< orphan*/  write_SSSR_CS (struct driver_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pxa2xx_spi_slave_abort(struct spi_controller *controller)
{
	struct driver_data *drv_data = spi_controller_get_devdata(controller);

	/* Stop and reset SSP */
	write_SSSR_CS(drv_data, drv_data->clear_sr);
	reset_sccr1(drv_data);
	if (!pxa25x_ssp_comp(drv_data))
		pxa2xx_spi_write(drv_data, SSTO, 0);
	pxa2xx_spi_flush(drv_data);
	pxa2xx_spi_write(drv_data, SSCR0,
			 pxa2xx_spi_read(drv_data, SSCR0) & ~SSCR0_SSE);

	dev_dbg(&drv_data->pdev->dev, "transfer aborted\n");

	drv_data->controller->cur_msg->status = -EINTR;
	spi_finalize_current_transfer(drv_data->controller);

	return 0;
}