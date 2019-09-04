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
struct drbd_device {int /*<<< orphan*/  debugfs_vol; int /*<<< orphan*/  debugfs_vol_ed_gen_id; int /*<<< orphan*/  debugfs_vol_data_gen_id; int /*<<< orphan*/  debugfs_vol_resync_extents; int /*<<< orphan*/  debugfs_vol_act_log_extents; int /*<<< orphan*/  debugfs_vol_oldest_requests; int /*<<< orphan*/  debugfs_minor; } ;

/* Variables and functions */
 int /*<<< orphan*/  drbd_debugfs_remove (int /*<<< orphan*/ *) ; 

void drbd_debugfs_device_cleanup(struct drbd_device *device)
{
	drbd_debugfs_remove(&device->debugfs_minor);
	drbd_debugfs_remove(&device->debugfs_vol_oldest_requests);
	drbd_debugfs_remove(&device->debugfs_vol_act_log_extents);
	drbd_debugfs_remove(&device->debugfs_vol_resync_extents);
	drbd_debugfs_remove(&device->debugfs_vol_data_gen_id);
	drbd_debugfs_remove(&device->debugfs_vol_ed_gen_id);
	drbd_debugfs_remove(&device->debugfs_vol);
}