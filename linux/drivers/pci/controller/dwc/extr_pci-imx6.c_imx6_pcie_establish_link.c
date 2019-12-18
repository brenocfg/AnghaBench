#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct imx6_pcie {int link_gen; TYPE_1__* drvdata; struct dw_pcie* pci; } ;
struct dw_pcie {struct device* dev; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int IMX6_PCIE_FLAG_IMX6_SPEED_CHANGE ; 
 int /*<<< orphan*/  PCIE_LINK_WIDTH_SPEED_CONTROL ; 
 int /*<<< orphan*/  PCIE_PORT_DEBUG0 ; 
 int /*<<< orphan*/  PCIE_PORT_DEBUG1 ; 
 int /*<<< orphan*/  PCIE_RC_LCR ; 
 int PCIE_RC_LCR_MAX_LINK_SPEEDS_GEN1 ; 
 int PCIE_RC_LCR_MAX_LINK_SPEEDS_GEN2 ; 
 int PCIE_RC_LCR_MAX_LINK_SPEEDS_MASK ; 
 int /*<<< orphan*/  PCIE_RC_LCSR ; 
 int PORT_LOGIC_SPEED_CHANGE ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int,int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,...) ; 
 int dw_pcie_readl_dbi (struct dw_pcie*,int /*<<< orphan*/ ) ; 
 int dw_pcie_wait_for_link (struct dw_pcie*) ; 
 int /*<<< orphan*/  dw_pcie_writel_dbi (struct dw_pcie*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  imx6_pcie_ltssm_enable (struct device*) ; 
 int /*<<< orphan*/  imx6_pcie_reset_phy (struct imx6_pcie*) ; 
 int imx6_pcie_wait_for_speed_change (struct imx6_pcie*) ; 

__attribute__((used)) static int imx6_pcie_establish_link(struct imx6_pcie *imx6_pcie)
{
	struct dw_pcie *pci = imx6_pcie->pci;
	struct device *dev = pci->dev;
	u32 tmp;
	int ret;

	/*
	 * Force Gen1 operation when starting the link.  In case the link is
	 * started in Gen2 mode, there is a possibility the devices on the
	 * bus will not be detected at all.  This happens with PCIe switches.
	 */
	tmp = dw_pcie_readl_dbi(pci, PCIE_RC_LCR);
	tmp &= ~PCIE_RC_LCR_MAX_LINK_SPEEDS_MASK;
	tmp |= PCIE_RC_LCR_MAX_LINK_SPEEDS_GEN1;
	dw_pcie_writel_dbi(pci, PCIE_RC_LCR, tmp);

	/* Start LTSSM. */
	imx6_pcie_ltssm_enable(dev);

	ret = dw_pcie_wait_for_link(pci);
	if (ret)
		goto err_reset_phy;

	if (imx6_pcie->link_gen == 2) {
		/* Allow Gen2 mode after the link is up. */
		tmp = dw_pcie_readl_dbi(pci, PCIE_RC_LCR);
		tmp &= ~PCIE_RC_LCR_MAX_LINK_SPEEDS_MASK;
		tmp |= PCIE_RC_LCR_MAX_LINK_SPEEDS_GEN2;
		dw_pcie_writel_dbi(pci, PCIE_RC_LCR, tmp);

		/*
		 * Start Directed Speed Change so the best possible
		 * speed both link partners support can be negotiated.
		 */
		tmp = dw_pcie_readl_dbi(pci, PCIE_LINK_WIDTH_SPEED_CONTROL);
		tmp |= PORT_LOGIC_SPEED_CHANGE;
		dw_pcie_writel_dbi(pci, PCIE_LINK_WIDTH_SPEED_CONTROL, tmp);

		if (imx6_pcie->drvdata->flags &
		    IMX6_PCIE_FLAG_IMX6_SPEED_CHANGE) {
			/*
			 * On i.MX7, DIRECT_SPEED_CHANGE behaves differently
			 * from i.MX6 family when no link speed transition
			 * occurs and we go Gen1 -> yep, Gen1. The difference
			 * is that, in such case, it will not be cleared by HW
			 * which will cause the following code to report false
			 * failure.
			 */

			ret = imx6_pcie_wait_for_speed_change(imx6_pcie);
			if (ret) {
				dev_err(dev, "Failed to bring link up!\n");
				goto err_reset_phy;
			}
		}

		/* Make sure link training is finished as well! */
		ret = dw_pcie_wait_for_link(pci);
		if (ret) {
			dev_err(dev, "Failed to bring link up!\n");
			goto err_reset_phy;
		}
	} else {
		dev_info(dev, "Link: Gen2 disabled\n");
	}

	tmp = dw_pcie_readl_dbi(pci, PCIE_RC_LCSR);
	dev_info(dev, "Link up, Gen%i\n", (tmp >> 16) & 0xf);
	return 0;

err_reset_phy:
	dev_dbg(dev, "PHY DEBUG_R0=0x%08x DEBUG_R1=0x%08x\n",
		dw_pcie_readl_dbi(pci, PCIE_PORT_DEBUG0),
		dw_pcie_readl_dbi(pci, PCIE_PORT_DEBUG1));
	imx6_pcie_reset_phy(imx6_pcie);
	return ret;
}