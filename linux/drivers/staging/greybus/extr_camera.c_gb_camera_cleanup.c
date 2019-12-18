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
struct gb_camera {int /*<<< orphan*/  mutex; int /*<<< orphan*/ * connection; int /*<<< orphan*/ * data_connection; } ;

/* Variables and functions */
 int /*<<< orphan*/  gb_camera_debugfs_cleanup (struct gb_camera*) ; 
 int /*<<< orphan*/  gb_connection_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gb_connection_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void gb_camera_cleanup(struct gb_camera *gcam)
{
	gb_camera_debugfs_cleanup(gcam);

	mutex_lock(&gcam->mutex);
	if (gcam->data_connection) {
		gb_connection_disable(gcam->data_connection);
		gb_connection_destroy(gcam->data_connection);
		gcam->data_connection = NULL;
	}

	if (gcam->connection) {
		gb_connection_disable(gcam->connection);
		gb_connection_destroy(gcam->connection);
		gcam->connection = NULL;
	}
	mutex_unlock(&gcam->mutex);
}