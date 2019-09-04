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
struct module {int dummy; } ;
struct gigaset_ops {int dummy; } ;
struct gigaset_driver {unsigned int minor; unsigned int minors; int /*<<< orphan*/  list; TYPE_1__* cs; struct gigaset_ops const* ops; struct module* owner; scalar_t__ blocked; int /*<<< orphan*/  lock; scalar_t__ have_tty; } ;
struct TYPE_2__ {unsigned int minor_index; int /*<<< orphan*/  mutex; struct gigaset_ops const* ops; struct gigaset_driver* driver; scalar_t__ flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  driver_lock ; 
 int /*<<< orphan*/  drivers ; 
 int /*<<< orphan*/  gigaset_if_initdriver (struct gigaset_driver*,char const*,char const*) ; 
 int /*<<< orphan*/  kfree (struct gigaset_driver*) ; 
 struct gigaset_driver* kmalloc (int,int /*<<< orphan*/ ) ; 
 TYPE_1__* kmalloc_array (unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

struct gigaset_driver *gigaset_initdriver(unsigned minor, unsigned minors,
					  const char *procname,
					  const char *devname,
					  const struct gigaset_ops *ops,
					  struct module *owner)
{
	struct gigaset_driver *drv;
	unsigned long flags;
	unsigned i;

	drv = kmalloc(sizeof *drv, GFP_KERNEL);
	if (!drv)
		return NULL;

	drv->have_tty = 0;
	drv->minor = minor;
	drv->minors = minors;
	spin_lock_init(&drv->lock);
	drv->blocked = 0;
	drv->ops = ops;
	drv->owner = owner;
	INIT_LIST_HEAD(&drv->list);

	drv->cs = kmalloc_array(minors, sizeof(*drv->cs), GFP_KERNEL);
	if (!drv->cs)
		goto error;

	for (i = 0; i < minors; ++i) {
		drv->cs[i].flags = 0;
		drv->cs[i].driver = drv;
		drv->cs[i].ops = drv->ops;
		drv->cs[i].minor_index = i;
		mutex_init(&drv->cs[i].mutex);
	}

	gigaset_if_initdriver(drv, procname, devname);

	spin_lock_irqsave(&driver_lock, flags);
	list_add(&drv->list, &drivers);
	spin_unlock_irqrestore(&driver_lock, flags);

	return drv;

error:
	kfree(drv);
	return NULL;
}