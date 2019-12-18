#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_9__ {TYPE_3__* def; } ;
struct gem {scalar_t__ phy_type; TYPE_4__ phy_mii; int /*<<< orphan*/  dev; int /*<<< orphan*/  lstate; scalar_t__ timer_ticks; int /*<<< orphan*/  mii_phy_addr; scalar_t__ regs; TYPE_1__* pdev; int /*<<< orphan*/  of_node; } ;
struct TYPE_8__ {char* name; TYPE_2__* ops; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* init ) (TYPE_4__*) ;} ;
struct TYPE_6__ {scalar_t__ vendor; scalar_t__ device; } ;

/* Variables and functions */
 int /*<<< orphan*/  BMCR_RESET ; 
 scalar_t__ MIF_CFG ; 
 int MIF_CFG_BBMODE ; 
 int /*<<< orphan*/  MII_BMCR ; 
 scalar_t__ PCI_DEVICE_ID_SUN_GEM ; 
 scalar_t__ PCI_VENDOR_ID_APPLE ; 
 scalar_t__ PCI_VENDOR_ID_SUN ; 
 scalar_t__ PCS_DMODE ; 
 int PCS_DMODE_ESM ; 
 int PCS_DMODE_GMOE ; 
 int PCS_DMODE_MGM ; 
 int PCS_DMODE_SM ; 
 int /*<<< orphan*/  PMAC_FTR_GMAC_PHY_RESET ; 
 int /*<<< orphan*/  gem_begin_auto_negotiation (struct gem*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gem_pcs_reinit_adv (struct gem*) ; 
 int /*<<< orphan*/  gem_pcs_reset (struct gem*) ; 
 int /*<<< orphan*/  link_down ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  netdev_info (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  netdev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  netif_carrier_off (int /*<<< orphan*/ ) ; 
 scalar_t__ phy_mii_mdio0 ; 
 scalar_t__ phy_mii_mdio1 ; 
 scalar_t__ phy_serialink ; 
 int /*<<< orphan*/  pmac_call_feature (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*) ; 
 int /*<<< orphan*/  sungem_phy_probe (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int sungem_phy_read (struct gem*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sungem_phy_write (struct gem*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void gem_init_phy(struct gem *gp)
{
	u32 mifcfg;

	/* Revert MIF CFG setting done on stop_phy */
	mifcfg = readl(gp->regs + MIF_CFG);
	mifcfg &= ~MIF_CFG_BBMODE;
	writel(mifcfg, gp->regs + MIF_CFG);

	if (gp->pdev->vendor == PCI_VENDOR_ID_APPLE) {
		int i;

		/* Those delay sucks, the HW seem to love them though, I'll
		 * serisouly consider breaking some locks here to be able
		 * to schedule instead
		 */
		for (i = 0; i < 3; i++) {
#ifdef CONFIG_PPC_PMAC
			pmac_call_feature(PMAC_FTR_GMAC_PHY_RESET, gp->of_node, 0, 0);
			msleep(20);
#endif
			/* Some PHYs used by apple have problem getting back to us,
			 * we do an additional reset here
			 */
			sungem_phy_write(gp, MII_BMCR, BMCR_RESET);
			msleep(20);
			if (sungem_phy_read(gp, MII_BMCR) != 0xffff)
				break;
			if (i == 2)
				netdev_warn(gp->dev, "GMAC PHY not responding !\n");
		}
	}

	if (gp->pdev->vendor == PCI_VENDOR_ID_SUN &&
	    gp->pdev->device == PCI_DEVICE_ID_SUN_GEM) {
		u32 val;

		/* Init datapath mode register. */
		if (gp->phy_type == phy_mii_mdio0 ||
		    gp->phy_type == phy_mii_mdio1) {
			val = PCS_DMODE_MGM;
		} else if (gp->phy_type == phy_serialink) {
			val = PCS_DMODE_SM | PCS_DMODE_GMOE;
		} else {
			val = PCS_DMODE_ESM;
		}

		writel(val, gp->regs + PCS_DMODE);
	}

	if (gp->phy_type == phy_mii_mdio0 ||
	    gp->phy_type == phy_mii_mdio1) {
		/* Reset and detect MII PHY */
		sungem_phy_probe(&gp->phy_mii, gp->mii_phy_addr);

		/* Init PHY */
		if (gp->phy_mii.def && gp->phy_mii.def->ops->init)
			gp->phy_mii.def->ops->init(&gp->phy_mii);
	} else {
		gem_pcs_reset(gp);
		gem_pcs_reinit_adv(gp);
	}

	/* Default aneg parameters */
	gp->timer_ticks = 0;
	gp->lstate = link_down;
	netif_carrier_off(gp->dev);

	/* Print things out */
	if (gp->phy_type == phy_mii_mdio0 ||
	    gp->phy_type == phy_mii_mdio1)
		netdev_info(gp->dev, "Found %s PHY\n",
			    gp->phy_mii.def ? gp->phy_mii.def->name : "no");

	gem_begin_auto_negotiation(gp, NULL);
}