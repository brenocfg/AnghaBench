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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u64 ;
struct tb_xdomain {scalar_t__ depth; int /*<<< orphan*/  route; } ;
struct tb_switch {int dummy; } ;
struct tb {int dummy; } ;
struct icm_pkg_header {int dummy; } ;
struct icm_fr_event_xdomain_connected {scalar_t__ link_info; int /*<<< orphan*/  remote_uuid; int /*<<< orphan*/  local_uuid; int /*<<< orphan*/  local_route_lo; int /*<<< orphan*/  local_route_hi; } ;

/* Variables and functions */
 scalar_t__ ICM_LINK_INFO_DEPTH_MASK ; 
 scalar_t__ ICM_LINK_INFO_DEPTH_SHIFT ; 
 scalar_t__ ICM_LINK_INFO_LINK_MASK ; 
 scalar_t__ ICM_MAX_LINK ; 
 scalar_t__ TB_SWITCH_MAX_DEPTH ; 
 int /*<<< orphan*/  add_xdomain (struct tb_switch*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 scalar_t__ dual_link_from_link (scalar_t__) ; 
 int /*<<< orphan*/  get_route (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ phy_port_from_route (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  remove_switch (struct tb_switch*) ; 
 int /*<<< orphan*/  remove_xdomain (struct tb_xdomain*) ; 
 struct tb_switch* tb_switch_find_by_link_depth (struct tb*,scalar_t__,scalar_t__) ; 
 struct tb_switch* tb_switch_find_by_route (struct tb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tb_switch_put (struct tb_switch*) ; 
 int /*<<< orphan*/  tb_warn (struct tb*,char*,scalar_t__,scalar_t__) ; 
 struct tb_xdomain* tb_xdomain_find_by_link_depth (struct tb*,scalar_t__,scalar_t__) ; 
 struct tb_xdomain* tb_xdomain_find_by_uuid (struct tb*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tb_xdomain_put (struct tb_xdomain*) ; 
 int /*<<< orphan*/  update_xdomain (struct tb_xdomain*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
icm_fr_xdomain_connected(struct tb *tb, const struct icm_pkg_header *hdr)
{
	const struct icm_fr_event_xdomain_connected *pkg =
		(const struct icm_fr_event_xdomain_connected *)hdr;
	struct tb_xdomain *xd;
	struct tb_switch *sw;
	u8 link, depth;
	u64 route;

	link = pkg->link_info & ICM_LINK_INFO_LINK_MASK;
	depth = (pkg->link_info & ICM_LINK_INFO_DEPTH_MASK) >>
		ICM_LINK_INFO_DEPTH_SHIFT;

	if (link > ICM_MAX_LINK || depth > TB_SWITCH_MAX_DEPTH) {
		tb_warn(tb, "invalid topology %u.%u, ignoring\n", link, depth);
		return;
	}

	route = get_route(pkg->local_route_hi, pkg->local_route_lo);

	xd = tb_xdomain_find_by_uuid(tb, &pkg->remote_uuid);
	if (xd) {
		u8 xd_phy_port, phy_port;

		xd_phy_port = phy_port_from_route(xd->route, xd->depth);
		phy_port = phy_port_from_route(route, depth);

		if (xd->depth == depth && xd_phy_port == phy_port) {
			update_xdomain(xd, route, link);
			tb_xdomain_put(xd);
			return;
		}

		/*
		 * If we find an existing XDomain connection remove it
		 * now. We need to go through login handshake and
		 * everything anyway to be able to re-establish the
		 * connection.
		 */
		remove_xdomain(xd);
		tb_xdomain_put(xd);
	}

	/*
	 * Look if there already exists an XDomain in the same place
	 * than the new one and in that case remove it because it is
	 * most likely another host that got disconnected.
	 */
	xd = tb_xdomain_find_by_link_depth(tb, link, depth);
	if (!xd) {
		u8 dual_link;

		dual_link = dual_link_from_link(link);
		if (dual_link)
			xd = tb_xdomain_find_by_link_depth(tb, dual_link,
							   depth);
	}
	if (xd) {
		remove_xdomain(xd);
		tb_xdomain_put(xd);
	}

	/*
	 * If the user disconnected a switch during suspend and
	 * connected another host to the same port, remove the switch
	 * first.
	 */
	sw = tb_switch_find_by_route(tb, route);
	if (sw) {
		remove_switch(sw);
		tb_switch_put(sw);
	}

	sw = tb_switch_find_by_link_depth(tb, link, depth);
	if (!sw) {
		tb_warn(tb, "no switch exists at %u.%u, ignoring\n", link,
			depth);
		return;
	}

	add_xdomain(sw, route, &pkg->local_uuid, &pkg->remote_uuid, link,
		    depth);
	tb_switch_put(sw);
}