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
typedef  int u32 ;
struct tb_switch {int cap_lc; } ;
struct tb_port {int /*<<< orphan*/  port; struct tb_switch* sw; } ;

/* Variables and functions */
 int TB_LC_DESC_PORT_SIZE_MASK ; 
 int TB_LC_DESC_PORT_SIZE_SHIFT ; 
 int TB_LC_DESC_SIZE_MASK ; 
 int TB_LC_DESC_SIZE_SHIFT ; 
 int read_lc_desc (struct tb_switch*,int*) ; 
 int tb_phy_port_from_link (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int find_port_lc_cap(struct tb_port *port)
{
	struct tb_switch *sw = port->sw;
	int start, phys, ret, size;
	u32 desc;

	ret = read_lc_desc(sw, &desc);
	if (ret)
		return ret;

	/* Start of port LC registers */
	start = (desc & TB_LC_DESC_SIZE_MASK) >> TB_LC_DESC_SIZE_SHIFT;
	size = (desc & TB_LC_DESC_PORT_SIZE_MASK) >> TB_LC_DESC_PORT_SIZE_SHIFT;
	phys = tb_phy_port_from_link(port->port);

	return sw->cap_lc + start + phys * size;
}