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
struct iio_dummy_state {int /*<<< orphan*/  event_timestamp; int /*<<< orphan*/  event_val; int /*<<< orphan*/  activity_walking; int /*<<< orphan*/  activity_running; TYPE_1__* regs; } ;
struct iio_dev {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int reg_data; int /*<<< orphan*/  reg_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  IIO_ACTIVITY ; 
 int /*<<< orphan*/  IIO_EVENT_CODE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IIO_EV_DIR_FALLING ; 
 int /*<<< orphan*/  IIO_EV_DIR_NONE ; 
 int /*<<< orphan*/  IIO_EV_DIR_RISING ; 
 int /*<<< orphan*/  IIO_EV_TYPE_CHANGE ; 
 int /*<<< orphan*/  IIO_EV_TYPE_THRESH ; 
 int /*<<< orphan*/  IIO_MOD_RUNNING ; 
 int /*<<< orphan*/  IIO_MOD_WALKING ; 
 int /*<<< orphan*/  IIO_NO_MOD ; 
 int /*<<< orphan*/  IIO_STEPS ; 
 int /*<<< orphan*/  IIO_VOLTAGE ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 struct iio_dummy_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_push_event (struct iio_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t iio_simple_dummy_event_handler(int irq, void *private)
{
	struct iio_dev *indio_dev = private;
	struct iio_dummy_state *st = iio_priv(indio_dev);

	dev_dbg(&indio_dev->dev, "id %x event %x\n",
		st->regs->reg_id, st->regs->reg_data);

	switch (st->regs->reg_data) {
	case 0:
		iio_push_event(indio_dev,
			       IIO_EVENT_CODE(IIO_VOLTAGE, 0, 0,
					      IIO_EV_DIR_RISING,
					      IIO_EV_TYPE_THRESH, 0, 0, 0),
			       st->event_timestamp);
		break;
	case 1:
		if (st->activity_running > st->event_val)
			iio_push_event(indio_dev,
				       IIO_EVENT_CODE(IIO_ACTIVITY, 0,
						      IIO_MOD_RUNNING,
						      IIO_EV_DIR_RISING,
						      IIO_EV_TYPE_THRESH,
						      0, 0, 0),
				       st->event_timestamp);
		break;
	case 2:
		if (st->activity_walking < st->event_val)
			iio_push_event(indio_dev,
				       IIO_EVENT_CODE(IIO_ACTIVITY, 0,
						      IIO_MOD_WALKING,
						      IIO_EV_DIR_FALLING,
						      IIO_EV_TYPE_THRESH,
						      0, 0, 0),
				       st->event_timestamp);
		break;
	case 3:
		iio_push_event(indio_dev,
			       IIO_EVENT_CODE(IIO_STEPS, 0, IIO_NO_MOD,
					      IIO_EV_DIR_NONE,
					      IIO_EV_TYPE_CHANGE, 0, 0, 0),
			       st->event_timestamp);
		break;
	default:
		break;
	}

	return IRQ_HANDLED;
}