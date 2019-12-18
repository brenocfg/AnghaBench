#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  release; int /*<<< orphan*/  groups; struct TYPE_9__* parent; int /*<<< orphan*/  init_name; int /*<<< orphan*/ * bus; } ;
struct most_interface {unsigned int num_channels; TYPE_4__ dev; struct most_channel* p; int /*<<< orphan*/  description; TYPE_1__* channel_vector; int /*<<< orphan*/  poison_channel; int /*<<< orphan*/  configure; int /*<<< orphan*/  enqueue; } ;
struct TYPE_7__ {scalar_t__ packets_per_xact; scalar_t__ subbuffer_size; scalar_t__ buffer_size; scalar_t__ num_buffers; scalar_t__ data_type; scalar_t__ direction; } ;
struct most_channel {int dev_id; unsigned int channel_id; int keep_mbo; int enqueue_halt; int is_poisoned; TYPE_4__ dev; struct most_channel** channel; int /*<<< orphan*/  channel_list; int /*<<< orphan*/  list; int /*<<< orphan*/  nq_mutex; int /*<<< orphan*/  start_mutex; int /*<<< orphan*/  mbo_ref; int /*<<< orphan*/  cleanup; int /*<<< orphan*/  halt_fifo; int /*<<< orphan*/  trash_fifo; int /*<<< orphan*/  fifo; int /*<<< orphan*/  fifo_lock; TYPE_2__ cfg; struct most_interface* iface; scalar_t__ is_starving; int /*<<< orphan*/  name; } ;
struct TYPE_8__ {TYPE_4__ dev; int /*<<< orphan*/  bus; } ;
struct TYPE_6__ {char* name_suffix; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 unsigned int MAX_CHANNELS ; 
 int /*<<< orphan*/  STRING_SIZE ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  channel_attr_groups ; 
 scalar_t__ device_register (TYPE_4__*) ; 
 int /*<<< orphan*/  device_unregister (TYPE_4__*) ; 
 int ida_simple_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ida_simple_remove (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  interface_attr_groups ; 
 int /*<<< orphan*/  kfree (struct most_channel*) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_3__ mc ; 
 int /*<<< orphan*/  mdev_id ; 
 int /*<<< orphan*/  most_interface_register_notify (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  pr_info (char*,...) ; 
 int /*<<< orphan*/  release_channel ; 
 int /*<<< orphan*/  release_interface ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int most_register_interface(struct most_interface *iface)
{
	unsigned int i;
	int id;
	struct most_channel *c;

	if (!iface || !iface->enqueue || !iface->configure ||
	    !iface->poison_channel || (iface->num_channels > MAX_CHANNELS)) {
		pr_err("Bad interface or channel overflow\n");
		return -EINVAL;
	}

	id = ida_simple_get(&mdev_id, 0, 0, GFP_KERNEL);
	if (id < 0) {
		pr_info("Failed to alloc mdev ID\n");
		return id;
	}

	iface->p = kzalloc(sizeof(*iface->p), GFP_KERNEL);
	if (!iface->p) {
		ida_simple_remove(&mdev_id, id);
		return -ENOMEM;
	}

	INIT_LIST_HEAD(&iface->p->channel_list);
	iface->p->dev_id = id;
	strscpy(iface->p->name, iface->description, sizeof(iface->p->name));
	iface->dev.init_name = iface->p->name;
	iface->dev.bus = &mc.bus;
	iface->dev.parent = &mc.dev;
	iface->dev.groups = interface_attr_groups;
	iface->dev.release = release_interface;
	if (device_register(&iface->dev)) {
		pr_err("registering iface->dev failed\n");
		kfree(iface->p);
		ida_simple_remove(&mdev_id, id);
		return -ENOMEM;
	}

	for (i = 0; i < iface->num_channels; i++) {
		const char *name_suffix = iface->channel_vector[i].name_suffix;

		c = kzalloc(sizeof(*c), GFP_KERNEL);
		if (!c)
			goto err_free_resources;
		if (!name_suffix)
			snprintf(c->name, STRING_SIZE, "ch%d", i);
		else
			snprintf(c->name, STRING_SIZE, "%s", name_suffix);
		c->dev.init_name = c->name;
		c->dev.parent = &iface->dev;
		c->dev.groups = channel_attr_groups;
		c->dev.release = release_channel;
		iface->p->channel[i] = c;
		c->is_starving = 0;
		c->iface = iface;
		c->channel_id = i;
		c->keep_mbo = false;
		c->enqueue_halt = false;
		c->is_poisoned = false;
		c->cfg.direction = 0;
		c->cfg.data_type = 0;
		c->cfg.num_buffers = 0;
		c->cfg.buffer_size = 0;
		c->cfg.subbuffer_size = 0;
		c->cfg.packets_per_xact = 0;
		spin_lock_init(&c->fifo_lock);
		INIT_LIST_HEAD(&c->fifo);
		INIT_LIST_HEAD(&c->trash_fifo);
		INIT_LIST_HEAD(&c->halt_fifo);
		init_completion(&c->cleanup);
		atomic_set(&c->mbo_ref, 0);
		mutex_init(&c->start_mutex);
		mutex_init(&c->nq_mutex);
		list_add_tail(&c->list, &iface->p->channel_list);
		if (device_register(&c->dev)) {
			pr_err("registering c->dev failed\n");
			goto err_free_most_channel;
		}
	}
	pr_info("registered new device mdev%d (%s)\n",
		id, iface->description);
	most_interface_register_notify(iface->description);
	return 0;

err_free_most_channel:
	kfree(c);

err_free_resources:
	while (i > 0) {
		c = iface->p->channel[--i];
		device_unregister(&c->dev);
		kfree(c);
	}
	kfree(iface->p);
	device_unregister(&iface->dev);
	ida_simple_remove(&mdev_id, id);
	return -ENOMEM;
}