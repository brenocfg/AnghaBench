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
struct nwl_pcie {struct device* dev; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int MSGF_MISC_SR_CORR_AER ; 
 int MSGF_MISC_SR_E_ADDR_ERR ; 
 int MSGF_MISC_SR_FATAL_AER ; 
 int MSGF_MISC_SR_FATAL_DEV ; 
 int MSGF_MISC_SR_I_ADDR_ERR ; 
 int MSGF_MISC_SR_MASKALL ; 
 int MSGF_MISC_SR_MASTER_ERR ; 
 int MSGF_MISC_SR_NON_FATAL_AER ; 
 int MSGF_MISC_SR_NON_FATAL_DEV ; 
 int MSGF_MISC_SR_RXMSG_OVER ; 
 int MSGF_MISC_SR_SLAVE_ERR ; 
 int MSGF_MISC_SR_UR_DETECT ; 
 int /*<<< orphan*/  MSGF_MISC_STATUS ; 
 int MSGF_MSIC_SR_LINK_AUTO_BWIDTH ; 
 int MSGF_MSIC_SR_LINK_BWIDTH ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 int nwl_bridge_readl (struct nwl_pcie*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nwl_bridge_writel (struct nwl_pcie*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t nwl_pcie_misc_handler(int irq, void *data)
{
	struct nwl_pcie *pcie = data;
	struct device *dev = pcie->dev;
	u32 misc_stat;

	/* Checking for misc interrupts */
	misc_stat = nwl_bridge_readl(pcie, MSGF_MISC_STATUS) &
				     MSGF_MISC_SR_MASKALL;
	if (!misc_stat)
		return IRQ_NONE;

	if (misc_stat & MSGF_MISC_SR_RXMSG_OVER)
		dev_err(dev, "Received Message FIFO Overflow\n");

	if (misc_stat & MSGF_MISC_SR_SLAVE_ERR)
		dev_err(dev, "Slave error\n");

	if (misc_stat & MSGF_MISC_SR_MASTER_ERR)
		dev_err(dev, "Master error\n");

	if (misc_stat & MSGF_MISC_SR_I_ADDR_ERR)
		dev_err(dev, "In Misc Ingress address translation error\n");

	if (misc_stat & MSGF_MISC_SR_E_ADDR_ERR)
		dev_err(dev, "In Misc Egress address translation error\n");

	if (misc_stat & MSGF_MISC_SR_FATAL_AER)
		dev_err(dev, "Fatal Error in AER Capability\n");

	if (misc_stat & MSGF_MISC_SR_NON_FATAL_AER)
		dev_err(dev, "Non-Fatal Error in AER Capability\n");

	if (misc_stat & MSGF_MISC_SR_CORR_AER)
		dev_err(dev, "Correctable Error in AER Capability\n");

	if (misc_stat & MSGF_MISC_SR_UR_DETECT)
		dev_err(dev, "Unsupported request Detected\n");

	if (misc_stat & MSGF_MISC_SR_NON_FATAL_DEV)
		dev_err(dev, "Non-Fatal Error Detected\n");

	if (misc_stat & MSGF_MISC_SR_FATAL_DEV)
		dev_err(dev, "Fatal Error Detected\n");

	if (misc_stat & MSGF_MSIC_SR_LINK_AUTO_BWIDTH)
		dev_info(dev, "Link Autonomous Bandwidth Management Status bit set\n");

	if (misc_stat & MSGF_MSIC_SR_LINK_BWIDTH)
		dev_info(dev, "Link Bandwidth Management Status bit set\n");

	/* Clear misc interrupt status */
	nwl_bridge_writel(pcie, misc_stat, MSGF_MISC_STATUS);

	return IRQ_HANDLED;
}