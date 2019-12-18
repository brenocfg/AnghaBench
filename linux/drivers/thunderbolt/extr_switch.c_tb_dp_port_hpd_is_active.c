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
struct tb_port {scalar_t__ cap_adap; } ;

/* Variables and functions */
 int /*<<< orphan*/  TB_CFG_PORT ; 
 int TB_DP_HDP ; 
 int tb_port_read (struct tb_port*,int*,int /*<<< orphan*/ ,scalar_t__,int) ; 

int tb_dp_port_hpd_is_active(struct tb_port *port)
{
	u32 data;
	int ret;

	ret = tb_port_read(port, &data, TB_CFG_PORT, port->cap_adap + 2, 1);
	if (ret)
		return ret;

	return !!(data & TB_DP_HDP);
}