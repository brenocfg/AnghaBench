#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct most_interface {int dummy; } ;
struct most_channel_config {int /*<<< orphan*/  num_buffers; } ;
struct TYPE_10__ {int /*<<< orphan*/  owner; } ;
struct comp_channel {int channel_id; TYPE_3__ cdev; int /*<<< orphan*/  list; int /*<<< orphan*/  fifo; TYPE_1__* dev; int /*<<< orphan*/  devno; int /*<<< orphan*/  io_mutex; int /*<<< orphan*/  wq; int /*<<< orphan*/  unlink; scalar_t__ access_ref; struct most_channel_config* cfg; struct most_interface* iface; } ;
struct TYPE_9__ {int /*<<< orphan*/  minor_id; int /*<<< orphan*/  class; int /*<<< orphan*/  major; } ;
struct TYPE_8__ {int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 int EEXIST ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_KFIFO (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (TYPE_1__*) ; 
 int /*<<< orphan*/  KOBJ_ADD ; 
 int /*<<< orphan*/  MKDEV (int /*<<< orphan*/ ,int) ; 
 int PTR_ERR (TYPE_1__*) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int cdev_add (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cdev_del (TYPE_3__*) ; 
 int /*<<< orphan*/  cdev_init (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ch_list_lock ; 
 int /*<<< orphan*/  channel_fops ; 
 int /*<<< orphan*/  channel_list ; 
 TYPE_2__ comp ; 
 TYPE_1__* device_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,char*) ; 
 struct comp_channel* get_channel (struct most_interface*,int) ; 
 int ida_simple_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ida_simple_remove (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int kfifo_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfifo_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct comp_channel*) ; 
 int /*<<< orphan*/  kobject_uevent (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct comp_channel* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_info (char*,...) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int comp_probe(struct most_interface *iface, int channel_id,
		      struct most_channel_config *cfg, char *name, char *args)
{
	struct comp_channel *c;
	unsigned long cl_flags;
	int retval;
	int current_minor;

	if ((!iface) || (!cfg) || (!name)) {
		pr_info("Probing component with bad arguments");
		return -EINVAL;
	}
	c = get_channel(iface, channel_id);
	if (c)
		return -EEXIST;

	current_minor = ida_simple_get(&comp.minor_id, 0, 0, GFP_KERNEL);
	if (current_minor < 0)
		return current_minor;

	c = kzalloc(sizeof(*c), GFP_KERNEL);
	if (!c) {
		retval = -ENOMEM;
		goto err_remove_ida;
	}

	c->devno = MKDEV(comp.major, current_minor);
	cdev_init(&c->cdev, &channel_fops);
	c->cdev.owner = THIS_MODULE;
	retval = cdev_add(&c->cdev, c->devno, 1);
	if (retval < 0)
		goto err_free_c;
	c->iface = iface;
	c->cfg = cfg;
	c->channel_id = channel_id;
	c->access_ref = 0;
	spin_lock_init(&c->unlink);
	INIT_KFIFO(c->fifo);
	retval = kfifo_alloc(&c->fifo, cfg->num_buffers, GFP_KERNEL);
	if (retval)
		goto err_del_cdev_and_free_channel;
	init_waitqueue_head(&c->wq);
	mutex_init(&c->io_mutex);
	spin_lock_irqsave(&ch_list_lock, cl_flags);
	list_add_tail(&c->list, &channel_list);
	spin_unlock_irqrestore(&ch_list_lock, cl_flags);
	c->dev = device_create(comp.class, NULL, c->devno, NULL, "%s", name);

	if (IS_ERR(c->dev)) {
		retval = PTR_ERR(c->dev);
		pr_info("failed to create new device node %s\n", name);
		goto err_free_kfifo_and_del_list;
	}
	kobject_uevent(&c->dev->kobj, KOBJ_ADD);
	return 0;

err_free_kfifo_and_del_list:
	kfifo_free(&c->fifo);
	list_del(&c->list);
err_del_cdev_and_free_channel:
	cdev_del(&c->cdev);
err_free_c:
	kfree(c);
err_remove_ida:
	ida_simple_remove(&comp.minor_id, current_minor);
	return retval;
}