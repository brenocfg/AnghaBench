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
struct iio_poll_func {int /*<<< orphan*/  timestamp; struct iio_dev* indio_dev; } ;
struct iio_dev {int masklength; int /*<<< orphan*/  trig; TYPE_1__* channels; int /*<<< orphan*/  active_scan_mask; } ;
struct hx711_data {int /*<<< orphan*/  lock; int /*<<< orphan*/ * buffer; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  channel; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  hx711_reset_read (struct hx711_data*,int /*<<< orphan*/ ) ; 
 struct hx711_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_push_to_buffers_with_timestamp (struct iio_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iio_trigger_notify_done (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t hx711_trigger(int irq, void *p)
{
	struct iio_poll_func *pf = p;
	struct iio_dev *indio_dev = pf->indio_dev;
	struct hx711_data *hx711_data = iio_priv(indio_dev);
	int i, j = 0;

	mutex_lock(&hx711_data->lock);

	memset(hx711_data->buffer, 0, sizeof(hx711_data->buffer));

	for (i = 0; i < indio_dev->masklength; i++) {
		if (!test_bit(i, indio_dev->active_scan_mask))
			continue;

		hx711_data->buffer[j] = hx711_reset_read(hx711_data,
					indio_dev->channels[i].channel);
		j++;
	}

	iio_push_to_buffers_with_timestamp(indio_dev, hx711_data->buffer,
							pf->timestamp);

	mutex_unlock(&hx711_data->lock);

	iio_trigger_notify_done(indio_dev->trig);

	return IRQ_HANDLED;
}