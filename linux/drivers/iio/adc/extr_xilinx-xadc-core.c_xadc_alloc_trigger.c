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

/* Variables and functions */
 int ENOMEM ; 
 struct iio_trigger* ERR_PTR (int) ; 
 int /*<<< orphan*/  iio_priv (struct iio_dev*) ; 
 struct iio_trigger* iio_trigger_alloc (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  iio_trigger_free (struct iio_trigger*) ; 
 int iio_trigger_register (struct iio_trigger*) ; 
 int /*<<< orphan*/  iio_trigger_set_drvdata (struct iio_trigger*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xadc_trigger_ops ; 

__attribute__((used)) static struct iio_trigger *xadc_alloc_trigger(struct iio_dev *indio_dev,
	const char *name)
{
	struct iio_trigger *trig;
	int ret;

	trig = iio_trigger_alloc("%s%d-%s", indio_dev->name,
				indio_dev->id, name);
	if (trig == NULL)
		return ERR_PTR(-ENOMEM);

	trig->dev.parent = indio_dev->dev.parent;
	trig->ops = &xadc_trigger_ops;
	iio_trigger_set_drvdata(trig, iio_priv(indio_dev));

	ret = iio_trigger_register(trig);
	if (ret)
		goto error_free_trig;

	return trig;

error_free_trig:
	iio_trigger_free(trig);
	return ERR_PTR(ret);
}