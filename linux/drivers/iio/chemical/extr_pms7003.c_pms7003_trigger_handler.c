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
typedef  int /*<<< orphan*/  u16 ;
struct pms7003_frame {int /*<<< orphan*/  data; } ;
struct pms7003_state {int /*<<< orphan*/  lock; struct pms7003_frame frame; } ;
struct iio_poll_func {struct iio_dev* indio_dev; } ;
struct iio_dev {int /*<<< orphan*/  trig; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_READ_PASSIVE ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 size_t PM1 ; 
 size_t PM10 ; 
 size_t PM2P5 ; 
 int PMS7003_PM10_OFFSET ; 
 int PMS7003_PM1_OFFSET ; 
 int PMS7003_PM2P5_OFFSET ; 
 int /*<<< orphan*/  iio_get_time_ns (struct iio_dev*) ; 
 struct pms7003_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_push_to_buffers_with_timestamp (struct iio_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iio_trigger_notify_done (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int pms7003_do_cmd (struct pms7003_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pms7003_get_pm (int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t pms7003_trigger_handler(int irq, void *p)
{
	struct iio_poll_func *pf = p;
	struct iio_dev *indio_dev = pf->indio_dev;
	struct pms7003_state *state = iio_priv(indio_dev);
	struct pms7003_frame *frame = &state->frame;
	u16 data[3 + 1 + 4]; /* PM1, PM2P5, PM10, padding, timestamp */
	int ret;

	mutex_lock(&state->lock);
	ret = pms7003_do_cmd(state, CMD_READ_PASSIVE);
	if (ret) {
		mutex_unlock(&state->lock);
		goto err;
	}

	data[PM1] = pms7003_get_pm(frame->data + PMS7003_PM1_OFFSET);
	data[PM2P5] = pms7003_get_pm(frame->data + PMS7003_PM2P5_OFFSET);
	data[PM10] = pms7003_get_pm(frame->data + PMS7003_PM10_OFFSET);
	mutex_unlock(&state->lock);

	iio_push_to_buffers_with_timestamp(indio_dev, data,
					   iio_get_time_ns(indio_dev));
err:
	iio_trigger_notify_done(indio_dev->trig);

	return IRQ_HANDLED;
}