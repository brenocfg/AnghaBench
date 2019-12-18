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
struct nvmet_port {int /*<<< orphan*/  entry; } ;

/* Variables and functions */
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvme_delete_wq ; 
 int /*<<< orphan*/  nvme_loop_ports_mutex ; 

__attribute__((used)) static void nvme_loop_remove_port(struct nvmet_port *port)
{
	mutex_lock(&nvme_loop_ports_mutex);
	list_del_init(&port->entry);
	mutex_unlock(&nvme_loop_ports_mutex);

	/*
	 * Ensure any ctrls that are in the process of being
	 * deleted are in fact deleted before we return
	 * and free the port. This is to prevent active
	 * ctrls from using a port after it's freed.
	 */
	flush_workqueue(nvme_delete_wq);
}