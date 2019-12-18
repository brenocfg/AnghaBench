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
struct opt3001 {int use_irq; struct device* dev; int /*<<< orphan*/  result_ready_queue; int /*<<< orphan*/  lock; struct i2c_client* client; } ;
struct TYPE_2__ {struct device* parent; } ;
struct iio_dev {int /*<<< orphan*/ * info; int /*<<< orphan*/  modes; TYPE_1__ dev; int /*<<< orphan*/  num_channels; int /*<<< orphan*/  channels; int /*<<< orphan*/  name; } ;
struct i2c_device_id {int dummy; } ;
struct device {int dummy; } ;
struct i2c_client {int irq; int /*<<< orphan*/  name; struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  INDIO_DIRECT_MODE ; 
 int IRQF_ONESHOT ; 
 int IRQF_TRIGGER_FALLING ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 struct iio_dev* devm_iio_device_alloc (struct device*,int) ; 
 int devm_iio_device_register (struct device*,struct iio_dev*) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct iio_dev*) ; 
 struct opt3001* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  opt3001_channels ; 
 int opt3001_configure (struct opt3001*) ; 
 int /*<<< orphan*/  opt3001_info ; 
 int /*<<< orphan*/  opt3001_irq ; 
 int opt3001_read_id (struct opt3001*) ; 
 int request_threaded_irq (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char*,struct iio_dev*) ; 

__attribute__((used)) static int opt3001_probe(struct i2c_client *client,
		const struct i2c_device_id *id)
{
	struct device *dev = &client->dev;

	struct iio_dev *iio;
	struct opt3001 *opt;
	int irq = client->irq;
	int ret;

	iio = devm_iio_device_alloc(dev, sizeof(*opt));
	if (!iio)
		return -ENOMEM;

	opt = iio_priv(iio);
	opt->client = client;
	opt->dev = dev;

	mutex_init(&opt->lock);
	init_waitqueue_head(&opt->result_ready_queue);
	i2c_set_clientdata(client, iio);

	ret = opt3001_read_id(opt);
	if (ret)
		return ret;

	ret = opt3001_configure(opt);
	if (ret)
		return ret;

	iio->name = client->name;
	iio->channels = opt3001_channels;
	iio->num_channels = ARRAY_SIZE(opt3001_channels);
	iio->dev.parent = dev;
	iio->modes = INDIO_DIRECT_MODE;
	iio->info = &opt3001_info;

	ret = devm_iio_device_register(dev, iio);
	if (ret) {
		dev_err(dev, "failed to register IIO device\n");
		return ret;
	}

	/* Make use of INT pin only if valid IRQ no. is given */
	if (irq > 0) {
		ret = request_threaded_irq(irq, NULL, opt3001_irq,
				IRQF_TRIGGER_FALLING | IRQF_ONESHOT,
				"opt3001", iio);
		if (ret) {
			dev_err(dev, "failed to request IRQ #%d\n", irq);
			return ret;
		}
		opt->use_irq = true;
	} else {
		dev_dbg(opt->dev, "enabling interrupt-less operation\n");
	}

	return 0;
}