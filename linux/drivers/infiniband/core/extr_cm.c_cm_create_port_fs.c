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
struct cm_port {TYPE_2__* counter_group; int /*<<< orphan*/  port_num; TYPE_1__* cm_dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  obj; } ;
struct TYPE_3__ {int /*<<< orphan*/  ib_device; } ;

/* Variables and functions */
 int CM_COUNTER_GROUPS ; 
 int /*<<< orphan*/  cm_counter_obj_type ; 
 int /*<<< orphan*/ * counter_group_names ; 
 int ib_port_register_module_stat (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_port_unregister_module_stat (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cm_create_port_fs(struct cm_port *port)
{
	int i, ret;

	for (i = 0; i < CM_COUNTER_GROUPS; i++) {
		ret = ib_port_register_module_stat(port->cm_dev->ib_device,
						   port->port_num,
						   &port->counter_group[i].obj,
						   &cm_counter_obj_type,
						   counter_group_names[i]);
		if (ret)
			goto error;
	}

	return 0;

error:
	while (i--)
		ib_port_unregister_module_stat(&port->counter_group[i].obj);
	return ret;

}