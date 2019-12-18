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
struct stm32_lptim_trigger {TYPE_2__* dev; int /*<<< orphan*/  trg; } ;
struct TYPE_4__ {int /*<<< orphan*/  parent; } ;
struct iio_trigger {int /*<<< orphan*/ * ops; TYPE_1__ dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct iio_trigger* devm_iio_trigger_alloc (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 int devm_iio_trigger_register (TYPE_2__*,struct iio_trigger*) ; 
 int /*<<< orphan*/  iio_trigger_set_drvdata (struct iio_trigger*,struct stm32_lptim_trigger*) ; 
 int /*<<< orphan*/  stm32_lptim_trigger_ops ; 

__attribute__((used)) static int stm32_lptim_setup_trig(struct stm32_lptim_trigger *priv)
{
	struct iio_trigger *trig;

	trig = devm_iio_trigger_alloc(priv->dev, "%s", priv->trg);
	if  (!trig)
		return -ENOMEM;

	trig->dev.parent = priv->dev->parent;
	trig->ops = &stm32_lptim_trigger_ops;
	iio_trigger_set_drvdata(trig, priv);

	return devm_iio_trigger_register(priv->dev, trig);
}