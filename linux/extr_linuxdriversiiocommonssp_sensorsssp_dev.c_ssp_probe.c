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
struct ssp_data {scalar_t__ fw_dl_state; int* delay_buf; int time_syncing; int shut_down; int /*<<< orphan*/  comm_lock; int /*<<< orphan*/  pending_lock; struct spi_device* spi; int /*<<< orphan*/  wdt_timer; int /*<<< orphan*/  work_refresh; int /*<<< orphan*/  work_wdt; int /*<<< orphan*/  enable_refcount; int /*<<< orphan*/  pending_list; int /*<<< orphan*/ * check_status; scalar_t__* batch_opt_buf; scalar_t__* batch_latency_buf; } ;
struct spi_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  irq; int /*<<< orphan*/  mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENODEV ; 
 int EPERM ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int IRQF_ONESHOT ; 
 int IRQF_TRIGGER_FALLING ; 
 int /*<<< orphan*/  SPI_MODE_1 ; 
 size_t SSP_BIO_HRM_LIB ; 
 int SSP_DEFAULT_POLLING_DELAY ; 
 scalar_t__ SSP_FW_DL_STATE_NONE ; 
 int /*<<< orphan*/  SSP_INITIALIZATION_STATE ; 
 int SSP_SENSOR_MAX ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  enable_irq_wake (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct ssp_data*) ; 
 int mfd_add_devices (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int request_threaded_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char*,struct ssp_data*) ; 
 int /*<<< orphan*/  sensorhub_sensor_devs ; 
 int /*<<< orphan*/  spi_set_drvdata (struct spi_device*,struct ssp_data*) ; 
 int spi_setup (struct spi_device*) ; 
 scalar_t__ ssp_check_fwbl (struct ssp_data*) ; 
 int ssp_initialize_mcu (struct ssp_data*) ; 
 int /*<<< orphan*/  ssp_irq_thread_fn ; 
 struct ssp_data* ssp_parse_dt (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ssp_refresh_task ; 
 int /*<<< orphan*/  ssp_wdt_timer_func ; 
 int /*<<< orphan*/  ssp_wdt_work_func ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ssp_probe(struct spi_device *spi)
{
	int ret, i;
	struct ssp_data *data;

	data = ssp_parse_dt(&spi->dev);
	if (!data) {
		dev_err(&spi->dev, "Failed to find platform data\n");
		return -ENODEV;
	}

	ret = mfd_add_devices(&spi->dev, -1, sensorhub_sensor_devs,
			      ARRAY_SIZE(sensorhub_sensor_devs), NULL, 0, NULL);
	if (ret < 0) {
		dev_err(&spi->dev, "mfd add devices fail\n");
		return ret;
	}

	spi->mode = SPI_MODE_1;
	ret = spi_setup(spi);
	if (ret < 0) {
		dev_err(&spi->dev, "Failed to setup spi\n");
		return ret;
	}

	data->fw_dl_state = SSP_FW_DL_STATE_NONE;
	data->spi = spi;
	spi_set_drvdata(spi, data);

	mutex_init(&data->comm_lock);

	for (i = 0; i < SSP_SENSOR_MAX; ++i) {
		data->delay_buf[i] = SSP_DEFAULT_POLLING_DELAY;
		data->batch_latency_buf[i] = 0;
		data->batch_opt_buf[i] = 0;
		data->check_status[i] = SSP_INITIALIZATION_STATE;
	}

	data->delay_buf[SSP_BIO_HRM_LIB] = 100;

	data->time_syncing = true;

	mutex_init(&data->pending_lock);
	INIT_LIST_HEAD(&data->pending_list);

	atomic_set(&data->enable_refcount, 0);

	INIT_WORK(&data->work_wdt, ssp_wdt_work_func);
	INIT_DELAYED_WORK(&data->work_refresh, ssp_refresh_task);

	timer_setup(&data->wdt_timer, ssp_wdt_timer_func, 0);

	ret = request_threaded_irq(data->spi->irq, NULL,
				   ssp_irq_thread_fn,
				   IRQF_TRIGGER_FALLING | IRQF_ONESHOT,
				   "SSP_Int", data);
	if (ret < 0) {
		dev_err(&spi->dev, "Irq request fail\n");
		goto err_setup_irq;
	}

	/* Let's start with enabled one so irq balance could be ok */
	data->shut_down = false;

	/* just to avoid unbalanced irq set wake up */
	enable_irq_wake(data->spi->irq);

	data->fw_dl_state = ssp_check_fwbl(data);
	if (data->fw_dl_state == SSP_FW_DL_STATE_NONE) {
		ret = ssp_initialize_mcu(data);
		if (ret < 0) {
			dev_err(&spi->dev, "Initialize_mcu failed\n");
			goto err_read_reg;
		}
	} else {
		dev_err(&spi->dev, "Firmware version not supported\n");
		ret = -EPERM;
		goto err_read_reg;
	}

	return 0;

err_read_reg:
	free_irq(data->spi->irq, data);
err_setup_irq:
	mutex_destroy(&data->pending_lock);
	mutex_destroy(&data->comm_lock);

	dev_err(&spi->dev, "Probe failed!\n");

	return ret;
}