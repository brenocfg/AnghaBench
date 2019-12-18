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
struct TYPE_4__ {int /*<<< orphan*/  parent; } ;
struct TYPE_3__ {int /*<<< orphan*/  enabled; } ;
struct tb_switch {TYPE_2__ dev; TYPE_1__ config; } ;
struct tb_port {int dummy; } ;

/* Variables and functions */
 int tb_lc_configure_lane (struct tb_port*,int) ; 
 struct tb_port* tb_port_at (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tb_route (struct tb_switch*) ; 
 int /*<<< orphan*/  tb_to_switch (int /*<<< orphan*/ ) ; 
 struct tb_port* tb_upstream_port (struct tb_switch*) ; 

int tb_lc_configure_link(struct tb_switch *sw)
{
	struct tb_port *up, *down;
	int ret;

	if (!sw->config.enabled || !tb_route(sw))
		return 0;

	up = tb_upstream_port(sw);
	down = tb_port_at(tb_route(sw), tb_to_switch(sw->dev.parent));

	/* Configure parent link toward this switch */
	ret = tb_lc_configure_lane(down, true);
	if (ret)
		return ret;

	/* Configure upstream link from this switch to the parent */
	ret = tb_lc_configure_lane(up, true);
	if (ret)
		tb_lc_configure_lane(down, false);

	return ret;
}