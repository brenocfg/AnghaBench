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
struct drbd_connection {int /*<<< orphan*/  debugfs_conn; int /*<<< orphan*/  debugfs_conn_oldest_requests; int /*<<< orphan*/  debugfs_conn_callback_history; } ;

/* Variables and functions */
 int /*<<< orphan*/  drbd_debugfs_remove (int /*<<< orphan*/ *) ; 

void drbd_debugfs_connection_cleanup(struct drbd_connection *connection)
{
	drbd_debugfs_remove(&connection->debugfs_conn_callback_history);
	drbd_debugfs_remove(&connection->debugfs_conn_oldest_requests);
	drbd_debugfs_remove(&connection->debugfs_conn);
}