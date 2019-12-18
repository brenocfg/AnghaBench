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
struct iio_sw_device {struct iio_dev* device; } ;
struct iio_dummy_state {int /*<<< orphan*/  lock; } ;
struct iio_dev {int /*<<< orphan*/  modes; int /*<<< orphan*/ * info; int /*<<< orphan*/  num_channels; int /*<<< orphan*/  channels; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 struct iio_sw_device* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INDIO_DIRECT_MODE ; 
 struct iio_dev* iio_device_alloc (int) ; 
 int /*<<< orphan*/  iio_device_free (struct iio_dev*) ; 
 int iio_device_register (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_dummy_channels ; 
 int /*<<< orphan*/  iio_dummy_info ; 
 int /*<<< orphan*/  iio_dummy_init_device (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_dummy_type ; 
 struct iio_dummy_state* iio_priv (struct iio_dev*) ; 
 int iio_simple_dummy_configure_buffer (struct iio_dev*) ; 
 int iio_simple_dummy_events_register (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_simple_dummy_events_unregister (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_simple_dummy_unconfigure_buffer (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_swd_group_init_type_name (struct iio_sw_device*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct iio_sw_device*) ; 
 int /*<<< orphan*/  kstrdup (char const*,int /*<<< orphan*/ ) ; 
 struct iio_sw_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct iio_sw_device *iio_dummy_probe(const char *name)
{
	int ret;
	struct iio_dev *indio_dev;
	struct iio_dummy_state *st;
	struct iio_sw_device *swd;

	swd = kzalloc(sizeof(*swd), GFP_KERNEL);
	if (!swd) {
		ret = -ENOMEM;
		goto error_kzalloc;
	}
	/*
	 * Allocate an IIO device.
	 *
	 * This structure contains all generic state
	 * information about the device instance.
	 * It also has a region (accessed by iio_priv()
	 * for chip specific state information.
	 */
	indio_dev = iio_device_alloc(sizeof(*st));
	if (!indio_dev) {
		ret = -ENOMEM;
		goto error_ret;
	}

	st = iio_priv(indio_dev);
	mutex_init(&st->lock);

	iio_dummy_init_device(indio_dev);
	/*
	 * With hardware: Set the parent device.
	 * indio_dev->dev.parent = &spi->dev;
	 * indio_dev->dev.parent = &client->dev;
	 */

	 /*
	 * Make the iio_dev struct available to remove function.
	 * Bus equivalents
	 * i2c_set_clientdata(client, indio_dev);
	 * spi_set_drvdata(spi, indio_dev);
	 */
	swd->device = indio_dev;

	/*
	 * Set the device name.
	 *
	 * This is typically a part number and obtained from the module
	 * id table.
	 * e.g. for i2c and spi:
	 *    indio_dev->name = id->name;
	 *    indio_dev->name = spi_get_device_id(spi)->name;
	 */
	indio_dev->name = kstrdup(name, GFP_KERNEL);

	/* Provide description of available channels */
	indio_dev->channels = iio_dummy_channels;
	indio_dev->num_channels = ARRAY_SIZE(iio_dummy_channels);

	/*
	 * Provide device type specific interface functions and
	 * constant data.
	 */
	indio_dev->info = &iio_dummy_info;

	/* Specify that device provides sysfs type interfaces */
	indio_dev->modes = INDIO_DIRECT_MODE;

	ret = iio_simple_dummy_events_register(indio_dev);
	if (ret < 0)
		goto error_free_device;

	ret = iio_simple_dummy_configure_buffer(indio_dev);
	if (ret < 0)
		goto error_unregister_events;

	ret = iio_device_register(indio_dev);
	if (ret < 0)
		goto error_unconfigure_buffer;

	iio_swd_group_init_type_name(swd, name, &iio_dummy_type);

	return swd;
error_unconfigure_buffer:
	iio_simple_dummy_unconfigure_buffer(indio_dev);
error_unregister_events:
	iio_simple_dummy_events_unregister(indio_dev);
error_free_device:
	iio_device_free(indio_dev);
error_ret:
	kfree(swd);
error_kzalloc:
	return ERR_PTR(ret);
}