#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int max_port_number; } ;
struct tb_switch {scalar_t__ is_unplugged; struct tb_port* ports; TYPE_3__ config; } ;
struct tb_port {TYPE_2__* remote; TYPE_1__* dual_link_port; } ;
struct TYPE_5__ {struct tb_switch* sw; } ;
struct TYPE_4__ {int /*<<< orphan*/ * remote; } ;

/* Variables and functions */
 int /*<<< orphan*/  tb_port_has_remote (struct tb_port*) ; 
 int /*<<< orphan*/  tb_switch_remove (struct tb_switch*) ; 

__attribute__((used)) static void tb_free_unplugged_children(struct tb_switch *sw)
{
	int i;
	for (i = 1; i <= sw->config.max_port_number; i++) {
		struct tb_port *port = &sw->ports[i];

		if (!tb_port_has_remote(port))
			continue;

		if (port->remote->sw->is_unplugged) {
			tb_switch_remove(port->remote->sw);
			port->remote = NULL;
			if (port->dual_link_port)
				port->dual_link_port->remote = NULL;
		} else {
			tb_free_unplugged_children(port->remote->sw);
		}
	}
}