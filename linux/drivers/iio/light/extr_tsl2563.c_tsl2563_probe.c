#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct tsl2563_platform_data {int cover_comp_gain; } ;
struct tsl2563_chip {int low_thres; int high_thres; int cover_comp_gain; int /*<<< orphan*/  poweroff_work; void* calib1; void* calib0; int /*<<< orphan*/  intr; int /*<<< orphan*/  gainlevel; int /*<<< orphan*/  lock; struct i2c_client* client; } ;
struct TYPE_6__ {TYPE_2__* parent; } ;
struct iio_dev {int /*<<< orphan*/ * info; int /*<<< orphan*/  modes; TYPE_1__ dev; int /*<<< orphan*/  num_channels; int /*<<< orphan*/  channels; int /*<<< orphan*/  name; } ;
struct i2c_device_id {int dummy; } ;
struct TYPE_7__ {struct device_node* of_node; struct tsl2563_platform_data* platform_data; } ;
struct i2c_client {TYPE_2__ dev; scalar_t__ irq; int /*<<< orphan*/  name; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CALIB_BASE_SYSFS ; 
 int ENOMEM ; 
 int HZ ; 
 int /*<<< orphan*/  INDIO_DIRECT_MODE ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int IRQF_ONESHOT ; 
 int IRQF_TRIGGER_RISING ; 
 int /*<<< orphan*/  TSL2563_INT_PERSIST (int) ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*,int) ; 
 int /*<<< orphan*/  dev_info (TYPE_2__*,char*,int,int) ; 
 struct iio_dev* devm_iio_device_alloc (TYPE_2__*,int) ; 
 int devm_request_threaded_irq (TYPE_2__*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,char*,struct iio_dev*) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct tsl2563_chip*) ; 
 int iio_device_register (struct iio_dev*) ; 
 struct tsl2563_chip* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_property_read_u32 (struct device_node*,char*,int*) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int) ; 
 void* tsl2563_calib_from_sysfs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tsl2563_channels ; 
 int tsl2563_configure (struct tsl2563_chip*) ; 
 int tsl2563_detect (struct tsl2563_chip*) ; 
 int /*<<< orphan*/  tsl2563_event_handler ; 
 int /*<<< orphan*/  tsl2563_gainlevel_table ; 
 int /*<<< orphan*/  tsl2563_info ; 
 int /*<<< orphan*/  tsl2563_info_no_irq ; 
 int /*<<< orphan*/  tsl2563_poweroff_work ; 
 int tsl2563_read_id (struct tsl2563_chip*,int*) ; 

__attribute__((used)) static int tsl2563_probe(struct i2c_client *client,
				const struct i2c_device_id *device_id)
{
	struct iio_dev *indio_dev;
	struct tsl2563_chip *chip;
	struct tsl2563_platform_data *pdata = client->dev.platform_data;
	struct device_node *np = client->dev.of_node;
	int err = 0;
	u8 id = 0;

	indio_dev = devm_iio_device_alloc(&client->dev, sizeof(*chip));
	if (!indio_dev)
		return -ENOMEM;

	chip = iio_priv(indio_dev);

	i2c_set_clientdata(client, chip);
	chip->client = client;

	err = tsl2563_detect(chip);
	if (err) {
		dev_err(&client->dev, "detect error %d\n", -err);
		return err;
	}

	err = tsl2563_read_id(chip, &id);
	if (err) {
		dev_err(&client->dev, "read id error %d\n", -err);
		return err;
	}

	mutex_init(&chip->lock);

	/* Default values used until userspace says otherwise */
	chip->low_thres = 0x0;
	chip->high_thres = 0xffff;
	chip->gainlevel = tsl2563_gainlevel_table;
	chip->intr = TSL2563_INT_PERSIST(4);
	chip->calib0 = tsl2563_calib_from_sysfs(CALIB_BASE_SYSFS);
	chip->calib1 = tsl2563_calib_from_sysfs(CALIB_BASE_SYSFS);

	if (pdata)
		chip->cover_comp_gain = pdata->cover_comp_gain;
	else if (np)
		of_property_read_u32(np, "amstaos,cover-comp-gain",
				     &chip->cover_comp_gain);
	else
		chip->cover_comp_gain = 1;

	dev_info(&client->dev, "model %d, rev. %d\n", id >> 4, id & 0x0f);
	indio_dev->name = client->name;
	indio_dev->channels = tsl2563_channels;
	indio_dev->num_channels = ARRAY_SIZE(tsl2563_channels);
	indio_dev->dev.parent = &client->dev;
	indio_dev->modes = INDIO_DIRECT_MODE;

	if (client->irq)
		indio_dev->info = &tsl2563_info;
	else
		indio_dev->info = &tsl2563_info_no_irq;

	if (client->irq) {
		err = devm_request_threaded_irq(&client->dev, client->irq,
					   NULL,
					   &tsl2563_event_handler,
					   IRQF_TRIGGER_RISING | IRQF_ONESHOT,
					   "tsl2563_event",
					   indio_dev);
		if (err) {
			dev_err(&client->dev, "irq request error %d\n", -err);
			return err;
		}
	}

	err = tsl2563_configure(chip);
	if (err) {
		dev_err(&client->dev, "configure error %d\n", -err);
		return err;
	}

	INIT_DELAYED_WORK(&chip->poweroff_work, tsl2563_poweroff_work);

	/* The interrupt cannot yet be enabled so this is fine without lock */
	schedule_delayed_work(&chip->poweroff_work, 5 * HZ);

	err = iio_device_register(indio_dev);
	if (err) {
		dev_err(&client->dev, "iio registration error %d\n", -err);
		goto fail;
	}

	return 0;

fail:
	cancel_delayed_work_sync(&chip->poweroff_work);
	return err;
}