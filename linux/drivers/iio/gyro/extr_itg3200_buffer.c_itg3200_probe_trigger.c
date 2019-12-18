#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct itg3200 {TYPE_3__* trig; TYPE_2__* i2c; } ;
struct iio_dev {int /*<<< orphan*/  trig; int /*<<< orphan*/  id; int /*<<< orphan*/  name; } ;
struct TYPE_10__ {int /*<<< orphan*/ * parent; } ;
struct TYPE_12__ {int /*<<< orphan*/ * ops; TYPE_1__ dev; } ;
struct TYPE_11__ {int /*<<< orphan*/  irq; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  IRQF_TRIGGER_RISING ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,TYPE_3__*) ; 
 struct itg3200* iio_priv (struct iio_dev*) ; 
 TYPE_3__* iio_trigger_alloc (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iio_trigger_free (TYPE_3__*) ; 
 int /*<<< orphan*/  iio_trigger_generic_data_rdy_poll ; 
 int /*<<< orphan*/  iio_trigger_get (TYPE_3__*) ; 
 int iio_trigger_register (TYPE_3__*) ; 
 int /*<<< orphan*/  iio_trigger_set_drvdata (TYPE_3__*,struct iio_dev*) ; 
 int /*<<< orphan*/  itg3200_trigger_ops ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,TYPE_3__*) ; 

int itg3200_probe_trigger(struct iio_dev *indio_dev)
{
	int ret;
	struct itg3200 *st = iio_priv(indio_dev);

	st->trig = iio_trigger_alloc("%s-dev%d", indio_dev->name,
				     indio_dev->id);
	if (!st->trig)
		return -ENOMEM;

	ret = request_irq(st->i2c->irq,
			  &iio_trigger_generic_data_rdy_poll,
			  IRQF_TRIGGER_RISING,
			  "itg3200_data_rdy",
			  st->trig);
	if (ret)
		goto error_free_trig;


	st->trig->dev.parent = &st->i2c->dev;
	st->trig->ops = &itg3200_trigger_ops;
	iio_trigger_set_drvdata(st->trig, indio_dev);
	ret = iio_trigger_register(st->trig);
	if (ret)
		goto error_free_irq;

	/* select default trigger */
	indio_dev->trig = iio_trigger_get(st->trig);

	return 0;

error_free_irq:
	free_irq(st->i2c->irq, st->trig);
error_free_trig:
	iio_trigger_free(st->trig);
	return ret;
}