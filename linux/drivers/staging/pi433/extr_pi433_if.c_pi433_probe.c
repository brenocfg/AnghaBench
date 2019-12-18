#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct spi_device {int mode; int bits_per_word; int /*<<< orphan*/  dev; int /*<<< orphan*/  max_speed_hz; } ;
struct pi433_device {int rx_active; int tx_active; int interrupt_rx_allowed; struct pi433_device* rx_buffer; int /*<<< orphan*/  devt; int /*<<< orphan*/ * tx_task_struct; TYPE_1__* cdev; int /*<<< orphan*/ * dev; int /*<<< orphan*/  minor; int /*<<< orphan*/  rx_lock; int /*<<< orphan*/  tx_fifo_lock; int /*<<< orphan*/  tx_fifo; int /*<<< orphan*/  fifo_wait_queue; int /*<<< orphan*/  rx_wait_queue; int /*<<< orphan*/  tx_wait_queue; struct spi_device* spi; } ;
struct TYPE_5__ {int /*<<< orphan*/  owner; } ;

/* Variables and functions */
 int /*<<< orphan*/  DATAMODUL_MODE_PACKET ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_KFIFO (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MAJOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MASK_PALEVEL_PA0 ; 
 int /*<<< orphan*/  MASK_PALEVEL_PA1 ; 
 int /*<<< orphan*/  MASK_PALEVEL_PA2 ; 
 int /*<<< orphan*/  MAX_MSG_SIZE ; 
 int /*<<< orphan*/  MKDEV (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int cdev_add (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* cdev_alloc () ; 
 int /*<<< orphan*/  cdev_del (TYPE_1__*) ; 
 int /*<<< orphan*/  cdev_init (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/ * device_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct pi433_device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fifty_ohm ; 
 int /*<<< orphan*/  free_gpio (struct pi433_device*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct pi433_device*) ; 
 struct pi433_device* kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * kthread_run (int /*<<< orphan*/ ,struct pi433_device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kthread_stop (int /*<<< orphan*/ *) ; 
 struct pi433_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pi433_class ; 
 int /*<<< orphan*/  pi433_dev ; 
 int /*<<< orphan*/  pi433_fops ; 
 int /*<<< orphan*/  pi433_free_minor (struct pi433_device*) ; 
 int pi433_get_minor (struct pi433_device*) ; 
 int /*<<< orphan*/  pi433_tx_thread ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int rf69_disable_amplifier (struct spi_device*,int /*<<< orphan*/ ) ; 
 int rf69_enable_amplifier (struct spi_device*,int /*<<< orphan*/ ) ; 
 int rf69_set_antenna_impedance (struct spi_device*,int /*<<< orphan*/ ) ; 
 int rf69_set_data_mode (struct spi_device*,int /*<<< orphan*/ ) ; 
 int rf69_set_mode (struct spi_device*,int /*<<< orphan*/ ) ; 
 int rf69_set_output_power_level (struct spi_device*,int) ; 
 int setup_gpio (struct pi433_device*) ; 
 int /*<<< orphan*/  spi_set_drvdata (struct spi_device*,struct pi433_device*) ; 
 int spi_setup (struct spi_device*) ; 
 int spi_w8r8 (struct spi_device*,int) ; 
 int /*<<< orphan*/  standby ; 

__attribute__((used)) static int pi433_probe(struct spi_device *spi)
{
	struct pi433_device	*device;
	int			retval;

	/* setup spi parameters */
	spi->mode = 0x00;
	spi->bits_per_word = 8;
	/*
	 * spi->max_speed_hz = 10000000;
	 * 1MHz already set by device tree overlay
	 */

	retval = spi_setup(spi);
	if (retval) {
		dev_dbg(&spi->dev, "configuration of SPI interface failed!\n");
		return retval;
	}

	dev_dbg(&spi->dev,
		"spi interface setup: mode 0x%2x, %d bits per word, %dhz max speed",
		spi->mode, spi->bits_per_word, spi->max_speed_hz);

	/* Ping the chip by reading the version register */
	retval = spi_w8r8(spi, 0x10);
	if (retval < 0)
		return retval;

	switch (retval) {
	case 0x24:
		dev_dbg(&spi->dev, "found pi433 (ver. 0x%x)", retval);
		break;
	default:
		dev_dbg(&spi->dev, "unknown chip version: 0x%x", retval);
		return -ENODEV;
	}

	/* Allocate driver data */
	device = kzalloc(sizeof(*device), GFP_KERNEL);
	if (!device)
		return -ENOMEM;

	/* Initialize the driver data */
	device->spi = spi;
	device->rx_active = false;
	device->tx_active = false;
	device->interrupt_rx_allowed = false;

	/* init rx buffer */
	device->rx_buffer = kmalloc(MAX_MSG_SIZE, GFP_KERNEL);
	if (!device->rx_buffer) {
		retval = -ENOMEM;
		goto RX_failed;
	}

	/* init wait queues */
	init_waitqueue_head(&device->tx_wait_queue);
	init_waitqueue_head(&device->rx_wait_queue);
	init_waitqueue_head(&device->fifo_wait_queue);

	/* init fifo */
	INIT_KFIFO(device->tx_fifo);

	/* init mutexes and locks */
	mutex_init(&device->tx_fifo_lock);
	mutex_init(&device->rx_lock);

	/* setup GPIO (including irq_handler) for the different DIOs */
	retval = setup_gpio(device);
	if (retval) {
		dev_dbg(&spi->dev, "setup of GPIOs failed");
		goto GPIO_failed;
	}

	/* setup the radio module */
	retval = rf69_set_mode(spi, standby);
	if (retval < 0)
		goto minor_failed;
	retval = rf69_set_data_mode(spi, DATAMODUL_MODE_PACKET);
	if (retval < 0)
		goto minor_failed;
	retval = rf69_enable_amplifier(spi, MASK_PALEVEL_PA0);
	if (retval < 0)
		goto minor_failed;
	retval = rf69_disable_amplifier(spi, MASK_PALEVEL_PA1);
	if (retval < 0)
		goto minor_failed;
	retval = rf69_disable_amplifier(spi, MASK_PALEVEL_PA2);
	if (retval < 0)
		goto minor_failed;
	retval = rf69_set_output_power_level(spi, 13);
	if (retval < 0)
		goto minor_failed;
	retval = rf69_set_antenna_impedance(spi, fifty_ohm);
	if (retval < 0)
		goto minor_failed;

	/* determ minor number */
	retval = pi433_get_minor(device);
	if (retval) {
		dev_dbg(&spi->dev, "get of minor number failed");
		goto minor_failed;
	}

	/* create device */
	device->devt = MKDEV(MAJOR(pi433_dev), device->minor);
	device->dev = device_create(pi433_class,
				    &spi->dev,
				    device->devt,
				    device,
				    "pi433.%d",
				    device->minor);
	if (IS_ERR(device->dev)) {
		pr_err("pi433: device register failed\n");
		retval = PTR_ERR(device->dev);
		goto device_create_failed;
	} else {
		dev_dbg(device->dev,
			"created device for major %d, minor %d\n",
			MAJOR(pi433_dev),
			device->minor);
	}

	/* start tx thread */
	device->tx_task_struct = kthread_run(pi433_tx_thread,
					     device,
					     "pi433.%d_tx_task",
					     device->minor);
	if (IS_ERR(device->tx_task_struct)) {
		dev_dbg(device->dev, "start of send thread failed");
		retval = PTR_ERR(device->tx_task_struct);
		goto send_thread_failed;
	}

	/* create cdev */
	device->cdev = cdev_alloc();
	if (!device->cdev) {
		dev_dbg(device->dev, "allocation of cdev failed");
		goto cdev_failed;
	}
	device->cdev->owner = THIS_MODULE;
	cdev_init(device->cdev, &pi433_fops);
	retval = cdev_add(device->cdev, device->devt, 1);
	if (retval) {
		dev_dbg(device->dev, "register of cdev failed");
		goto del_cdev;
	}

	/* spi setup */
	spi_set_drvdata(spi, device);

	return 0;

del_cdev:
	cdev_del(device->cdev);
cdev_failed:
	kthread_stop(device->tx_task_struct);
send_thread_failed:
	device_destroy(pi433_class, device->devt);
device_create_failed:
	pi433_free_minor(device);
minor_failed:
	free_gpio(device);
GPIO_failed:
	kfree(device->rx_buffer);
RX_failed:
	kfree(device);

	return retval;
}