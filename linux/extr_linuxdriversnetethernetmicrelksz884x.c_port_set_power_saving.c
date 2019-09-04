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
struct ksz_port {int first_port; int port_cnt; struct ksz_hw* hw; } ;
struct ksz_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KS884X_PORT_CTRL_4_OFFSET ; 
 int /*<<< orphan*/  PORT_POWER_DOWN ; 
 int /*<<< orphan*/  port_cfg (struct ksz_hw*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void port_set_power_saving(struct ksz_port *port, int enable)
{
	struct ksz_hw *hw = port->hw;
	int i;
	int p;

	for (i = 0, p = port->first_port; i < port->port_cnt; i++, p++)
		port_cfg(hw, p,
			KS884X_PORT_CTRL_4_OFFSET, PORT_POWER_DOWN, enable);
}