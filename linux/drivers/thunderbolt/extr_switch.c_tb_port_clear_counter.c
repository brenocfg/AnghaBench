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
struct tb_port {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TB_CFG_COUNTERS ; 
 int /*<<< orphan*/  tb_port_dbg (struct tb_port*,char*,int) ; 
 int tb_port_write (struct tb_port*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 

int tb_port_clear_counter(struct tb_port *port, int counter)
{
	u32 zero[3] = { 0, 0, 0 };
	tb_port_dbg(port, "clearing counter %d\n", counter);
	return tb_port_write(port, zero, TB_CFG_COUNTERS, 3 * counter, 3);
}