#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct inv_mpu6050_state {TYPE_2__* trig; int /*<<< orphan*/  map; int /*<<< orphan*/  irq; } ;
struct iio_dev {int /*<<< orphan*/  trig; int /*<<< orphan*/  dev; int /*<<< orphan*/  id; int /*<<< orphan*/  name; } ;
struct TYPE_7__ {int /*<<< orphan*/  parent; } ;
struct TYPE_8__ {int /*<<< orphan*/ * ops; TYPE_1__ dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 TYPE_2__* devm_iio_trigger_alloc (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int devm_iio_trigger_register (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int devm_request_irq (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,char*,TYPE_2__*) ; 
 struct inv_mpu6050_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_trigger_generic_data_rdy_poll ; 
 int /*<<< orphan*/  iio_trigger_get (TYPE_2__*) ; 
 int /*<<< orphan*/  iio_trigger_set_drvdata (TYPE_2__*,struct iio_dev*) ; 
 int /*<<< orphan*/  inv_mpu_trigger_ops ; 
 int /*<<< orphan*/  regmap_get_device (int /*<<< orphan*/ ) ; 

int inv_mpu6050_probe_trigger(struct iio_dev *indio_dev, int irq_type)
{
	int ret;
	struct inv_mpu6050_state *st = iio_priv(indio_dev);

	st->trig = devm_iio_trigger_alloc(&indio_dev->dev,
					  "%s-dev%d",
					  indio_dev->name,
					  indio_dev->id);
	if (!st->trig)
		return -ENOMEM;

	ret = devm_request_irq(&indio_dev->dev, st->irq,
			       &iio_trigger_generic_data_rdy_poll,
			       irq_type,
			       "inv_mpu",
			       st->trig);
	if (ret)
		return ret;

	st->trig->dev.parent = regmap_get_device(st->map);
	st->trig->ops = &inv_mpu_trigger_ops;
	iio_trigger_set_drvdata(st->trig, indio_dev);

	ret = devm_iio_trigger_register(&indio_dev->dev, st->trig);
	if (ret)
		return ret;

	indio_dev->trig = iio_trigger_get(st->trig);

	return 0;
}