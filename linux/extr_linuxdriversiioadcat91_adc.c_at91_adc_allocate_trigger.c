#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  parent; } ;
struct iio_trigger {int /*<<< orphan*/ * ops; TYPE_1__ dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  parent; } ;
struct iio_dev {TYPE_2__ dev; int /*<<< orphan*/  id; int /*<<< orphan*/  name; } ;
struct at91_adc_trigger {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  at91_adc_trigger_ops ; 
 struct iio_trigger* iio_trigger_alloc (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int iio_trigger_register (struct iio_trigger*) ; 
 int /*<<< orphan*/  iio_trigger_set_drvdata (struct iio_trigger*,struct iio_dev*) ; 

__attribute__((used)) static struct iio_trigger *at91_adc_allocate_trigger(struct iio_dev *idev,
						     struct at91_adc_trigger *trigger)
{
	struct iio_trigger *trig;
	int ret;

	trig = iio_trigger_alloc("%s-dev%d-%s", idev->name,
				 idev->id, trigger->name);
	if (trig == NULL)
		return NULL;

	trig->dev.parent = idev->dev.parent;
	iio_trigger_set_drvdata(trig, idev);
	trig->ops = &at91_adc_trigger_ops;

	ret = iio_trigger_register(trig);
	if (ret)
		return NULL;

	return trig;
}