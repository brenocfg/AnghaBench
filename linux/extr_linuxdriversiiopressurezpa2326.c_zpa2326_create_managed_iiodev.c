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
struct zpa2326_private {int dummy; } ;
struct regmap {int dummy; } ;
struct TYPE_2__ {struct device* parent; } ;
struct iio_dev {char const* name; int /*<<< orphan*/ * info; int /*<<< orphan*/  num_channels; int /*<<< orphan*/  channels; TYPE_1__ dev; int /*<<< orphan*/  modes; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INDIO_DIRECT_MODE ; 
 struct iio_dev* devm_iio_device_alloc (struct device*,int) ; 
 int /*<<< orphan*/  zpa2326_channels ; 
 int /*<<< orphan*/  zpa2326_info ; 

__attribute__((used)) static struct iio_dev *zpa2326_create_managed_iiodev(struct device *device,
						     const char    *name,
						     struct regmap *regmap)
{
	struct iio_dev *indio_dev;

	/* Allocate space to hold IIO device internal state. */
	indio_dev = devm_iio_device_alloc(device,
					  sizeof(struct zpa2326_private));
	if (!indio_dev)
		return NULL;

	/* Setup for userspace synchronous on demand sampling. */
	indio_dev->modes = INDIO_DIRECT_MODE;
	indio_dev->dev.parent = device;
	indio_dev->channels = zpa2326_channels;
	indio_dev->num_channels = ARRAY_SIZE(zpa2326_channels);
	indio_dev->name = name;
	indio_dev->info = &zpa2326_info;

	return indio_dev;
}