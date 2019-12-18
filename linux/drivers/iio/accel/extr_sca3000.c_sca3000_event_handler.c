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
struct sca3000_state {int* rx; int /*<<< orphan*/  lock; } ;
struct iio_dev {int dummy; } ;
typedef  int /*<<< orphan*/  s64 ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IIO_ACCEL ; 
 int /*<<< orphan*/  IIO_EV_DIR_FALLING ; 
 int /*<<< orphan*/  IIO_EV_DIR_RISING ; 
 int /*<<< orphan*/  IIO_EV_TYPE_MAG ; 
 int /*<<< orphan*/  IIO_MOD_EVENT_CODE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IIO_MOD_X ; 
 int /*<<< orphan*/  IIO_MOD_X_AND_Y_AND_Z ; 
 int /*<<< orphan*/  IIO_MOD_Y ; 
 int /*<<< orphan*/  IIO_MOD_Z ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int SCA3000_INT_STATUS_FREE_FALL ; 
 int SCA3000_INT_STATUS_X_TRIGGER ; 
 int SCA3000_INT_STATUS_Y_TRIGGER ; 
 int SCA3000_INT_STATUS_Z_TRIGGER ; 
 int /*<<< orphan*/  SCA3000_REG_INT_STATUS_ADDR ; 
 int /*<<< orphan*/  iio_get_time_ns (struct iio_dev*) ; 
 struct sca3000_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_push_event (struct iio_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int sca3000_read_data_short (struct sca3000_state*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sca3000_ring_int_process (int,struct iio_dev*) ; 

__attribute__((used)) static irqreturn_t sca3000_event_handler(int irq, void *private)
{
	struct iio_dev *indio_dev = private;
	struct sca3000_state *st = iio_priv(indio_dev);
	int ret, val;
	s64 last_timestamp = iio_get_time_ns(indio_dev);

	/*
	 * Could lead if badly timed to an extra read of status reg,
	 * but ensures no interrupt is missed.
	 */
	mutex_lock(&st->lock);
	ret = sca3000_read_data_short(st, SCA3000_REG_INT_STATUS_ADDR, 1);
	val = st->rx[0];
	mutex_unlock(&st->lock);
	if (ret)
		goto done;

	sca3000_ring_int_process(val, indio_dev);

	if (val & SCA3000_INT_STATUS_FREE_FALL)
		iio_push_event(indio_dev,
			       IIO_MOD_EVENT_CODE(IIO_ACCEL,
						  0,
						  IIO_MOD_X_AND_Y_AND_Z,
						  IIO_EV_TYPE_MAG,
						  IIO_EV_DIR_FALLING),
			       last_timestamp);

	if (val & SCA3000_INT_STATUS_Y_TRIGGER)
		iio_push_event(indio_dev,
			       IIO_MOD_EVENT_CODE(IIO_ACCEL,
						  0,
						  IIO_MOD_Y,
						  IIO_EV_TYPE_MAG,
						  IIO_EV_DIR_RISING),
			       last_timestamp);

	if (val & SCA3000_INT_STATUS_X_TRIGGER)
		iio_push_event(indio_dev,
			       IIO_MOD_EVENT_CODE(IIO_ACCEL,
						  0,
						  IIO_MOD_X,
						  IIO_EV_TYPE_MAG,
						  IIO_EV_DIR_RISING),
			       last_timestamp);

	if (val & SCA3000_INT_STATUS_Z_TRIGGER)
		iio_push_event(indio_dev,
			       IIO_MOD_EVENT_CODE(IIO_ACCEL,
						  0,
						  IIO_MOD_Z,
						  IIO_EV_TYPE_MAG,
						  IIO_EV_DIR_RISING),
			       last_timestamp);

done:
	return IRQ_HANDLED;
}