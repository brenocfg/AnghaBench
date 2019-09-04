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
struct drbd_resource {char* name; struct dentry* debugfs_res_in_flight_summary; struct dentry* debugfs_res; struct dentry* debugfs_res_connections; struct dentry* debugfs_res_volumes; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR_OR_NULL (struct dentry*) ; 
 struct dentry* debugfs_create_dir (char*,struct dentry*) ; 
 struct dentry* debugfs_create_file (char*,int,struct dentry*,struct drbd_resource*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drbd_debugfs_resource_cleanup (struct drbd_resource*) ; 
 struct dentry* drbd_debugfs_resources ; 
 int /*<<< orphan*/  drbd_err (struct drbd_resource*,char*) ; 
 int /*<<< orphan*/  in_flight_summary_fops ; 

void drbd_debugfs_resource_add(struct drbd_resource *resource)
{
	struct dentry *dentry;
	if (!drbd_debugfs_resources)
		return;

	dentry = debugfs_create_dir(resource->name, drbd_debugfs_resources);
	if (IS_ERR_OR_NULL(dentry))
		goto fail;
	resource->debugfs_res = dentry;

	dentry = debugfs_create_dir("volumes", resource->debugfs_res);
	if (IS_ERR_OR_NULL(dentry))
		goto fail;
	resource->debugfs_res_volumes = dentry;

	dentry = debugfs_create_dir("connections", resource->debugfs_res);
	if (IS_ERR_OR_NULL(dentry))
		goto fail;
	resource->debugfs_res_connections = dentry;

	dentry = debugfs_create_file("in_flight_summary", 0440,
				     resource->debugfs_res, resource,
				     &in_flight_summary_fops);
	if (IS_ERR_OR_NULL(dentry))
		goto fail;
	resource->debugfs_res_in_flight_summary = dentry;
	return;

fail:
	drbd_debugfs_resource_cleanup(resource);
	drbd_err(resource, "failed to create debugfs dentry\n");
}