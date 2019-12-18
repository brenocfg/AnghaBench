#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ parent; } ;
struct iio_trigger {int attached_own_device; TYPE_3__ dev; TYPE_1__* ops; int /*<<< orphan*/  pool; } ;
struct iio_poll_func {TYPE_4__* indio_dev; int /*<<< orphan*/  irq; } ;
struct TYPE_6__ {scalar_t__ parent; } ;
struct TYPE_8__ {int /*<<< orphan*/  driver_module; TYPE_2__ dev; } ;
struct TYPE_5__ {int (* set_trigger_state ) (struct iio_trigger*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_IIO_CONSUMERS_PER_TRIGGER ; 
 int bitmap_weight (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct iio_poll_func*) ; 
 int /*<<< orphan*/  iio_trigger_put_irq (struct iio_trigger*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int stub1 (struct iio_trigger*,int) ; 

__attribute__((used)) static int iio_trigger_detach_poll_func(struct iio_trigger *trig,
					 struct iio_poll_func *pf)
{
	int ret = 0;
	bool no_other_users
		= (bitmap_weight(trig->pool,
				 CONFIG_IIO_CONSUMERS_PER_TRIGGER)
		   == 1);
	if (trig->ops && trig->ops->set_trigger_state && no_other_users) {
		ret = trig->ops->set_trigger_state(trig, false);
		if (ret)
			return ret;
	}
	if (pf->indio_dev->dev.parent == trig->dev.parent)
		trig->attached_own_device = false;
	iio_trigger_put_irq(trig, pf->irq);
	free_irq(pf->irq, pf);
	module_put(pf->indio_dev->driver_module);

	return ret;
}