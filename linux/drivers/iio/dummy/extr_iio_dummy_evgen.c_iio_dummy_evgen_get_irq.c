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
struct TYPE_2__ {int* inuse; int /*<<< orphan*/  lock; int /*<<< orphan*/  irq_sim; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int IIO_EVENTGEN_NO ; 
 TYPE_1__* iio_evgen ; 
 int irq_sim_irqnum (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int iio_dummy_evgen_get_irq(void)
{
	int i, ret = 0;

	if (!iio_evgen)
		return -ENODEV;

	mutex_lock(&iio_evgen->lock);
	for (i = 0; i < IIO_EVENTGEN_NO; i++) {
		if (!iio_evgen->inuse[i]) {
			ret = irq_sim_irqnum(&iio_evgen->irq_sim, i);
			iio_evgen->inuse[i] = true;
			break;
		}
	}
	mutex_unlock(&iio_evgen->lock);
	if (i == IIO_EVENTGEN_NO)
		return -ENOMEM;

	return ret;
}