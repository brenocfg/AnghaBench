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
struct iio_dev {int /*<<< orphan*/  name; } ;
struct iio_chan_spec {scalar_t__ type; } ;
struct dht11 {scalar_t__ timestamp; int num_edges; int temperature; int humidity; int /*<<< orphan*/  lock; int /*<<< orphan*/  dev; int /*<<< orphan*/  irq; int /*<<< orphan*/  completion; int /*<<< orphan*/  gpiod; } ;

/* Variables and functions */
 int DHT11_AMBIG_HIGH ; 
 int DHT11_AMBIG_LOW ; 
 scalar_t__ DHT11_DATA_VALID_TIME ; 
 int DHT11_EDGES_PER_READ ; 
 int DHT11_EDGES_PREAMBLE ; 
 int DHT11_MIN_TIMERES ; 
 int /*<<< orphan*/  DHT11_START_TRANSMISSION_MAX ; 
 int /*<<< orphan*/  DHT11_START_TRANSMISSION_MIN ; 
 int EAGAIN ; 
 int EINVAL ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  HZ ; 
 scalar_t__ IIO_HUMIDITYRELATIVE ; 
 scalar_t__ IIO_TEMP ; 
 int IIO_VAL_INT ; 
 int IRQF_TRIGGER_FALLING ; 
 int IRQF_TRIGGER_RISING ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int) ; 
 int dht11_decode (struct dht11*,int) ; 
 int /*<<< orphan*/  dht11_edges_print (struct dht11*) ; 
 int /*<<< orphan*/  dht11_handle_irq ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct iio_dev*) ; 
 int gpiod_direction_input (int /*<<< orphan*/ ) ; 
 int gpiod_direction_output (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct dht11* iio_priv (struct iio_dev*) ; 
 scalar_t__ ktime_get_boottime_ns () ; 
 int ktime_get_resolution_ns () ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct iio_dev*) ; 
 int /*<<< orphan*/  usleep_range (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int wait_for_completion_killable_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dht11_read_raw(struct iio_dev *iio_dev,
			  const struct iio_chan_spec *chan,
			int *val, int *val2, long m)
{
	struct dht11 *dht11 = iio_priv(iio_dev);
	int ret, timeres, offset;

	mutex_lock(&dht11->lock);
	if (dht11->timestamp + DHT11_DATA_VALID_TIME < ktime_get_boottime_ns()) {
		timeres = ktime_get_resolution_ns();
		dev_dbg(dht11->dev, "current timeresolution: %dns\n", timeres);
		if (timeres > DHT11_MIN_TIMERES) {
			dev_err(dht11->dev, "timeresolution %dns too low\n",
				timeres);
			/* In theory a better clock could become available
			 * at some point ... and there is no error code
			 * that really fits better.
			 */
			ret = -EAGAIN;
			goto err;
		}
		if (timeres > DHT11_AMBIG_LOW && timeres < DHT11_AMBIG_HIGH)
			dev_warn(dht11->dev,
				 "timeresolution: %dns - decoding ambiguous\n",
				 timeres);

		reinit_completion(&dht11->completion);

		dht11->num_edges = 0;
		ret = gpiod_direction_output(dht11->gpiod, 0);
		if (ret)
			goto err;
		usleep_range(DHT11_START_TRANSMISSION_MIN,
			     DHT11_START_TRANSMISSION_MAX);
		ret = gpiod_direction_input(dht11->gpiod);
		if (ret)
			goto err;

		ret = request_irq(dht11->irq, dht11_handle_irq,
				  IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING,
				  iio_dev->name, iio_dev);
		if (ret)
			goto err;

		ret = wait_for_completion_killable_timeout(&dht11->completion,
							   HZ);

		free_irq(dht11->irq, iio_dev);

#ifdef CONFIG_DYNAMIC_DEBUG
		dht11_edges_print(dht11);
#endif

		if (ret == 0 && dht11->num_edges < DHT11_EDGES_PER_READ - 1) {
			dev_err(dht11->dev, "Only %d signal edges detected\n",
				dht11->num_edges);
			ret = -ETIMEDOUT;
		}
		if (ret < 0)
			goto err;

		offset = DHT11_EDGES_PREAMBLE +
				dht11->num_edges - DHT11_EDGES_PER_READ;
		for (; offset >= 0; --offset) {
			ret = dht11_decode(dht11, offset);
			if (!ret)
				break;
		}

		if (ret)
			goto err;
	}

	ret = IIO_VAL_INT;
	if (chan->type == IIO_TEMP)
		*val = dht11->temperature;
	else if (chan->type == IIO_HUMIDITYRELATIVE)
		*val = dht11->humidity;
	else
		ret = -EINVAL;
err:
	dht11->num_edges = -1;
	mutex_unlock(&dht11->lock);
	return ret;
}