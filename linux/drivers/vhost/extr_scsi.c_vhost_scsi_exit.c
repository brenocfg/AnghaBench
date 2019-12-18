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

/* Variables and functions */
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  target_unregister_template (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vhost_scsi_deregister () ; 
 int /*<<< orphan*/  vhost_scsi_ops ; 
 int /*<<< orphan*/  vhost_scsi_workqueue ; 

__attribute__((used)) static void vhost_scsi_exit(void)
{
	target_unregister_template(&vhost_scsi_ops);
	vhost_scsi_deregister();
	destroy_workqueue(vhost_scsi_workqueue);
}