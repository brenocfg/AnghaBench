#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  kobj; int /*<<< orphan*/  release; struct device* parent; int /*<<< orphan*/ * class; int /*<<< orphan*/  devt; } ;
struct stm_device {scalar_t__ major; unsigned int sw_nmasters; TYPE_1__ dev; struct stm_data* data; struct module* owner; int /*<<< orphan*/  policy_mutex; int /*<<< orphan*/  mc_lock; int /*<<< orphan*/  link_list; int /*<<< orphan*/  link_lock; int /*<<< orphan*/  link_mutex; } ;
struct stm_data {int sw_end; int sw_start; int /*<<< orphan*/  name; struct stm_device* stm; int /*<<< orphan*/  sw_nchannels; int /*<<< orphan*/  packet; } ;
struct module {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MKDEV (scalar_t__,int /*<<< orphan*/ ) ; 
 int device_add (TYPE_1__*) ; 
 int /*<<< orphan*/  device_initialize (TYPE_1__*) ; 
 int kobject_set_name (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_enable (TYPE_1__*) ; 
 int /*<<< orphan*/  pm_runtime_no_callbacks (TYPE_1__*) ; 
 int /*<<< orphan*/  pm_runtime_set_autosuspend_delay (TYPE_1__*,int) ; 
 int /*<<< orphan*/  pm_runtime_set_suspended (TYPE_1__*) ; 
 int /*<<< orphan*/  pm_runtime_use_autosuspend (TYPE_1__*) ; 
 int /*<<< orphan*/  put_device (TYPE_1__*) ; 
 scalar_t__ register_chrdev (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stm_class ; 
 int /*<<< orphan*/  stm_core_up ; 
 int /*<<< orphan*/  stm_device_release ; 
 int /*<<< orphan*/  stm_fops ; 
 int /*<<< orphan*/  unregister_chrdev (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfree (struct stm_device*) ; 
 struct stm_device* vzalloc (int) ; 

int stm_register_device(struct device *parent, struct stm_data *stm_data,
			struct module *owner)
{
	struct stm_device *stm;
	unsigned int nmasters;
	int err = -ENOMEM;

	if (!stm_core_up)
		return -EPROBE_DEFER;

	if (!stm_data->packet || !stm_data->sw_nchannels)
		return -EINVAL;

	nmasters = stm_data->sw_end - stm_data->sw_start + 1;
	stm = vzalloc(sizeof(*stm) + nmasters * sizeof(void *));
	if (!stm)
		return -ENOMEM;

	stm->major = register_chrdev(0, stm_data->name, &stm_fops);
	if (stm->major < 0)
		goto err_free;

	device_initialize(&stm->dev);
	stm->dev.devt = MKDEV(stm->major, 0);
	stm->dev.class = &stm_class;
	stm->dev.parent = parent;
	stm->dev.release = stm_device_release;

	mutex_init(&stm->link_mutex);
	spin_lock_init(&stm->link_lock);
	INIT_LIST_HEAD(&stm->link_list);

	/* initialize the object before it is accessible via sysfs */
	spin_lock_init(&stm->mc_lock);
	mutex_init(&stm->policy_mutex);
	stm->sw_nmasters = nmasters;
	stm->owner = owner;
	stm->data = stm_data;
	stm_data->stm = stm;

	err = kobject_set_name(&stm->dev.kobj, "%s", stm_data->name);
	if (err)
		goto err_device;

	err = device_add(&stm->dev);
	if (err)
		goto err_device;

	/*
	 * Use delayed autosuspend to avoid bouncing back and forth
	 * on recurring character device writes, with the initial
	 * delay time of 2 seconds.
	 */
	pm_runtime_no_callbacks(&stm->dev);
	pm_runtime_use_autosuspend(&stm->dev);
	pm_runtime_set_autosuspend_delay(&stm->dev, 2000);
	pm_runtime_set_suspended(&stm->dev);
	pm_runtime_enable(&stm->dev);

	return 0;

err_device:
	unregister_chrdev(stm->major, stm_data->name);

	/* matches device_initialize() above */
	put_device(&stm->dev);
err_free:
	vfree(stm);

	return err;
}