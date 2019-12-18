#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct iio_sw_trigger {TYPE_1__* trigger; } ;
struct iio_loop_info {struct iio_sw_trigger swt; } ;
struct TYPE_5__ {int /*<<< orphan*/ * ops; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct iio_sw_trigger* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  iio_loop_trigger_ops ; 
 int /*<<< orphan*/  iio_loop_type ; 
 int /*<<< orphan*/  iio_swt_group_init_type_name (struct iio_sw_trigger*,char const*,int /*<<< orphan*/ *) ; 
 TYPE_1__* iio_trigger_alloc (char*,char const*) ; 
 int /*<<< orphan*/  iio_trigger_free (TYPE_1__*) ; 
 int iio_trigger_register (TYPE_1__*) ; 
 int /*<<< orphan*/  iio_trigger_set_drvdata (TYPE_1__*,struct iio_loop_info*) ; 
 int /*<<< orphan*/  kfree (struct iio_loop_info*) ; 
 struct iio_loop_info* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct iio_sw_trigger *iio_trig_loop_probe(const char *name)
{
	struct iio_loop_info *trig_info;
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
	trig_info->swt.trigger->ops = &iio_loop_trigger_ops;

	ret = iio_trigger_register(trig_info->swt.trigger);
	if (ret)
		goto err_free_trigger;

	iio_swt_group_init_type_name(&trig_info->swt, name, &iio_loop_type);

	return &trig_info->swt;

err_free_trigger:
	iio_trigger_free(trig_info->swt.trigger);
err_free_trig_info:
	kfree(trig_info);

	return ERR_PTR(ret);
}