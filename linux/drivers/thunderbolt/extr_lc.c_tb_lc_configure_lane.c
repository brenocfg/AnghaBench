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
typedef  int /*<<< orphan*/  u32 ;
struct tb_switch {int generation; } ;
struct tb_port {int port; struct tb_switch* sw; } ;

/* Variables and functions */
 int /*<<< orphan*/  TB_CFG_SWITCH ; 
 scalar_t__ TB_LC_SX_CTRL ; 
 int /*<<< orphan*/  TB_LC_SX_CTRL_L1C ; 
 int /*<<< orphan*/  TB_LC_SX_CTRL_L2C ; 
 int /*<<< orphan*/  TB_LC_SX_CTRL_UPSTREAM ; 
 int find_port_lc_cap (struct tb_port*) ; 
 int tb_is_upstream_port (struct tb_port*) ; 
 int tb_sw_read (struct tb_switch*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int tb_sw_write (struct tb_switch*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int) ; 

__attribute__((used)) static int tb_lc_configure_lane(struct tb_port *port, bool configure)
{
	bool upstream = tb_is_upstream_port(port);
	struct tb_switch *sw = port->sw;
	u32 ctrl, lane;
	int cap, ret;

	if (sw->generation < 2)
		return 0;

	cap = find_port_lc_cap(port);
	if (cap < 0)
		return cap;

	ret = tb_sw_read(sw, &ctrl, TB_CFG_SWITCH, cap + TB_LC_SX_CTRL, 1);
	if (ret)
		return ret;

	/* Resolve correct lane */
	if (port->port % 2)
		lane = TB_LC_SX_CTRL_L1C;
	else
		lane = TB_LC_SX_CTRL_L2C;

	if (configure) {
		ctrl |= lane;
		if (upstream)
			ctrl |= TB_LC_SX_CTRL_UPSTREAM;
	} else {
		ctrl &= ~lane;
		if (upstream)
			ctrl &= ~TB_LC_SX_CTRL_UPSTREAM;
	}

	return tb_sw_write(sw, &ctrl, TB_CFG_SWITCH, cap + TB_LC_SX_CTRL, 1);
}