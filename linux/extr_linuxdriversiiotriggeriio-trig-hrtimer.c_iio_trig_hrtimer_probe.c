#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_6__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct iio_sw_trigger {TYPE_2__* trigger; } ;
struct TYPE_9__ {int /*<<< orphan*/  function; } ;
struct iio_hrtimer_info {int sampling_frequency; int period; struct iio_sw_trigger swt; TYPE_6__ timer; } ;
struct TYPE_7__ {int /*<<< orphan*/  groups; } ;
struct TYPE_8__ {TYPE_1__ dev; int /*<<< orphan*/ * ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 int ENOMEM ; 
 struct iio_sw_trigger* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HRTIMER_DEFAULT_SAMPLING_FREQUENCY ; 
 int /*<<< orphan*/  HRTIMER_MODE_REL ; 
 int NSEC_PER_SEC ; 
 int /*<<< orphan*/  hrtimer_init (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iio_hrtimer_attr_groups ; 
 int /*<<< orphan*/  iio_hrtimer_trig_handler ; 
 int /*<<< orphan*/  iio_hrtimer_trigger_ops ; 
 int /*<<< orphan*/  iio_hrtimer_type ; 
 int /*<<< orphan*/  iio_swt_group_init_type_name (struct iio_sw_trigger*,char const*,int /*<<< orphan*/ *) ; 
 TYPE_2__* iio_trigger_alloc (char*,char const*) ; 
 int /*<<< orphan*/  iio_trigger_free (TYPE_2__*) ; 
 int iio_trigger_register (TYPE_2__*) ; 
 int /*<<< orphan*/  iio_trigger_set_drvdata (TYPE_2__*,struct iio_hrtimer_info*) ; 
 int /*<<< orphan*/  kfree (struct iio_hrtimer_info*) ; 
 struct iio_hrtimer_info* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct iio_sw_trigger *iio_trig_hrtimer_probe(const char *name)
{
	struct iio_hrtimer_info *trig_info;
	int ret;

	trig_info = kzalloc(sizeof(*trig_info), GFP_KERNEL);
	if (!trig_info)
		return ERR_PTR(-ENOMEM);

	trig_info->swt.trigger = iio_trigger_alloc("%s", name);
	if (!trig_info->swt.trigger) {
		ret = -ENOMEM;
		goto err_free_trig_info;
	}

	iio_trigger_set_drvdata(trig_info->swt.trigger, trig_info);
	trig_info->swt.trigger->ops = &iio_hrtimer_trigger_ops;
	trig_info->swt.trigger->dev.groups = iio_hrtimer_attr_groups;

	hrtimer_init(&trig_info->timer, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
	trig_info->timer.function = iio_hrtimer_trig_handler;

	trig_info->sampling_frequency = HRTIMER_DEFAULT_SAMPLING_FREQUENCY;
	trig_info->period = NSEC_PER_SEC / trig_info->sampling_frequency;

	ret = iio_trigger_register(trig_info->swt.trigger);
	if (ret)
		goto err_free_trigger;

	iio_swt_group_init_type_name(&trig_info->swt, name, &iio_hrtimer_type);
	return &trig_info->swt;
err_free_trigger:
	iio_trigger_free(trig_info->swt.trigger);
err_free_trig_info:
	kfree(trig_info);

	return ERR_PTR(ret);
}