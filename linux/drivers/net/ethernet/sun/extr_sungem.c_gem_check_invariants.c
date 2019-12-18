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
struct pci_dev {scalar_t__ vendor; scalar_t__ device; } ;
struct gem {scalar_t__ phy_type; int tx_fifo_sz; int rx_fifo_sz; int swrst_base; int mii_phy_addr; scalar_t__ regs; int /*<<< orphan*/  of_node; struct pci_dev* pdev; } ;

/* Variables and functions */
 int GREG_SWRST_CACHE_SHIFT ; 
 scalar_t__ MAC_XIFCFG ; 
 int MAC_XIFCFG_OE ; 
 scalar_t__ MIF_CFG ; 
 int MIF_CFG_BBMODE ; 
 int MIF_CFG_MDI0 ; 
 int MIF_CFG_MDI1 ; 
 int MIF_CFG_POLL ; 
 int MIF_CFG_PSELECT ; 
 int /*<<< orphan*/  MII_BMCR ; 
 scalar_t__ PCI_DEVICE_ID_APPLE_K2_GMAC ; 
 scalar_t__ PCI_DEVICE_ID_SUN_GEM ; 
 scalar_t__ PCI_DEVICE_ID_SUN_RIO_GEM ; 
 scalar_t__ PCI_VENDOR_ID_APPLE ; 
 scalar_t__ PCI_VENDOR_ID_SUN ; 
 scalar_t__ PCS_DMODE ; 
 int PCS_DMODE_MGM ; 
 scalar_t__ RXDMA_FSZ ; 
 scalar_t__ TXDMA_FSZ ; 
 char* of_get_property (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ phy_mii_mdio0 ; 
 scalar_t__ phy_mii_mdio1 ; 
 void* phy_serdes ; 
 scalar_t__ phy_serialink ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int sungem_phy_read (struct gem*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int gem_check_invariants(struct gem *gp)
{
	struct pci_dev *pdev = gp->pdev;
	u32 mif_cfg;

	/* On Apple's sungem, we can't rely on registers as the chip
	 * was been powered down by the firmware. The PHY is looked
	 * up later on.
	 */
	if (pdev->vendor == PCI_VENDOR_ID_APPLE) {
		gp->phy_type = phy_mii_mdio0;
		gp->tx_fifo_sz = readl(gp->regs + TXDMA_FSZ) * 64;
		gp->rx_fifo_sz = readl(gp->regs + RXDMA_FSZ) * 64;
		gp->swrst_base = 0;

		mif_cfg = readl(gp->regs + MIF_CFG);
		mif_cfg &= ~(MIF_CFG_PSELECT|MIF_CFG_POLL|MIF_CFG_BBMODE|MIF_CFG_MDI1);
		mif_cfg |= MIF_CFG_MDI0;
		writel(mif_cfg, gp->regs + MIF_CFG);
		writel(PCS_DMODE_MGM, gp->regs + PCS_DMODE);
		writel(MAC_XIFCFG_OE, gp->regs + MAC_XIFCFG);

		/* We hard-code the PHY address so we can properly bring it out of
		 * reset later on, we can't really probe it at this point, though
		 * that isn't an issue.
		 */
		if (gp->pdev->device == PCI_DEVICE_ID_APPLE_K2_GMAC)
			gp->mii_phy_addr = 1;
		else
			gp->mii_phy_addr = 0;

		return 0;
	}

	mif_cfg = readl(gp->regs + MIF_CFG);

	if (pdev->vendor == PCI_VENDOR_ID_SUN &&
	    pdev->device == PCI_DEVICE_ID_SUN_RIO_GEM) {
		/* One of the MII PHYs _must_ be present
		 * as this chip has no gigabit PHY.
		 */
		if ((mif_cfg & (MIF_CFG_MDI0 | MIF_CFG_MDI1)) == 0) {
			pr_err("RIO GEM lacks MII phy, mif_cfg[%08x]\n",
			       mif_cfg);
			return -1;
		}
	}

	/* Determine initial PHY interface type guess.  MDIO1 is the
	 * external PHY and thus takes precedence over MDIO0.
	 */

	if (mif_cfg & MIF_CFG_MDI1) {
		gp->phy_type = phy_mii_mdio1;
		mif_cfg |= MIF_CFG_PSELECT;
		writel(mif_cfg, gp->regs + MIF_CFG);
	} else if (mif_cfg & MIF_CFG_MDI0) {
		gp->phy_type = phy_mii_mdio0;
		mif_cfg &= ~MIF_CFG_PSELECT;
		writel(mif_cfg, gp->regs + MIF_CFG);
	} else {
#ifdef CONFIG_SPARC
		const char *p;

		p = of_get_property(gp->of_node, "shared-pins", NULL);
		if (p && !strcmp(p, "serdes"))
			gp->phy_type = phy_serdes;
		else
#endif
			gp->phy_type = phy_serialink;
	}
	if (gp->phy_type == phy_mii_mdio1 ||
	    gp->phy_type == phy_mii_mdio0) {
		int i;

		for (i = 0; i < 32; i++) {
			gp->mii_phy_addr = i;
			if (sungem_phy_read(gp, MII_BMCR) != 0xffff)
				break;
		}
		if (i == 32) {
			if (pdev->device != PCI_DEVICE_ID_SUN_GEM) {
				pr_err("RIO MII phy will not respond\n");
				return -1;
			}
			gp->phy_type = phy_serdes;
		}
	}

	/* Fetch the FIFO configurations now too. */
	gp->tx_fifo_sz = readl(gp->regs + TXDMA_FSZ) * 64;
	gp->rx_fifo_sz = readl(gp->regs + RXDMA_FSZ) * 64;

	if (pdev->vendor == PCI_VENDOR_ID_SUN) {
		if (pdev->device == PCI_DEVICE_ID_SUN_GEM) {
			if (gp->tx_fifo_sz != (9 * 1024) ||
			    gp->rx_fifo_sz != (20 * 1024)) {
				pr_err("GEM has bogus fifo sizes tx(%d) rx(%d)\n",
				       gp->tx_fifo_sz, gp->rx_fifo_sz);
				return -1;
			}
			gp->swrst_base = 0;
		} else {
			if (gp->tx_fifo_sz != (2 * 1024) ||
			    gp->rx_fifo_sz != (2 * 1024)) {
				pr_err("RIO GEM has bogus fifo sizes tx(%d) rx(%d)\n",
				       gp->tx_fifo_sz, gp->rx_fifo_sz);
				return -1;
			}
			gp->swrst_base = (64 / 4) << GREG_SWRST_CACHE_SHIFT;
		}
	}

	return 0;
}