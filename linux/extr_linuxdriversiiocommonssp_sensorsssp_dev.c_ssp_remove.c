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
struct ssp_data {int /*<<< orphan*/  pending_lock; int /*<<< orphan*/  comm_lock; int /*<<< orphan*/  work_wdt; int /*<<< orphan*/  wdt_timer; TYPE_1__* spi; } ;
struct spi_device {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  irq; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  SSP_MSG2SSP_AP_STATUS_SHUTDOWN ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct ssp_data*) ; 
 int /*<<< orphan*/  mfd_remove_devices (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 struct ssp_data* spi_get_drvdata (struct spi_device*) ; 
 int /*<<< orphan*/  ssp_clean_pending_list (struct ssp_data*) ; 
 scalar_t__ ssp_command (struct ssp_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssp_disable_wdt_timer (struct ssp_data*) ; 
 int /*<<< orphan*/  ssp_enable_mcu (struct ssp_data*,int) ; 

__attribute__((used)) static int ssp_remove(struct spi_device *spi)
{
	struct ssp_data *data = spi_get_drvdata(spi);

	if (ssp_command(data, SSP_MSG2SSP_AP_STATUS_SHUTDOWN, 0) < 0)
		dev_err(&data->spi->dev,
			"SSP_MSG2SSP_AP_STATUS_SHUTDOWN failed\n");

	ssp_enable_mcu(data, false);
	ssp_disable_wdt_timer(data);

	ssp_clean_pending_list(data);

	free_irq(data->spi->irq, data);

	del_timer_sync(&data->wdt_timer);
	cancel_work_sync(&data->work_wdt);

	mutex_destroy(&data->comm_lock);
	mutex_destroy(&data->pending_lock);

	mfd_remove_devices(&spi->dev);

	return 0;
}