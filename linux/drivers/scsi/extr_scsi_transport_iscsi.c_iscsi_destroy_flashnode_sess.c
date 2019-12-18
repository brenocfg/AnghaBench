#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  name; } ;
struct TYPE_5__ {TYPE_1__ kobj; } ;
struct iscsi_bus_flash_session {TYPE_2__ dev; } ;

/* Variables and functions */
 int device_for_each_child (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_unregister (TYPE_2__*) ; 
 int /*<<< orphan*/  iscsi_iter_destroy_flashnode_conn_fn ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int) ; 

void iscsi_destroy_flashnode_sess(struct iscsi_bus_flash_session *fnode_sess)
{
	int err;

	err = device_for_each_child(&fnode_sess->dev, NULL,
				    iscsi_iter_destroy_flashnode_conn_fn);
	if (err)
		pr_err("Could not delete all connections for %s. Error %d.\n",
		       fnode_sess->dev.kobj.name, err);

	device_unregister(&fnode_sess->dev);
}