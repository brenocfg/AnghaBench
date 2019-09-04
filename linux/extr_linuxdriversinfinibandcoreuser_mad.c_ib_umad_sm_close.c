#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct inode {int dummy; } ;
struct ib_umad_port {TYPE_1__* umad_dev; int /*<<< orphan*/  sm_sem; int /*<<< orphan*/  file_mutex; int /*<<< orphan*/  port_num; scalar_t__ ib_dev; } ;
struct ib_port_modify {int /*<<< orphan*/  clr_port_cap_mask; } ;
struct file {struct ib_umad_port* private_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 int /*<<< orphan*/  IB_PORT_SM ; 
 int ib_modify_port (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ib_port_modify*) ; 
 int /*<<< orphan*/  kobject_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ib_umad_sm_close(struct inode *inode, struct file *filp)
{
	struct ib_umad_port *port = filp->private_data;
	struct ib_port_modify props = {
		.clr_port_cap_mask = IB_PORT_SM
	};
	int ret = 0;

	mutex_lock(&port->file_mutex);
	if (port->ib_dev)
		ret = ib_modify_port(port->ib_dev, port->port_num, 0, &props);
	mutex_unlock(&port->file_mutex);

	up(&port->sm_sem);

	kobject_put(&port->umad_dev->kobj);

	return ret;
}