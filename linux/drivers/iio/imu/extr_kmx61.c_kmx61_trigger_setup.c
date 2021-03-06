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
struct kmx61_data {TYPE_2__* client; } ;
struct TYPE_3__ {int /*<<< orphan*/ * parent; } ;
struct iio_trigger {int /*<<< orphan*/ * ops; TYPE_1__ dev; } ;
struct iio_dev {int /*<<< orphan*/  id; int /*<<< orphan*/  name; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct iio_trigger* ERR_PTR (int) ; 
 struct iio_trigger* devm_iio_trigger_alloc (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int iio_trigger_register (struct iio_trigger*) ; 
 int /*<<< orphan*/  iio_trigger_set_drvdata (struct iio_trigger*,struct iio_dev*) ; 
 int /*<<< orphan*/  kmx61_trigger_ops ; 

__attribute__((used)) static struct iio_trigger *kmx61_trigger_setup(struct kmx61_data *data,
					       struct iio_dev *indio_dev,
					       const char *tag)
{
	struct iio_trigger *trig;
	int ret;

	trig = devm_iio_trigger_alloc(&data->client->dev,
				      "%s-%s-dev%d",
				      indio_dev->name,
				      tag,
				      indio_dev->id);
	if (!trig)
		return ERR_PTR(-ENOMEM);

	trig->dev.parent = &data->client->dev;
	trig->ops = &kmx61_trigger_ops;
	iio_trigger_set_drvdata(trig, indio_dev);

	ret = iio_trigger_register(trig);
	if (ret)
		return ERR_PTR(ret);

	return trig;
}