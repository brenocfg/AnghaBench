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
struct mxs_lradc_adc {struct iio_trigger* trig; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct iio_trigger {int /*<<< orphan*/ * ops; TYPE_1__ dev; } ;
struct iio_dev {int /*<<< orphan*/  id; int /*<<< orphan*/  name; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct iio_trigger* devm_iio_trigger_alloc (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mxs_lradc_adc* iio_priv (struct iio_dev*) ; 
 int iio_trigger_register (struct iio_trigger*) ; 
 int /*<<< orphan*/  iio_trigger_set_drvdata (struct iio_trigger*,struct iio_dev*) ; 
 int /*<<< orphan*/  mxs_lradc_adc_trigger_ops ; 

__attribute__((used)) static int mxs_lradc_adc_trigger_init(struct iio_dev *iio)
{
	int ret;
	struct iio_trigger *trig;
	struct mxs_lradc_adc *adc = iio_priv(iio);

	trig = devm_iio_trigger_alloc(&iio->dev, "%s-dev%i", iio->name,
				      iio->id);
	if (!trig)
		return -ENOMEM;

	trig->dev.parent = adc->dev;
	iio_trigger_set_drvdata(trig, iio);
	trig->ops = &mxs_lradc_adc_trigger_ops;

	ret = iio_trigger_register(trig);
	if (ret)
		return ret;

	adc->trig = trig;

	return 0;
}