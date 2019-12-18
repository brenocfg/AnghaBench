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
struct sdw_cdns {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  CDNS_MCP_INTMASK ; 
 int /*<<< orphan*/  CDNS_MCP_INTSTAT ; 
 int /*<<< orphan*/  CDNS_MCP_INT_SLAVE_MASK ; 
 int /*<<< orphan*/  CDNS_MCP_SLAVE_INTSTAT0 ; 
 int /*<<< orphan*/  CDNS_MCP_SLAVE_INTSTAT1 ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  cdns_readl (struct sdw_cdns*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cdns_update_slave_status (struct sdw_cdns*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cdns_updatel (struct sdw_cdns*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cdns_writel (struct sdw_cdns*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg_ratelimited (int /*<<< orphan*/ ,char*) ; 

irqreturn_t sdw_cdns_thread(int irq, void *dev_id)
{
	struct sdw_cdns *cdns = dev_id;
	u32 slave0, slave1;

	dev_dbg_ratelimited(cdns->dev, "Slave status change\n");

	slave0 = cdns_readl(cdns, CDNS_MCP_SLAVE_INTSTAT0);
	slave1 = cdns_readl(cdns, CDNS_MCP_SLAVE_INTSTAT1);

	cdns_update_slave_status(cdns, slave0, slave1);
	cdns_writel(cdns, CDNS_MCP_SLAVE_INTSTAT0, slave0);
	cdns_writel(cdns, CDNS_MCP_SLAVE_INTSTAT1, slave1);

	/* clear and unmask Slave interrupt now */
	cdns_writel(cdns, CDNS_MCP_INTSTAT, CDNS_MCP_INT_SLAVE_MASK);
	cdns_updatel(cdns, CDNS_MCP_INTMASK,
		     CDNS_MCP_INT_SLAVE_MASK, CDNS_MCP_INT_SLAVE_MASK);

	return IRQ_HANDLED;
}