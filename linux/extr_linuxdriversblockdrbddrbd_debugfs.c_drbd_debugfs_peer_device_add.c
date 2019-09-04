#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vnr_buf ;
struct drbd_peer_device {struct dentry* debugfs_peer_dev; TYPE_2__* device; TYPE_1__* connection; } ;
struct dentry {int dummy; } ;
struct TYPE_4__ {int vnr; } ;
struct TYPE_3__ {struct dentry* debugfs_conn; } ;

/* Variables and functions */
 scalar_t__ IS_ERR_OR_NULL (struct dentry*) ; 
 struct dentry* debugfs_create_dir (char*,struct dentry*) ; 
 int /*<<< orphan*/  drbd_debugfs_peer_device_cleanup (struct drbd_peer_device*) ; 
 int /*<<< orphan*/  drbd_err (struct drbd_peer_device*,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

void drbd_debugfs_peer_device_add(struct drbd_peer_device *peer_device)
{
	struct dentry *conn_dir = peer_device->connection->debugfs_conn;
	struct dentry *dentry;
	char vnr_buf[8];

	if (!conn_dir)
		return;

	snprintf(vnr_buf, sizeof(vnr_buf), "%u", peer_device->device->vnr);
	dentry = debugfs_create_dir(vnr_buf, conn_dir);
	if (IS_ERR_OR_NULL(dentry))
		goto fail;
	peer_device->debugfs_peer_dev = dentry;
	return;

fail:
	drbd_debugfs_peer_device_cleanup(peer_device);
	drbd_err(peer_device, "failed to create debugfs entries\n");
}