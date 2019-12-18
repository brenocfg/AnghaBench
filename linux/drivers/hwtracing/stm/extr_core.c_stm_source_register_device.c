#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  kobj; int /*<<< orphan*/  release; struct device* parent; int /*<<< orphan*/ * class; } ;
struct stm_source_device {TYPE_1__ dev; struct stm_source_data* data; int /*<<< orphan*/  link_entry; int /*<<< orphan*/  link_lock; int /*<<< orphan*/  output; } ;
struct stm_source_data {struct stm_source_device* src; int /*<<< orphan*/  name; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int device_add (TYPE_1__*) ; 
 int /*<<< orphan*/  device_initialize (TYPE_1__*) ; 
 int kobject_set_name (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 struct stm_source_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_forbid (TYPE_1__*) ; 
 int /*<<< orphan*/  pm_runtime_no_callbacks (TYPE_1__*) ; 
 int /*<<< orphan*/  put_device (TYPE_1__*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stm_core_up ; 
 int /*<<< orphan*/  stm_output_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stm_source_class ; 
 int /*<<< orphan*/  stm_source_device_release ; 

int stm_source_register_device(struct device *parent,
			       struct stm_source_data *data)
{
	struct stm_source_device *src;
	int err;

	if (!stm_core_up)
		return -EPROBE_DEFER;

	src = kzalloc(sizeof(*src), GFP_KERNEL);
	if (!src)
		return -ENOMEM;

	device_initialize(&src->dev);
	src->dev.class = &stm_source_class;
	src->dev.parent = parent;
	src->dev.release = stm_source_device_release;

	err = kobject_set_name(&src->dev.kobj, "%s", data->name);
	if (err)
		goto err;

	pm_runtime_no_callbacks(&src->dev);
	pm_runtime_forbid(&src->dev);

	err = device_add(&src->dev);
	if (err)
		goto err;

	stm_output_init(&src->output);
	spin_lock_init(&src->link_lock);
	INIT_LIST_HEAD(&src->link_entry);
	src->data = data;
	data->src = src;

	return 0;

err:
	put_device(&src->dev);

	return err;
}