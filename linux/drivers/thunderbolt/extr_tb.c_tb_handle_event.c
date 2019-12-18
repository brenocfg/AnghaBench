#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct tb {int /*<<< orphan*/  ctl; } ;
struct cfg_event_pkg {int /*<<< orphan*/  unplug; int /*<<< orphan*/  port; int /*<<< orphan*/  header; } ;
typedef  enum tb_cfg_pkg_type { ____Placeholder_tb_cfg_pkg_type } tb_cfg_pkg_type ;

/* Variables and functions */
 int /*<<< orphan*/  TB_CFG_ERROR_ACK_PLUG_EVENT ; 
 int TB_CFG_PKG_EVENT ; 
 scalar_t__ tb_cfg_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tb_cfg_get_route (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tb_queue_hotplug (struct tb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tb_warn (struct tb*,char*,int,...) ; 

__attribute__((used)) static void tb_handle_event(struct tb *tb, enum tb_cfg_pkg_type type,
			    const void *buf, size_t size)
{
	const struct cfg_event_pkg *pkg = buf;
	u64 route;

	if (type != TB_CFG_PKG_EVENT) {
		tb_warn(tb, "unexpected event %#x, ignoring\n", type);
		return;
	}

	route = tb_cfg_get_route(&pkg->header);

	if (tb_cfg_error(tb->ctl, route, pkg->port,
			 TB_CFG_ERROR_ACK_PLUG_EVENT)) {
		tb_warn(tb, "could not ack plug event on %llx:%x\n", route,
			pkg->port);
	}

	tb_queue_hotplug(tb, route, pkg->port, pkg->unplug);
}