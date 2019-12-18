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
struct cm_port {TYPE_1__* counter_group; } ;
struct TYPE_2__ {int /*<<< orphan*/  obj; } ;

/* Variables and functions */
 int CM_COUNTER_GROUPS ; 
 int /*<<< orphan*/  ib_port_unregister_module_stat (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cm_remove_port_fs(struct cm_port *port)
{
	int i;

	for (i = 0; i < CM_COUNTER_GROUPS; i++)
		ib_port_unregister_module_stat(&port->counter_group[i].obj);

}