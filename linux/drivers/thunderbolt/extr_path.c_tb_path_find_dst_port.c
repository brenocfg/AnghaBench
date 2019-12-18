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
struct tb_switch {struct tb_port* ports; } ;
struct tb_regs_hop {size_t out_port; int next_hop; int /*<<< orphan*/  enable; } ;
struct tb_port {struct tb_port* remote; struct tb_switch* sw; } ;

/* Variables and functions */
 int /*<<< orphan*/  TB_CFG_HOPS ; 
 int TB_PATH_MAX_HOPS ; 
 int tb_port_read (struct tb_port*,struct tb_regs_hop*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  tb_port_warn (struct tb_port*,char*,int) ; 

__attribute__((used)) static struct tb_port *tb_path_find_dst_port(struct tb_port *src, int src_hopid,
					     int dst_hopid)
{
	struct tb_port *port, *out_port = NULL;
	struct tb_regs_hop hop;
	struct tb_switch *sw;
	int i, ret, hopid;

	hopid = src_hopid;
	port = src;

	for (i = 0; port && i < TB_PATH_MAX_HOPS; i++) {
		sw = port->sw;

		ret = tb_port_read(port, &hop, TB_CFG_HOPS, 2 * hopid, 2);
		if (ret) {
			tb_port_warn(port, "failed to read path at %d\n", hopid);
			return NULL;
		}

		if (!hop.enable)
			return NULL;

		out_port = &sw->ports[hop.out_port];
		hopid = hop.next_hop;
		port = out_port->remote;
	}

	return out_port && hopid == dst_hopid ? out_port : NULL;
}