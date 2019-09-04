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
struct mpu3050 {int /*<<< orphan*/  hw_timestamp; int /*<<< orphan*/  hw_irq_trigger; } ;
struct iio_trigger {int dummy; } ;
struct iio_dev {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  IRQ_WAKE_THREAD ; 
 int /*<<< orphan*/  iio_get_time_ns (struct iio_dev*) ; 
 struct mpu3050* iio_priv (struct iio_dev*) ; 
 struct iio_dev* iio_trigger_get_drvdata (struct iio_trigger*) ; 

__attribute__((used)) static irqreturn_t mpu3050_irq_handler(int irq, void *p)
{
	struct iio_trigger *trig = p;
	struct iio_dev *indio_dev = iio_trigger_get_drvdata(trig);
	struct mpu3050 *mpu3050 = iio_priv(indio_dev);

	if (!mpu3050->hw_irq_trigger)
		return IRQ_NONE;

	/* Get the time stamp as close in time as possible */
	mpu3050->hw_timestamp = iio_get_time_ns(indio_dev);

	return IRQ_WAKE_THREAD;
}