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
struct zpa2326_private {struct iio_trigger* trigger; } ;
struct TYPE_2__ {struct device* parent; } ;
struct iio_trigger {int /*<<< orphan*/ * ops; TYPE_1__ dev; } ;
struct iio_dev {int /*<<< orphan*/  id; int /*<<< orphan*/  name; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 struct iio_trigger* devm_iio_trigger_alloc (struct device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int devm_iio_trigger_register (struct device*,struct iio_trigger*) ; 
 int /*<<< orphan*/  zpa2326_trigger_ops ; 

__attribute__((used)) static int zpa2326_init_managed_trigger(struct device          *parent,
					struct iio_dev         *indio_dev,
					struct zpa2326_private *private,
					int                     irq)
{
	struct iio_trigger *trigger;
	int                 ret;

	if (irq <= 0)
		return 0;

	trigger = devm_iio_trigger_alloc(parent, "%s-dev%d",
					 indio_dev->name, indio_dev->id);
	if (!trigger)
		return -ENOMEM;

	/* Basic setup. */
	trigger->dev.parent = parent;
	trigger->ops = &zpa2326_trigger_ops;

	private->trigger = trigger;

	/* Register to triggers space. */
	ret = devm_iio_trigger_register(parent, trigger);
	if (ret)
		dev_err(parent, "failed to register hardware trigger (%d)",
			ret);

	return ret;
}