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
struct tb_port {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TB_CFG_PORT ; 
 int TB_PORT_LCA_MASK ; 
 int TB_PORT_LCA_SHIFT ; 
 int tb_port_read (struct tb_port*,int*,int /*<<< orphan*/ ,int,int) ; 
 int tb_port_write (struct tb_port*,int*,int /*<<< orphan*/ ,int,int) ; 

int tb_port_set_initial_credits(struct tb_port *port, u32 credits)
{
	u32 data;
	int ret;

	ret = tb_port_read(port, &data, TB_CFG_PORT, 5, 1);
	if (ret)
		return ret;

	data &= ~TB_PORT_LCA_MASK;
	data |= (credits << TB_PORT_LCA_SHIFT) & TB_PORT_LCA_MASK;

	return tb_port_write(port, &data, TB_CFG_PORT, 5, 1);
}