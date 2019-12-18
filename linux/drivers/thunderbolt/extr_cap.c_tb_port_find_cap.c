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
struct tb_port {int dummy; } ;
typedef  enum tb_port_cap { ____Placeholder_tb_port_cap } tb_port_cap ;

/* Variables and functions */
 int __tb_port_find_cap (struct tb_port*,int) ; 
 int /*<<< orphan*/  tb_port_dummy_read (struct tb_port*) ; 
 int tb_port_enable_tmu (struct tb_port*,int) ; 

int tb_port_find_cap(struct tb_port *port, enum tb_port_cap cap)
{
	int ret;

	ret = tb_port_enable_tmu(port, true);
	if (ret)
		return ret;

	ret = __tb_port_find_cap(port, cap);

	tb_port_dummy_read(port);
	tb_port_enable_tmu(port, false);

	return ret;
}