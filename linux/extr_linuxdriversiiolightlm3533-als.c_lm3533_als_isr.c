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
typedef  int /*<<< orphan*/  u8 ;
struct lm3533_als {int /*<<< orphan*/  zone; } ;
struct iio_dev {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IIO_EV_DIR_EITHER ; 
 int /*<<< orphan*/  IIO_EV_TYPE_THRESH ; 
 int /*<<< orphan*/  IIO_LIGHT ; 
 int /*<<< orphan*/  IIO_UNMOD_EVENT_CODE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int _lm3533_als_get_zone (struct iio_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iio_get_time_ns (struct iio_dev*) ; 
 struct lm3533_als* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_push_event (struct iio_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t lm3533_als_isr(int irq, void *dev_id)
{

	struct iio_dev *indio_dev = dev_id;
	struct lm3533_als *als = iio_priv(indio_dev);
	u8 zone;
	int ret;

	/* Clear interrupt by reading the ALS zone register. */
	ret = _lm3533_als_get_zone(indio_dev, &zone);
	if (ret)
		goto out;

	atomic_set(&als->zone, zone);

	iio_push_event(indio_dev,
		       IIO_UNMOD_EVENT_CODE(IIO_LIGHT,
					    0,
					    IIO_EV_TYPE_THRESH,
					    IIO_EV_DIR_EITHER),
		       iio_get_time_ns(indio_dev));
out:
	return IRQ_HANDLED;
}