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
typedef  int u16 ;
struct max44000_data {int /*<<< orphan*/  lock; int /*<<< orphan*/  regmap; } ;
struct iio_poll_func {struct iio_dev* indio_dev; } ;
struct iio_dev {int /*<<< orphan*/  trig; int /*<<< orphan*/  active_scan_mask; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  MAX44000_REG_PRX_DATA ; 
 int /*<<< orphan*/  MAX44000_SCAN_INDEX_ALS ; 
 int /*<<< orphan*/  MAX44000_SCAN_INDEX_PRX ; 
 int /*<<< orphan*/  iio_get_time_ns (struct iio_dev*) ; 
 struct max44000_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_push_to_buffers_with_timestamp (struct iio_dev*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iio_trigger_notify_done (int /*<<< orphan*/ ) ; 
 int max44000_read_alsval (struct max44000_data*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t max44000_trigger_handler(int irq, void *p)
{
	struct iio_poll_func *pf = p;
	struct iio_dev *indio_dev = pf->indio_dev;
	struct max44000_data *data = iio_priv(indio_dev);
	u16 buf[8]; /* 2x u16 + padding + 8 bytes timestamp */
	int index = 0;
	unsigned int regval;
	int ret;

	mutex_lock(&data->lock);
	if (test_bit(MAX44000_SCAN_INDEX_ALS, indio_dev->active_scan_mask)) {
		ret = max44000_read_alsval(data);
		if (ret < 0)
			goto out_unlock;
		buf[index++] = ret;
	}
	if (test_bit(MAX44000_SCAN_INDEX_PRX, indio_dev->active_scan_mask)) {
		ret = regmap_read(data->regmap, MAX44000_REG_PRX_DATA, &regval);
		if (ret < 0)
			goto out_unlock;
		buf[index] = regval;
	}
	mutex_unlock(&data->lock);

	iio_push_to_buffers_with_timestamp(indio_dev, buf,
					   iio_get_time_ns(indio_dev));
	iio_trigger_notify_done(indio_dev->trig);
	return IRQ_HANDLED;

out_unlock:
	mutex_unlock(&data->lock);
	iio_trigger_notify_done(indio_dev->trig);
	return IRQ_HANDLED;
}