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
struct device {int dummy; } ;
struct backlight_properties {scalar_t__ type; } ;
struct backlight_ops {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  release; struct device* parent; int /*<<< orphan*/  class; } ;
struct TYPE_8__ {void* type; } ;
struct backlight_device {int /*<<< orphan*/  entry; struct backlight_ops const* ops; TYPE_1__ dev; TYPE_2__ props; int /*<<< orphan*/  ops_lock; int /*<<< orphan*/  update_lock; } ;

/* Variables and functions */
 void* BACKLIGHT_RAW ; 
 int /*<<< orphan*/  BACKLIGHT_REGISTERED ; 
 scalar_t__ BACKLIGHT_TYPE_MAX ; 
 int ENOMEM ; 
 struct backlight_device* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  WARN (int,char*,char const*) ; 
 int /*<<< orphan*/  backlight_class ; 
 int /*<<< orphan*/  backlight_dev_list ; 
 int /*<<< orphan*/  backlight_dev_list_mutex ; 
 int /*<<< orphan*/  backlight_notifier ; 
 int backlight_register_fb (struct backlight_device*) ; 
 int /*<<< orphan*/  bl_device_release ; 
 int /*<<< orphan*/  blocking_notifier_call_chain (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct backlight_device*) ; 
 int /*<<< orphan*/  dev_set_drvdata (TYPE_1__*,void*) ; 
 int /*<<< orphan*/  dev_set_name (TYPE_1__*,char*,char const*) ; 
 int device_register (TYPE_1__*) ; 
 int /*<<< orphan*/  device_unregister (TYPE_1__*) ; 
 struct backlight_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (TYPE_2__*,struct backlight_properties const*,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct backlight_device* pmac_backlight ; 
 int /*<<< orphan*/  pmac_backlight_mutex ; 
 int /*<<< orphan*/  pr_debug (char*,char const*) ; 
 int /*<<< orphan*/  put_device (TYPE_1__*) ; 

struct backlight_device *backlight_device_register(const char *name,
	struct device *parent, void *devdata, const struct backlight_ops *ops,
	const struct backlight_properties *props)
{
	struct backlight_device *new_bd;
	int rc;

	pr_debug("backlight_device_register: name=%s\n", name);

	new_bd = kzalloc(sizeof(struct backlight_device), GFP_KERNEL);
	if (!new_bd)
		return ERR_PTR(-ENOMEM);

	mutex_init(&new_bd->update_lock);
	mutex_init(&new_bd->ops_lock);

	new_bd->dev.class = backlight_class;
	new_bd->dev.parent = parent;
	new_bd->dev.release = bl_device_release;
	dev_set_name(&new_bd->dev, "%s", name);
	dev_set_drvdata(&new_bd->dev, devdata);

	/* Set default properties */
	if (props) {
		memcpy(&new_bd->props, props,
		       sizeof(struct backlight_properties));
		if (props->type <= 0 || props->type >= BACKLIGHT_TYPE_MAX) {
			WARN(1, "%s: invalid backlight type", name);
			new_bd->props.type = BACKLIGHT_RAW;
		}
	} else {
		new_bd->props.type = BACKLIGHT_RAW;
	}

	rc = device_register(&new_bd->dev);
	if (rc) {
		put_device(&new_bd->dev);
		return ERR_PTR(rc);
	}

	rc = backlight_register_fb(new_bd);
	if (rc) {
		device_unregister(&new_bd->dev);
		return ERR_PTR(rc);
	}

	new_bd->ops = ops;

#ifdef CONFIG_PMAC_BACKLIGHT
	mutex_lock(&pmac_backlight_mutex);
	if (!pmac_backlight)
		pmac_backlight = new_bd;
	mutex_unlock(&pmac_backlight_mutex);
#endif

	mutex_lock(&backlight_dev_list_mutex);
	list_add(&new_bd->entry, &backlight_dev_list);
	mutex_unlock(&backlight_dev_list_mutex);

	blocking_notifier_call_chain(&backlight_notifier,
				     BACKLIGHT_REGISTERED, new_bd);

	return new_bd;
}