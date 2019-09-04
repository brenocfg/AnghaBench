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
typedef  int /*<<< orphan*/  u64 ;
struct iio_dev {int dummy; } ;
struct cm3605 {scalar_t__ dir; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  CM3605_PROX_CHANNEL ; 
 scalar_t__ IIO_EV_DIR_FALLING ; 
 scalar_t__ IIO_EV_DIR_RISING ; 
 int /*<<< orphan*/  IIO_EV_TYPE_THRESH ; 
 int /*<<< orphan*/  IIO_PROXIMITY ; 
 int /*<<< orphan*/  IIO_UNMOD_EVENT_CODE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  iio_get_time_ns (struct iio_dev*) ; 
 struct cm3605* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_push_event (struct iio_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t cm3605_prox_irq(int irq, void *d)
{
	struct iio_dev *indio_dev = d;
	struct cm3605 *cm3605 = iio_priv(indio_dev);
	u64 ev;

	ev = IIO_UNMOD_EVENT_CODE(IIO_PROXIMITY, CM3605_PROX_CHANNEL,
				  IIO_EV_TYPE_THRESH, cm3605->dir);
	iio_push_event(indio_dev, ev, iio_get_time_ns(indio_dev));

	/* Invert the edge for each event */
	if (cm3605->dir == IIO_EV_DIR_RISING)
		cm3605->dir = IIO_EV_DIR_FALLING;
	else
		cm3605->dir = IIO_EV_DIR_RISING;

	return IRQ_HANDLED;
}