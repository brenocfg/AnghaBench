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
typedef  void* u8 ;
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_3__ {int /*<<< orphan*/  route_lo; int /*<<< orphan*/  route_hi; } ;
struct tb_switch {int boot; int is_unplugged; int /*<<< orphan*/  rpm_complete; void* depth; void* link; void* connection_key; void* connection_id; TYPE_1__ config; } ;
struct TYPE_4__ {int /*<<< orphan*/ * remote; } ;

/* Variables and functions */
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lower_32_bits (int /*<<< orphan*/ ) ; 
 TYPE_2__* tb_port_at (int /*<<< orphan*/ ,struct tb_switch*) ; 
 int /*<<< orphan*/  tb_route (struct tb_switch*) ; 
 int /*<<< orphan*/ * tb_upstream_port (struct tb_switch*) ; 
 int /*<<< orphan*/  upper_32_bits (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void update_switch(struct tb_switch *parent_sw, struct tb_switch *sw,
			  u64 route, u8 connection_id, u8 connection_key,
			  u8 link, u8 depth, bool boot)
{
	/* Disconnect from parent */
	tb_port_at(tb_route(sw), parent_sw)->remote = NULL;
	/* Re-connect via updated port*/
	tb_port_at(route, parent_sw)->remote = tb_upstream_port(sw);

	/* Update with the new addressing information */
	sw->config.route_hi = upper_32_bits(route);
	sw->config.route_lo = lower_32_bits(route);
	sw->connection_id = connection_id;
	sw->connection_key = connection_key;
	sw->link = link;
	sw->depth = depth;
	sw->boot = boot;

	/* This switch still exists */
	sw->is_unplugged = false;

	/* Runtime resume is now complete */
	complete(&sw->rpm_complete);
}