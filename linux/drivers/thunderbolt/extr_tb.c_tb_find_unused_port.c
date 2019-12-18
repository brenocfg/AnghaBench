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
struct TYPE_3__ {int max_port_number; } ;
struct tb_switch {struct tb_port* ports; TYPE_1__ config; } ;
struct TYPE_4__ {int type; } ;
struct tb_port {int /*<<< orphan*/  cap_adap; TYPE_2__ config; } ;
typedef  enum tb_port_type { ____Placeholder_tb_port_type } tb_port_type ;

/* Variables and functions */
 scalar_t__ tb_is_upstream_port (struct tb_port*) ; 
 scalar_t__ tb_port_is_enabled (struct tb_port*) ; 

__attribute__((used)) static struct tb_port *tb_find_unused_port(struct tb_switch *sw,
					   enum tb_port_type type)
{
	int i;

	for (i = 1; i <= sw->config.max_port_number; i++) {
		if (tb_is_upstream_port(&sw->ports[i]))
			continue;
		if (sw->ports[i].config.type != type)
			continue;
		if (!sw->ports[i].cap_adap)
			continue;
		if (tb_port_is_enabled(&sw->ports[i]))
			continue;
		return &sw->ports[i];
	}
	return NULL;
}