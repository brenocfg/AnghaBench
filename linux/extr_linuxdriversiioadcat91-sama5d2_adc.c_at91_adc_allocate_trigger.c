#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  parent; } ;
struct iio_trigger {int /*<<< orphan*/ * ops; TYPE_1__ dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  parent; } ;
struct iio_dev {TYPE_2__ dev; int /*<<< orphan*/  id; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 struct iio_trigger* ERR_PTR (int) ; 
 int /*<<< orphan*/  at91_adc_trigger_ops ; 
 struct iio_trigger* devm_iio_trigger_alloc (TYPE_2__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int devm_iio_trigger_register (TYPE_2__*,struct iio_trigger*) ; 
 int /*<<< orphan*/  iio_trigger_set_drvdata (struct iio_trigger*,struct iio_dev*) ; 

__attribute__((used)) static struct iio_trigger *at91_adc_allocate_trigger(struct iio_dev *indio,
						     char *trigger_name)
{
	struct iio_trigger *trig;
	int ret;

	trig = devm_iio_trigger_alloc(&indio->dev, "%s-dev%d-%s", indio->name,
				      indio->id, trigger_name);
	if (!trig)
		return NULL;

	trig->dev.parent = indio->dev.parent;
	iio_trigger_set_drvdata(trig, indio);
	trig->ops = &at91_adc_trigger_ops;

	ret = devm_iio_trigger_register(&indio->dev, trig);
	if (ret)
		return ERR_PTR(ret);

	return trig;
}