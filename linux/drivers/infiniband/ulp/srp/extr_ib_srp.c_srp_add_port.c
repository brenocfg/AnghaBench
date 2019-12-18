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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_8__ {int /*<<< orphan*/  parent; int /*<<< orphan*/ * class; } ;
struct srp_host {TYPE_2__ dev; int /*<<< orphan*/  port; struct srp_device* srp_dev; int /*<<< orphan*/  add_target_mutex; int /*<<< orphan*/  released; int /*<<< orphan*/  target_lock; int /*<<< orphan*/  target_list; } ;
struct srp_device {TYPE_1__* dev; } ;
struct TYPE_9__ {int /*<<< orphan*/  parent; } ;
struct TYPE_7__ {TYPE_6__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_attr_add_target ; 
 int /*<<< orphan*/  dev_attr_ibdev ; 
 int /*<<< orphan*/  dev_attr_port ; 
 int /*<<< orphan*/  dev_name (TYPE_6__*) ; 
 int /*<<< orphan*/  dev_set_name (TYPE_2__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ device_create_file (TYPE_2__*,int /*<<< orphan*/ *) ; 
 scalar_t__ device_register (TYPE_2__*) ; 
 int /*<<< orphan*/  device_unregister (TYPE_2__*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct srp_host*) ; 
 struct srp_host* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  srp_class ; 

__attribute__((used)) static struct srp_host *srp_add_port(struct srp_device *device, u8 port)
{
	struct srp_host *host;

	host = kzalloc(sizeof *host, GFP_KERNEL);
	if (!host)
		return NULL;

	INIT_LIST_HEAD(&host->target_list);
	spin_lock_init(&host->target_lock);
	init_completion(&host->released);
	mutex_init(&host->add_target_mutex);
	host->srp_dev = device;
	host->port = port;

	host->dev.class = &srp_class;
	host->dev.parent = device->dev->dev.parent;
	dev_set_name(&host->dev, "srp-%s-%d", dev_name(&device->dev->dev),
		     port);

	if (device_register(&host->dev))
		goto free_host;
	if (device_create_file(&host->dev, &dev_attr_add_target))
		goto err_class;
	if (device_create_file(&host->dev, &dev_attr_ibdev))
		goto err_class;
	if (device_create_file(&host->dev, &dev_attr_port))
		goto err_class;

	return host;

err_class:
	device_unregister(&host->dev);

free_host:
	kfree(host);

	return NULL;
}