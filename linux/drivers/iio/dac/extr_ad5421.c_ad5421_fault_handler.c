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
struct iio_dev {int dummy; } ;
struct ad5421_state {unsigned int fault_mask; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 unsigned int AD5421_FAULT_OVER_CURRENT ; 
 unsigned int AD5421_FAULT_TEMP_OVER_140 ; 
 unsigned int AD5421_FAULT_TRIGGER_IRQ ; 
 unsigned int AD5421_FAULT_UNDER_CURRENT ; 
 int /*<<< orphan*/  AD5421_REG_FAULT ; 
 int /*<<< orphan*/  IIO_CURRENT ; 
 int /*<<< orphan*/  IIO_EV_DIR_FALLING ; 
 int /*<<< orphan*/  IIO_EV_DIR_RISING ; 
 int /*<<< orphan*/  IIO_EV_TYPE_MAG ; 
 int /*<<< orphan*/  IIO_EV_TYPE_THRESH ; 
 int /*<<< orphan*/  IIO_TEMP ; 
 int /*<<< orphan*/  IIO_UNMOD_EVENT_CODE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 unsigned int ad5421_read (struct iio_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ad5421_update_ctrl (struct iio_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iio_get_time_ns (struct iio_dev*) ; 
 struct ad5421_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_push_event (struct iio_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static irqreturn_t ad5421_fault_handler(int irq, void *data)
{
	struct iio_dev *indio_dev = data;
	struct ad5421_state *st = iio_priv(indio_dev);
	unsigned int fault;
	unsigned int old_fault = 0;
	unsigned int events;

	fault = ad5421_read(indio_dev, AD5421_REG_FAULT);
	if (!fault)
		return IRQ_NONE;

	/* If we had a fault, this might mean that the DAC has lost its state
	 * and has been reset. Make sure that the control register actually
	 * contains what we expect it to contain. Otherwise the watchdog might
	 * be enabled and we get watchdog timeout faults, which will render the
	 * DAC unusable. */
	ad5421_update_ctrl(indio_dev, 0, 0);


	/* The fault pin stays high as long as a fault condition is present and
	 * it is not possible to mask fault conditions. For certain fault
	 * conditions for example like over-temperature it takes some time
	 * until the fault condition disappears. If we would exit the interrupt
	 * handler immediately after handling the event it would be entered
	 * again instantly. Thus we fall back to polling in case we detect that
	 * a interrupt condition is still present.
	 */
	do {
		/* 0xffff is a invalid value for the register and will only be
		 * read if there has been a communication error */
		if (fault == 0xffff)
			fault = 0;

		/* we are only interested in new events */
		events = (old_fault ^ fault) & fault;
		events &= st->fault_mask;

		if (events & AD5421_FAULT_OVER_CURRENT) {
			iio_push_event(indio_dev,
				IIO_UNMOD_EVENT_CODE(IIO_CURRENT,
					0,
					IIO_EV_TYPE_THRESH,
					IIO_EV_DIR_RISING),
			iio_get_time_ns(indio_dev));
		}

		if (events & AD5421_FAULT_UNDER_CURRENT) {
			iio_push_event(indio_dev,
				IIO_UNMOD_EVENT_CODE(IIO_CURRENT,
					0,
					IIO_EV_TYPE_THRESH,
					IIO_EV_DIR_FALLING),
				iio_get_time_ns(indio_dev));
		}

		if (events & AD5421_FAULT_TEMP_OVER_140) {
			iio_push_event(indio_dev,
				IIO_UNMOD_EVENT_CODE(IIO_TEMP,
					0,
					IIO_EV_TYPE_MAG,
					IIO_EV_DIR_RISING),
				iio_get_time_ns(indio_dev));
		}

		old_fault = fault;
		fault = ad5421_read(indio_dev, AD5421_REG_FAULT);

		/* still active? go to sleep for some time */
		if (fault & AD5421_FAULT_TRIGGER_IRQ)
			msleep(1000);

	} while (fault & AD5421_FAULT_TRIGGER_IRQ);


	return IRQ_HANDLED;
}