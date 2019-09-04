#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct drbd_resource {struct drbd_resource* name; int /*<<< orphan*/  req_lock; int /*<<< orphan*/  adm_mutex; int /*<<< orphan*/  conf_update; int /*<<< orphan*/  resources; int /*<<< orphan*/  write_ordering; int /*<<< orphan*/  connections; int /*<<< orphan*/  devices; int /*<<< orphan*/  kref; int /*<<< orphan*/  cpu_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WO_BDEV_FLUSH ; 
 int /*<<< orphan*/  drbd_debugfs_resource_add (struct drbd_resource*) ; 
 int /*<<< orphan*/  drbd_resources ; 
 int /*<<< orphan*/  idr_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct drbd_resource*) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 struct drbd_resource* kstrdup (char const*,int /*<<< orphan*/ ) ; 
 struct drbd_resource* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zalloc_cpumask_var (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

struct drbd_resource *drbd_create_resource(const char *name)
{
	struct drbd_resource *resource;

	resource = kzalloc(sizeof(struct drbd_resource), GFP_KERNEL);
	if (!resource)
		goto fail;
	resource->name = kstrdup(name, GFP_KERNEL);
	if (!resource->name)
		goto fail_free_resource;
	if (!zalloc_cpumask_var(&resource->cpu_mask, GFP_KERNEL))
		goto fail_free_name;
	kref_init(&resource->kref);
	idr_init(&resource->devices);
	INIT_LIST_HEAD(&resource->connections);
	resource->write_ordering = WO_BDEV_FLUSH;
	list_add_tail_rcu(&resource->resources, &drbd_resources);
	mutex_init(&resource->conf_update);
	mutex_init(&resource->adm_mutex);
	spin_lock_init(&resource->req_lock);
	drbd_debugfs_resource_add(resource);
	return resource;

fail_free_name:
	kfree(resource->name);
fail_free_resource:
	kfree(resource);
fail:
	return NULL;
}