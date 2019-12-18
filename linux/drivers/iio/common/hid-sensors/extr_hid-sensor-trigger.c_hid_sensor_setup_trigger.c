#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  parent; } ;
struct iio_trigger {int /*<<< orphan*/ * ops; TYPE_1__ dev; } ;
struct TYPE_7__ {int /*<<< orphan*/  parent; } ;
struct iio_dev {TYPE_3__ dev; int /*<<< orphan*/  trig; int /*<<< orphan*/  id; } ;
struct hid_sensor_common {TYPE_2__* pdev; int /*<<< orphan*/  work; struct iio_trigger* trigger; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  hid_sensor_set_power_work ; 
 int /*<<< orphan*/  hid_sensor_setup_batch_mode (struct iio_dev*,struct hid_sensor_common*) ; 
 int /*<<< orphan*/  hid_sensor_trigger_ops ; 
 int /*<<< orphan*/  iio_device_set_drvdata (struct iio_dev*,struct hid_sensor_common*) ; 
 struct iio_trigger* iio_trigger_alloc (char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iio_trigger_free (struct iio_trigger*) ; 
 int /*<<< orphan*/  iio_trigger_get (struct iio_trigger*) ; 
 int iio_trigger_register (struct iio_trigger*) ; 
 int /*<<< orphan*/  iio_trigger_set_drvdata (struct iio_trigger*,struct hid_sensor_common*) ; 
 int /*<<< orphan*/  iio_trigger_unregister (struct iio_trigger*) ; 
 int pm_runtime_set_active (TYPE_3__*) ; 
 int /*<<< orphan*/  pm_runtime_set_autosuspend_delay (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pm_suspend_ignore_children (int /*<<< orphan*/ *,int) ; 

int hid_sensor_setup_trigger(struct iio_dev *indio_dev, const char *name,
				struct hid_sensor_common *attrb)
{
	int ret;
	struct iio_trigger *trig;

	trig = iio_trigger_alloc("%s-dev%d", name, indio_dev->id);
	if (trig == NULL) {
		dev_err(&indio_dev->dev, "Trigger Allocate Failed\n");
		ret = -ENOMEM;
		goto error_ret;
	}

	trig->dev.parent = indio_dev->dev.parent;
	iio_trigger_set_drvdata(trig, attrb);
	trig->ops = &hid_sensor_trigger_ops;
	ret = iio_trigger_register(trig);

	if (ret) {
		dev_err(&indio_dev->dev, "Trigger Register Failed\n");
		goto error_free_trig;
	}
	attrb->trigger = trig;
	indio_dev->trig = iio_trigger_get(trig);

	hid_sensor_setup_batch_mode(indio_dev, attrb);

	ret = pm_runtime_set_active(&indio_dev->dev);
	if (ret)
		goto error_unreg_trigger;

	iio_device_set_drvdata(indio_dev, attrb);

	INIT_WORK(&attrb->work, hid_sensor_set_power_work);

	pm_suspend_ignore_children(&attrb->pdev->dev, true);
	/* Default to 3 seconds, but can be changed from sysfs */
	pm_runtime_set_autosuspend_delay(&attrb->pdev->dev,
					 3000);
	return ret;
error_unreg_trigger:
	iio_trigger_unregister(trig);
error_free_trig:
	iio_trigger_free(trig);
error_ret:
	return ret;
}