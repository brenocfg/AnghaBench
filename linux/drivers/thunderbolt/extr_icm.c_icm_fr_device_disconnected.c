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
typedef  int u8 ;
struct tb_switch {int dummy; } ;
struct tb {int dummy; } ;
struct icm_pkg_header {int dummy; } ;
struct icm_fr_event_device_disconnected {int link_info; } ;

/* Variables and functions */
 int ICM_LINK_INFO_DEPTH_MASK ; 
 int ICM_LINK_INFO_DEPTH_SHIFT ; 
 int ICM_LINK_INFO_LINK_MASK ; 
 int ICM_MAX_LINK ; 
 int TB_SWITCH_MAX_DEPTH ; 
 int /*<<< orphan*/  remove_switch (struct tb_switch*) ; 
 struct tb_switch* tb_switch_find_by_link_depth (struct tb*,int,int) ; 
 int /*<<< orphan*/  tb_switch_put (struct tb_switch*) ; 
 int /*<<< orphan*/  tb_warn (struct tb*,char*,int,int) ; 

__attribute__((used)) static void
icm_fr_device_disconnected(struct tb *tb, const struct icm_pkg_header *hdr)
{
	const struct icm_fr_event_device_disconnected *pkg =
		(const struct icm_fr_event_device_disconnected *)hdr;
	struct tb_switch *sw;
	u8 link, depth;

	link = pkg->link_info & ICM_LINK_INFO_LINK_MASK;
	depth = (pkg->link_info & ICM_LINK_INFO_DEPTH_MASK) >>
		ICM_LINK_INFO_DEPTH_SHIFT;

	if (link > ICM_MAX_LINK || depth > TB_SWITCH_MAX_DEPTH) {
		tb_warn(tb, "invalid topology %u.%u, ignoring\n", link, depth);
		return;
	}

	sw = tb_switch_find_by_link_depth(tb, link, depth);
	if (!sw) {
		tb_warn(tb, "no switch exists at %u.%u, ignoring\n", link,
			depth);
		return;
	}

	remove_switch(sw);
	tb_switch_put(sw);
}