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
struct mvpp2_port {scalar_t__ base; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 scalar_t__ MVPP2_GMAC_CTRL_2_REG ; 
 int MVPP2_GMAC_PORT_RESET_MASK ; 
 int /*<<< orphan*/ * mvpp2_ethtool_regs ; 
 int /*<<< orphan*/  mvpp2_read_count (struct mvpp2_port*,int /*<<< orphan*/ *) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void mvpp2_port_reset(struct mvpp2_port *port)
{
	u32 val;
	unsigned int i;

	/* Read the GOP statistics to reset the hardware counters */
	for (i = 0; i < ARRAY_SIZE(mvpp2_ethtool_regs); i++)
		mvpp2_read_count(port, &mvpp2_ethtool_regs[i]);

	val = readl(port->base + MVPP2_GMAC_CTRL_2_REG) |
	      MVPP2_GMAC_PORT_RESET_MASK;
	writel(val, port->base + MVPP2_GMAC_CTRL_2_REG);
}