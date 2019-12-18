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
struct iio_trigger {int attached_own_device; TYPE_3__ dev; TYPE_1__* ops; int /*<<< orphan*/  name; int /*<<< orphan*/  pool; } ;
struct iio_poll_func {scalar_t__ irq; TYPE_4__* indio_dev; int /*<<< orphan*/  name; int /*<<< orphan*/  type; int /*<<< orphan*/  thread; int /*<<< orphan*/  h; } ;
struct TYPE_6__ {scalar_t__ parent; } ;
struct TYPE_8__ {int /*<<< orphan*/  driver_module; TYPE_2__ dev; } ;
struct TYPE_5__ {int (* set_trigger_state ) (struct iio_trigger*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_IIO_CONSUMERS_PER_TRIGGER ; 
 int /*<<< orphan*/  __module_get (int /*<<< orphan*/ ) ; 
 int bitmap_empty (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (scalar_t__,struct iio_poll_func*) ; 
 scalar_t__ iio_trigger_get_irq (struct iio_trigger*) ; 
 int /*<<< orphan*/  iio_trigger_put_irq (struct iio_trigger*,scalar_t__) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int request_threaded_irq (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct iio_poll_func*) ; 
 int stub1 (struct iio_trigger*,int) ; 

__attribute__((used)) static int iio_trigger_attach_poll_func(struct iio_trigger *trig,
					struct iio_poll_func *pf)
{
	int ret = 0;
	bool notinuse
		= bitmap_empty(trig->pool, CONFIG_IIO_CONSUMERS_PER_TRIGGER);

	/* Prevent the module from being removed whilst attached to a trigger */
	__module_get(pf->indio_dev->driver_module);

	/* Get irq number */
	pf->irq = iio_trigger_get_irq(trig);
	if (pf->irq < 0) {
		pr_err("Could not find an available irq for trigger %s, CONFIG_IIO_CONSUMERS_PER_TRIGGER=%d limit might be exceeded\n",
			trig->name, CONFIG_IIO_CONSUMERS_PER_TRIGGER);
		goto out_put_module;
	}

	/* Request irq */
	ret = request_threaded_irq(pf->irq, pf->h, pf->thread,
				   pf->type, pf->name,
				   pf);
	if (ret < 0)
		goto out_put_irq;

	/* Enable trigger in driver */
	if (trig->ops && trig->ops->set_trigger_state && notinuse) {
		ret = trig->ops->set_trigger_state(trig, true);
		if (ret < 0)
			goto out_free_irq;
	}

	/*
	 * Check if we just registered to our own trigger: we determine that
	 * this is the case if the IIO device and the trigger device share the
	 * same parent device.
	 */
	if (pf->indio_dev->dev.parent == trig->dev.parent)
		trig->attached_own_device = true;

	return ret;

out_free_irq:
	free_irq(pf->irq, pf);
out_put_irq:
	iio_trigger_put_irq(trig, pf->irq);
out_put_module:
	module_put(pf->indio_dev->driver_module);
	return ret;
}