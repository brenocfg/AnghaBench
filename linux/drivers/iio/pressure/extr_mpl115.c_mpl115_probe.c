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
struct mpl115_ops {int (* init ) (struct device*) ;int (* read ) (struct device*,int /*<<< orphan*/ ) ;} ;
struct mpl115_data {int a0; int b1; int b2; int c12; struct device* dev; struct mpl115_ops const* ops; int /*<<< orphan*/  lock; } ;
struct TYPE_2__ {struct device* parent; } ;
struct iio_dev {char const* name; int /*<<< orphan*/  num_channels; int /*<<< orphan*/  channels; int /*<<< orphan*/  modes; TYPE_1__ dev; int /*<<< orphan*/ * info; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  INDIO_DIRECT_MODE ; 
 int /*<<< orphan*/  MPL115_A0 ; 
 int /*<<< orphan*/  MPL115_B1 ; 
 int /*<<< orphan*/  MPL115_B2 ; 
 int /*<<< orphan*/  MPL115_C12 ; 
 struct iio_dev* devm_iio_device_alloc (struct device*,int) ; 
 int devm_iio_device_register (struct device*,struct iio_dev*) ; 
 struct mpl115_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mpl115_channels ; 
 int /*<<< orphan*/  mpl115_info ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int stub1 (struct device*) ; 
 int stub2 (struct device*,int /*<<< orphan*/ ) ; 
 int stub3 (struct device*,int /*<<< orphan*/ ) ; 
 int stub4 (struct device*,int /*<<< orphan*/ ) ; 
 int stub5 (struct device*,int /*<<< orphan*/ ) ; 

int mpl115_probe(struct device *dev, const char *name,
			const struct mpl115_ops *ops)
{
	struct mpl115_data *data;
	struct iio_dev *indio_dev;
	int ret;

	indio_dev = devm_iio_device_alloc(dev, sizeof(*data));
	if (!indio_dev)
		return -ENOMEM;

	data = iio_priv(indio_dev);
	data->dev = dev;
	data->ops = ops;
	mutex_init(&data->lock);

	indio_dev->info = &mpl115_info;
	indio_dev->name = name;
	indio_dev->dev.parent = dev;
	indio_dev->modes = INDIO_DIRECT_MODE;
	indio_dev->channels = mpl115_channels;
	indio_dev->num_channels = ARRAY_SIZE(mpl115_channels);

	ret = data->ops->init(data->dev);
	if (ret)
		return ret;

	ret = data->ops->read(data->dev, MPL115_A0);
	if (ret < 0)
		return ret;
	data->a0 = ret;
	ret = data->ops->read(data->dev, MPL115_B1);
	if (ret < 0)
		return ret;
	data->b1 = ret;
	ret = data->ops->read(data->dev, MPL115_B2);
	if (ret < 0)
		return ret;
	data->b2 = ret;
	ret = data->ops->read(data->dev, MPL115_C12);
	if (ret < 0)
		return ret;
	data->c12 = ret;

	return devm_iio_device_register(dev, indio_dev);
}