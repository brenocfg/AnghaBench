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
typedef  int /*<<< orphan*/  uuid_t ;
typedef  void* u8 ;
typedef  int /*<<< orphan*/  u64 ;
struct tb_switch {int authorized; int security_level; int boot; int rpm; int /*<<< orphan*/  dev; int /*<<< orphan*/  rpm_complete; void* depth; void* link; void* connection_key; void* connection_id; int /*<<< orphan*/  uuid; int /*<<< orphan*/  tb; } ;
struct intel_vss {int flags; } ;
typedef  enum tb_security_level { ____Placeholder_tb_security_level } tb_security_level ;
struct TYPE_4__ {TYPE_1__* remote; } ;
struct TYPE_3__ {TYPE_2__* remote; } ;

/* Variables and functions */
 struct tb_switch* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int INTEL_VSS_FLAGS_RTD3 ; 
 scalar_t__ IS_ERR (struct tb_switch*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kmemdup (int /*<<< orphan*/  const*,int,int /*<<< orphan*/ ) ; 
 struct intel_vss* parse_intel_vss (void* const*,size_t) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ *) ; 
 TYPE_2__* tb_port_at (int /*<<< orphan*/ ,struct tb_switch*) ; 
 int /*<<< orphan*/  tb_route (struct tb_switch*) ; 
 int /*<<< orphan*/  tb_sw_warn (struct tb_switch*,char*) ; 
 int tb_switch_add (struct tb_switch*) ; 
 struct tb_switch* tb_switch_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tb_switch_put (struct tb_switch*) ; 
 TYPE_1__* tb_upstream_port (struct tb_switch*) ; 

__attribute__((used)) static struct tb_switch *add_switch(struct tb_switch *parent_sw, u64 route,
				    const uuid_t *uuid, const u8 *ep_name,
				    size_t ep_name_size, u8 connection_id,
				    u8 connection_key, u8 link, u8 depth,
				    enum tb_security_level security_level,
				    bool authorized, bool boot)
{
	const struct intel_vss *vss;
	struct tb_switch *sw;
	int ret;

	pm_runtime_get_sync(&parent_sw->dev);

	sw = tb_switch_alloc(parent_sw->tb, &parent_sw->dev, route);
	if (IS_ERR(sw))
		goto out;

	sw->uuid = kmemdup(uuid, sizeof(*uuid), GFP_KERNEL);
	if (!sw->uuid) {
		tb_sw_warn(sw, "cannot allocate memory for switch\n");
		tb_switch_put(sw);
		goto out;
	}
	sw->connection_id = connection_id;
	sw->connection_key = connection_key;
	sw->link = link;
	sw->depth = depth;
	sw->authorized = authorized;
	sw->security_level = security_level;
	sw->boot = boot;
	init_completion(&sw->rpm_complete);

	vss = parse_intel_vss(ep_name, ep_name_size);
	if (vss)
		sw->rpm = !!(vss->flags & INTEL_VSS_FLAGS_RTD3);

	/* Link the two switches now */
	tb_port_at(route, parent_sw)->remote = tb_upstream_port(sw);
	tb_upstream_port(sw)->remote = tb_port_at(route, parent_sw);

	ret = tb_switch_add(sw);
	if (ret) {
		tb_port_at(tb_route(sw), parent_sw)->remote = NULL;
		tb_switch_put(sw);
		sw = ERR_PTR(ret);
	}

out:
	pm_runtime_mark_last_busy(&parent_sw->dev);
	pm_runtime_put_autosuspend(&parent_sw->dev);

	return sw;
}