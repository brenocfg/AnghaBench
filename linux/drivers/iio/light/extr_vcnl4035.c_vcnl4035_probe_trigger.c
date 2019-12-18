#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct vcnl4035_data {TYPE_3__* client; TYPE_4__* drdy_trigger0; } ;
struct TYPE_8__ {int /*<<< orphan*/  parent; } ;
struct iio_dev {TYPE_2__ dev; int /*<<< orphan*/  id; int /*<<< orphan*/  name; } ;
struct TYPE_7__ {int /*<<< orphan*/  parent; } ;
struct TYPE_10__ {int /*<<< orphan*/ * ops; TYPE_1__ dev; } ;
struct TYPE_9__ {int /*<<< orphan*/  irq; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int IRQF_ONESHOT ; 
 int IRQF_TRIGGER_LOW ; 
 int /*<<< orphan*/  VCNL4035_IRQ_NAME ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 TYPE_4__* devm_iio_trigger_alloc (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int devm_iio_trigger_register (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int devm_iio_triggered_buffer_setup (int /*<<< orphan*/ ,struct iio_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int devm_request_threaded_irq (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct iio_dev*) ; 
 struct vcnl4035_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_trigger_set_drvdata (TYPE_4__*,struct iio_dev*) ; 
 int /*<<< orphan*/  iio_triggered_buffer_setup_ops ; 
 int /*<<< orphan*/  vcnl4035_drdy_irq_thread ; 
 int /*<<< orphan*/  vcnl4035_trigger_consumer_handler ; 
 int /*<<< orphan*/  vcnl4035_trigger_ops ; 

__attribute__((used)) static int vcnl4035_probe_trigger(struct iio_dev *indio_dev)
{
	int ret;
	struct vcnl4035_data *data = iio_priv(indio_dev);

	data->drdy_trigger0 = devm_iio_trigger_alloc(
			indio_dev->dev.parent,
			"%s-dev%d", indio_dev->name, indio_dev->id);
	if (!data->drdy_trigger0)
		return -ENOMEM;

	data->drdy_trigger0->dev.parent = indio_dev->dev.parent;
	data->drdy_trigger0->ops = &vcnl4035_trigger_ops;
	iio_trigger_set_drvdata(data->drdy_trigger0, indio_dev);
	ret = devm_iio_trigger_register(indio_dev->dev.parent,
					data->drdy_trigger0);
	if (ret) {
		dev_err(&data->client->dev, "iio trigger register failed\n");
		return ret;
	}

	/* Trigger setup */
	ret = devm_iio_triggered_buffer_setup(indio_dev->dev.parent, indio_dev,
					NULL, vcnl4035_trigger_consumer_handler,
					&iio_triggered_buffer_setup_ops);
	if (ret < 0) {
		dev_err(&data->client->dev, "iio triggered buffer setup failed\n");
		return ret;
	}

	/* IRQ to trigger mapping */
	ret = devm_request_threaded_irq(&data->client->dev, data->client->irq,
			NULL, vcnl4035_drdy_irq_thread,
			IRQF_TRIGGER_LOW | IRQF_ONESHOT,
			VCNL4035_IRQ_NAME, indio_dev);
	if (ret < 0)
		dev_err(&data->client->dev, "request irq %d for trigger0 failed\n",
				data->client->irq);
	return ret;
}