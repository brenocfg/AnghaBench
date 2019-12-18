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
struct sx9500_data {int /*<<< orphan*/  mutex; int /*<<< orphan*/  completion; TYPE_1__* client; int /*<<< orphan*/  regmap; } ;
struct iio_dev {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 unsigned int SX9500_CLOSE_IRQ ; 
 unsigned int SX9500_CONVDONE_IRQ ; 
 unsigned int SX9500_FAR_IRQ ; 
 int /*<<< orphan*/  SX9500_REG_IRQ_SRC ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct sx9500_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  sx9500_push_events (struct iio_dev*) ; 

__attribute__((used)) static irqreturn_t sx9500_irq_thread_handler(int irq, void *private)
{
	struct iio_dev *indio_dev = private;
	struct sx9500_data *data = iio_priv(indio_dev);
	int ret;
	unsigned int val;

	mutex_lock(&data->mutex);

	ret = regmap_read(data->regmap, SX9500_REG_IRQ_SRC, &val);
	if (ret < 0) {
		dev_err(&data->client->dev, "i2c transfer error in irq\n");
		goto out;
	}

	if (val & (SX9500_CLOSE_IRQ | SX9500_FAR_IRQ))
		sx9500_push_events(indio_dev);

	if (val & SX9500_CONVDONE_IRQ)
		complete(&data->completion);

out:
	mutex_unlock(&data->mutex);

	return IRQ_HANDLED;
}