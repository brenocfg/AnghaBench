#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct spidev_data {int /*<<< orphan*/  speed_hz; int /*<<< orphan*/  device_entry; int /*<<< orphan*/  devt; int /*<<< orphan*/  buf_lock; int /*<<< orphan*/  spi_lock; struct spi_device* spi; } ;
struct TYPE_5__ {scalar_t__ of_node; } ;
struct spi_device {int /*<<< orphan*/  max_speed_hz; TYPE_2__ dev; int /*<<< orphan*/  chip_select; TYPE_1__* master; } ;
struct device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  bus_num; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MKDEV (int /*<<< orphan*/ ,unsigned long) ; 
 unsigned long N_SPI_MINORS ; 
 int PTR_ERR_OR_ZERO (struct device*) ; 
 int /*<<< orphan*/  SPIDEV_MAJOR ; 
 int /*<<< orphan*/  WARN (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  dev_dbg (TYPE_2__*,char*) ; 
 struct device* device_create (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,struct spidev_data*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_list ; 
 int /*<<< orphan*/  device_list_lock ; 
 unsigned long find_first_zero_bit (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  kfree (struct spidev_data*) ; 
 struct spidev_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  minors ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ of_device_is_compatible (scalar_t__,char*) ; 
 int /*<<< orphan*/  set_bit (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spi_set_drvdata (struct spi_device*,struct spidev_data*) ; 
 int /*<<< orphan*/  spidev_class ; 
 int /*<<< orphan*/  spidev_probe_acpi (struct spi_device*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int spidev_probe(struct spi_device *spi)
{
	struct spidev_data	*spidev;
	int			status;
	unsigned long		minor;

	/*
	 * spidev should never be referenced in DT without a specific
	 * compatible string, it is a Linux implementation thing
	 * rather than a description of the hardware.
	 */
	WARN(spi->dev.of_node &&
	     of_device_is_compatible(spi->dev.of_node, "spidev"),
	     "%pOF: buggy DT: spidev listed directly in DT\n", spi->dev.of_node);

	spidev_probe_acpi(spi);

	/* Allocate driver data */
	spidev = kzalloc(sizeof(*spidev), GFP_KERNEL);
	if (!spidev)
		return -ENOMEM;

	/* Initialize the driver data */
	spidev->spi = spi;
	spin_lock_init(&spidev->spi_lock);
	mutex_init(&spidev->buf_lock);

	INIT_LIST_HEAD(&spidev->device_entry);

	/* If we can allocate a minor number, hook up this device.
	 * Reusing minors is fine so long as udev or mdev is working.
	 */
	mutex_lock(&device_list_lock);
	minor = find_first_zero_bit(minors, N_SPI_MINORS);
	if (minor < N_SPI_MINORS) {
		struct device *dev;

		spidev->devt = MKDEV(SPIDEV_MAJOR, minor);
		dev = device_create(spidev_class, &spi->dev, spidev->devt,
				    spidev, "spidev%d.%d",
				    spi->master->bus_num, spi->chip_select);
		status = PTR_ERR_OR_ZERO(dev);
	} else {
		dev_dbg(&spi->dev, "no minor number available!\n");
		status = -ENODEV;
	}
	if (status == 0) {
		set_bit(minor, minors);
		list_add(&spidev->device_entry, &device_list);
	}
	mutex_unlock(&device_list_lock);

	spidev->speed_hz = spi->max_speed_hz;

	if (status == 0)
		spi_set_drvdata(spi, spidev);
	else
		kfree(spidev);

	return status;
}