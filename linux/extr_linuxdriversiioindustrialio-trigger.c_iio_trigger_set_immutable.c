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
struct iio_trigger {int dummy; } ;
struct iio_dev {int trig_readonly; int /*<<< orphan*/  mlock; int /*<<< orphan*/  trig; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  iio_trigger_get (struct iio_trigger*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int iio_trigger_set_immutable(struct iio_dev *indio_dev, struct iio_trigger *trig)
{
	if (!indio_dev || !trig)
		return -EINVAL;

	mutex_lock(&indio_dev->mlock);
	WARN_ON(indio_dev->trig_readonly);

	indio_dev->trig = iio_trigger_get(trig);
	indio_dev->trig_readonly = true;
	mutex_unlock(&indio_dev->mlock);

	return 0;
}