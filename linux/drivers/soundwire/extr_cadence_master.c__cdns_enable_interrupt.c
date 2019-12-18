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
struct sdw_cdns {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CDNS_MCP_INTMASK ; 
 int CDNS_MCP_INT_CTRL_CLASH ; 
 int CDNS_MCP_INT_DATA_CLASH ; 
 int CDNS_MCP_INT_IRQ ; 
 int CDNS_MCP_INT_PARITY ; 
 int CDNS_MCP_INT_RX_WL ; 
 int CDNS_MCP_INT_SLAVE_MASK ; 
 int /*<<< orphan*/  CDNS_MCP_SLAVE_INTMASK0 ; 
 int CDNS_MCP_SLAVE_INTMASK0_MASK ; 
 int /*<<< orphan*/  CDNS_MCP_SLAVE_INTMASK1 ; 
 int CDNS_MCP_SLAVE_INTMASK1_MASK ; 
 int /*<<< orphan*/  cdns_writel (struct sdw_cdns*,int /*<<< orphan*/ ,int) ; 
 int interrupt_mask ; 

__attribute__((used)) static int _cdns_enable_interrupt(struct sdw_cdns *cdns)
{
	u32 mask;

	cdns_writel(cdns, CDNS_MCP_SLAVE_INTMASK0,
		    CDNS_MCP_SLAVE_INTMASK0_MASK);
	cdns_writel(cdns, CDNS_MCP_SLAVE_INTMASK1,
		    CDNS_MCP_SLAVE_INTMASK1_MASK);

	/* enable detection of all slave state changes */
	mask = CDNS_MCP_INT_SLAVE_MASK;

	/* enable detection of bus issues */
	mask |= CDNS_MCP_INT_CTRL_CLASH | CDNS_MCP_INT_DATA_CLASH |
		CDNS_MCP_INT_PARITY;

	/* no detection of port interrupts for now */

	/* enable detection of RX fifo level */
	mask |= CDNS_MCP_INT_RX_WL;

	/*
	 * CDNS_MCP_INT_IRQ needs to be set otherwise all previous
	 * settings are irrelevant
	 */
	mask |= CDNS_MCP_INT_IRQ;

	if (interrupt_mask) /* parameter override */
		mask = interrupt_mask;

	cdns_writel(cdns, CDNS_MCP_INTMASK, mask);

	return 0;
}