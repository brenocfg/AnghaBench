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
struct tb_port {int /*<<< orphan*/  cap_phy; } ;

/* Variables and functions */
 int EINVAL ; 
 int TB_PORT_DISABLED ; 
 int TB_PORT_UNPLUGGED ; 
 int TB_PORT_UP ; 
 int /*<<< orphan*/  msleep (int) ; 
 scalar_t__ tb_is_upstream_port (struct tb_port*) ; 
 int /*<<< orphan*/  tb_port_WARN (struct tb_port*,char*) ; 
 int /*<<< orphan*/  tb_port_dbg (struct tb_port*,char*,...) ; 
 int tb_port_state (struct tb_port*) ; 
 int /*<<< orphan*/  tb_port_warn (struct tb_port*,char*) ; 

int tb_wait_for_port(struct tb_port *port, bool wait_if_unplugged)
{
	int retries = 10;
	int state;
	if (!port->cap_phy) {
		tb_port_WARN(port, "does not have PHY\n");
		return -EINVAL;
	}
	if (tb_is_upstream_port(port)) {
		tb_port_WARN(port, "is the upstream port\n");
		return -EINVAL;
	}

	while (retries--) {
		state = tb_port_state(port);
		if (state < 0)
			return state;
		if (state == TB_PORT_DISABLED) {
			tb_port_dbg(port, "is disabled (state: 0)\n");
			return 0;
		}
		if (state == TB_PORT_UNPLUGGED) {
			if (wait_if_unplugged) {
				/* used during resume */
				tb_port_dbg(port,
					    "is unplugged (state: 7), retrying...\n");
				msleep(100);
				continue;
			}
			tb_port_dbg(port, "is unplugged (state: 7)\n");
			return 0;
		}
		if (state == TB_PORT_UP) {
			tb_port_dbg(port, "is connected, link is up (state: 2)\n");
			return 1;
		}

		/*
		 * After plug-in the state is TB_PORT_CONNECTING. Give it some
		 * time.
		 */
		tb_port_dbg(port,
			    "is connected, link is not up (state: %d), retrying...\n",
			    state);
		msleep(100);
	}
	tb_port_warn(port,
		     "failed to reach state TB_PORT_UP. Ignoring port...\n");
	return 0;
}