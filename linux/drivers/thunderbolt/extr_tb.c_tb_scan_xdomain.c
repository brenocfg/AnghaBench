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
typedef  int /*<<< orphan*/  u64 ;
struct tb_xdomain {int dummy; } ;
struct tb_switch {int /*<<< orphan*/  dev; struct tb* tb; } ;
struct tb_port {struct tb_switch* sw; } ;
struct tb {TYPE_1__* root_switch; } ;
struct TYPE_4__ {struct tb_xdomain* xdomain; } ;
struct TYPE_3__ {int /*<<< orphan*/  uuid; } ;

/* Variables and functions */
 int /*<<< orphan*/  tb_downstream_route (struct tb_port*) ; 
 TYPE_2__* tb_port_at (int /*<<< orphan*/ ,struct tb_switch*) ; 
 int /*<<< orphan*/  tb_xdomain_add (struct tb_xdomain*) ; 
 struct tb_xdomain* tb_xdomain_alloc (struct tb*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct tb_xdomain* tb_xdomain_find_by_route (struct tb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tb_xdomain_put (struct tb_xdomain*) ; 

__attribute__((used)) static void tb_scan_xdomain(struct tb_port *port)
{
	struct tb_switch *sw = port->sw;
	struct tb *tb = sw->tb;
	struct tb_xdomain *xd;
	u64 route;

	route = tb_downstream_route(port);
	xd = tb_xdomain_find_by_route(tb, route);
	if (xd) {
		tb_xdomain_put(xd);
		return;
	}

	xd = tb_xdomain_alloc(tb, &sw->dev, route, tb->root_switch->uuid,
			      NULL);
	if (xd) {
		tb_port_at(route, sw)->xdomain = xd;
		tb_xdomain_add(xd);
	}
}