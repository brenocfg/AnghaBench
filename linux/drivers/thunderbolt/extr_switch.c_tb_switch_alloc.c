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
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_6__ {int /*<<< orphan*/  groups; int /*<<< orphan*/ * type; int /*<<< orphan*/ * bus; struct device* parent; } ;
struct TYPE_5__ {int upstream_port_number; int depth; int max_port_number; scalar_t__ enabled; int /*<<< orphan*/  route_lo; int /*<<< orphan*/  route_hi; } ;
struct tb_switch {int port; int cap_plug_events; int cap_lc; int authorized; struct tb_switch* ports; TYPE_3__ dev; int /*<<< orphan*/  generation; struct tb_switch* sw; TYPE_1__ config; struct tb* tb; } ;
struct tb {int /*<<< orphan*/  index; int /*<<< orphan*/  ctl; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EADDRNOTAVAIL ; 
 int ENOMEM ; 
 struct tb_switch* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  TB_CFG_SWITCH ; 
 int TB_SWITCH_MAX_DEPTH ; 
 int /*<<< orphan*/  TB_VSE_CAP_LINK_CONTROLLER ; 
 int /*<<< orphan*/  TB_VSE_CAP_PLUG_EVENTS ; 
 int /*<<< orphan*/  dev_set_name (TYPE_3__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_initialize (TYPE_3__*) ; 
 struct tb_switch* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct tb_switch*) ; 
 struct tb_switch* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lower_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  switch_groups ; 
 int /*<<< orphan*/  tb_bus_type ; 
 int tb_cfg_get_upstream_port (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int tb_cfg_read (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tb_dbg (struct tb*,char*) ; 
 int /*<<< orphan*/  tb_dump_switch (struct tb*,TYPE_1__*) ; 
 int /*<<< orphan*/  tb_route (struct tb_switch*) ; 
 int tb_route_length (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tb_sw_warn (struct tb_switch*,char*) ; 
 int tb_switch_find_vse_cap (struct tb_switch*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tb_switch_get_generation (struct tb_switch*) ; 
 int /*<<< orphan*/  tb_switch_type ; 
 int /*<<< orphan*/  upper_32_bits (int /*<<< orphan*/ ) ; 

struct tb_switch *tb_switch_alloc(struct tb *tb, struct device *parent,
				  u64 route)
{
	struct tb_switch *sw;
	int upstream_port;
	int i, ret, depth;

	/* Make sure we do not exceed maximum topology limit */
	depth = tb_route_length(route);
	if (depth > TB_SWITCH_MAX_DEPTH)
		return ERR_PTR(-EADDRNOTAVAIL);

	upstream_port = tb_cfg_get_upstream_port(tb->ctl, route);
	if (upstream_port < 0)
		return ERR_PTR(upstream_port);

	sw = kzalloc(sizeof(*sw), GFP_KERNEL);
	if (!sw)
		return ERR_PTR(-ENOMEM);

	sw->tb = tb;
	ret = tb_cfg_read(tb->ctl, &sw->config, route, 0, TB_CFG_SWITCH, 0, 5);
	if (ret)
		goto err_free_sw_ports;

	tb_dbg(tb, "current switch config:\n");
	tb_dump_switch(tb, &sw->config);

	/* configure switch */
	sw->config.upstream_port_number = upstream_port;
	sw->config.depth = depth;
	sw->config.route_hi = upper_32_bits(route);
	sw->config.route_lo = lower_32_bits(route);
	sw->config.enabled = 0;

	/* initialize ports */
	sw->ports = kcalloc(sw->config.max_port_number + 1, sizeof(*sw->ports),
				GFP_KERNEL);
	if (!sw->ports) {
		ret = -ENOMEM;
		goto err_free_sw_ports;
	}

	for (i = 0; i <= sw->config.max_port_number; i++) {
		/* minimum setup for tb_find_cap and tb_drom_read to work */
		sw->ports[i].sw = sw;
		sw->ports[i].port = i;
	}

	sw->generation = tb_switch_get_generation(sw);

	ret = tb_switch_find_vse_cap(sw, TB_VSE_CAP_PLUG_EVENTS);
	if (ret < 0) {
		tb_sw_warn(sw, "cannot find TB_VSE_CAP_PLUG_EVENTS aborting\n");
		goto err_free_sw_ports;
	}
	sw->cap_plug_events = ret;

	ret = tb_switch_find_vse_cap(sw, TB_VSE_CAP_LINK_CONTROLLER);
	if (ret > 0)
		sw->cap_lc = ret;

	/* Root switch is always authorized */
	if (!route)
		sw->authorized = true;

	device_initialize(&sw->dev);
	sw->dev.parent = parent;
	sw->dev.bus = &tb_bus_type;
	sw->dev.type = &tb_switch_type;
	sw->dev.groups = switch_groups;
	dev_set_name(&sw->dev, "%u-%llx", tb->index, tb_route(sw));

	return sw;

err_free_sw_ports:
	kfree(sw->ports);
	kfree(sw);

	return ERR_PTR(ret);
}