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
struct kmx61_data {TYPE_2__* client; } ;
struct iio_info {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/ * parent; } ;
struct iio_dev {int num_channels; char const* name; struct iio_info const* info; int /*<<< orphan*/  modes; struct iio_chan_spec const* channels; TYPE_1__ dev; } ;
struct iio_chan_spec {int dummy; } ;
typedef  int /*<<< orphan*/  data ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct iio_dev* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INDIO_DIRECT_MODE ; 
 struct iio_dev* devm_iio_device_alloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  kmx61_set_data (struct iio_dev*,struct kmx61_data*) ; 

__attribute__((used)) static struct iio_dev *kmx61_indiodev_setup(struct kmx61_data *data,
					    const struct iio_info *info,
					    const struct iio_chan_spec *chan,
					    int num_channels,
					    const char *name)
{
	struct iio_dev *indio_dev;

	indio_dev = devm_iio_device_alloc(&data->client->dev, sizeof(data));
	if (!indio_dev)
		return ERR_PTR(-ENOMEM);

	kmx61_set_data(indio_dev, data);

	indio_dev->dev.parent = &data->client->dev;
	indio_dev->channels = chan;
	indio_dev->num_channels = num_channels;
	indio_dev->name = name;
	indio_dev->modes = INDIO_DIRECT_MODE;
	indio_dev->info = info;

	return indio_dev;
}