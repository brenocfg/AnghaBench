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
struct si1145_data {struct iio_trigger* trig; struct i2c_client* client; } ;
struct TYPE_2__ {int /*<<< orphan*/ * parent; } ;
struct iio_trigger {int /*<<< orphan*/ * ops; TYPE_1__ dev; } ;
struct iio_dev {int /*<<< orphan*/  trig; int /*<<< orphan*/  id; int /*<<< orphan*/  name; } ;
struct i2c_client {int /*<<< orphan*/  dev; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  IRQF_TRIGGER_FALLING ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct iio_trigger* devm_iio_trigger_alloc (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int devm_iio_trigger_register (int /*<<< orphan*/ *,struct iio_trigger*) ; 
 int devm_request_irq (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct iio_trigger*) ; 
 struct si1145_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_trigger_generic_data_rdy_poll ; 
 int /*<<< orphan*/  iio_trigger_get (struct iio_trigger*) ; 
 int /*<<< orphan*/  iio_trigger_set_drvdata (struct iio_trigger*,struct iio_dev*) ; 
 int /*<<< orphan*/  si1145_trigger_ops ; 

__attribute__((used)) static int si1145_probe_trigger(struct iio_dev *indio_dev)
{
	struct si1145_data *data = iio_priv(indio_dev);
	struct i2c_client *client = data->client;
	struct iio_trigger *trig;
	int ret;

	trig = devm_iio_trigger_alloc(&client->dev,
			"%s-dev%d", indio_dev->name, indio_dev->id);
	if (!trig)
		return -ENOMEM;

	trig->dev.parent = &client->dev;
	trig->ops = &si1145_trigger_ops;
	iio_trigger_set_drvdata(trig, indio_dev);

	ret = devm_request_irq(&client->dev, client->irq,
			  iio_trigger_generic_data_rdy_poll,
			  IRQF_TRIGGER_FALLING,
			  "si1145_irq",
			  trig);
	if (ret < 0) {
		dev_err(&client->dev, "irq request failed\n");
		return ret;
	}

	ret = devm_iio_trigger_register(&client->dev, trig);
	if (ret)
		return ret;

	data->trig = trig;
	indio_dev->trig = iio_trigger_get(data->trig);

	return 0;
}