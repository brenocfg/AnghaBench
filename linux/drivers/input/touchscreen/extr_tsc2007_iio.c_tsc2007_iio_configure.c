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
struct tsc2007_iio {struct tsc2007* ts; } ;
struct tsc2007 {TYPE_2__* client; } ;
struct TYPE_3__ {int /*<<< orphan*/ * parent; } ;
struct iio_dev {char* name; int /*<<< orphan*/  num_channels; int /*<<< orphan*/  channels; int /*<<< orphan*/  modes; int /*<<< orphan*/ * info; TYPE_1__ dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  INDIO_DIRECT_MODE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 struct iio_dev* devm_iio_device_alloc (int /*<<< orphan*/ *,int) ; 
 int devm_iio_device_register (int /*<<< orphan*/ *,struct iio_dev*) ; 
 struct tsc2007_iio* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  tsc2007_iio_channel ; 
 int /*<<< orphan*/  tsc2007_iio_info ; 

int tsc2007_iio_configure(struct tsc2007 *ts)
{
	struct iio_dev *indio_dev;
	struct tsc2007_iio *iio;
	int error;

	indio_dev = devm_iio_device_alloc(&ts->client->dev, sizeof(*iio));
	if (!indio_dev) {
		dev_err(&ts->client->dev, "iio_device_alloc failed\n");
		return -ENOMEM;
	}

	iio = iio_priv(indio_dev);
	iio->ts = ts;

	indio_dev->name = "tsc2007";
	indio_dev->dev.parent = &ts->client->dev;
	indio_dev->info = &tsc2007_iio_info;
	indio_dev->modes = INDIO_DIRECT_MODE;
	indio_dev->channels = tsc2007_iio_channel;
	indio_dev->num_channels = ARRAY_SIZE(tsc2007_iio_channel);

	error = devm_iio_device_register(&ts->client->dev, indio_dev);
	if (error) {
		dev_err(&ts->client->dev,
			"iio_device_register() failed: %d\n", error);
		return error;
	}

	return 0;
}