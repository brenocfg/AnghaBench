#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct ssb_sprom {int boardflags_lo; int /*<<< orphan*/  et2phyaddr; int /*<<< orphan*/  et1phyaddr; int /*<<< orphan*/  et0phyaddr; int /*<<< orphan*/ * et2mac; int /*<<< orphan*/ * et1mac; int /*<<< orphan*/ * et0mac; } ;
struct phy_device {int /*<<< orphan*/  dev_flags; TYPE_1__* drv; } ;
struct mii_bus {int dummy; } ;
struct TYPE_13__ {scalar_t__ cmn; struct bcma_device* core; } ;
struct bgmac {int has_robosw; struct mii_bus* mii_bus; int /*<<< orphan*/  phy_connect; int /*<<< orphan*/  cmn_maskset32; int /*<<< orphan*/  get_bus_clock; int /*<<< orphan*/  cco_ctl_maskset; int /*<<< orphan*/  clk_enable; int /*<<< orphan*/  clk_enabled; int /*<<< orphan*/  idm_write; int /*<<< orphan*/  idm_read; int /*<<< orphan*/  write; int /*<<< orphan*/  read; int /*<<< orphan*/  feature_flags; TYPE_7__* dev; int /*<<< orphan*/  phyaddr; TYPE_4__ bcma; TYPE_2__* net_dev; int /*<<< orphan*/  irq; int /*<<< orphan*/  dma_dev; } ;
struct TYPE_12__ {scalar_t__ id; int rev; } ;
struct bcma_device {int core_unit; TYPE_3__ id; TYPE_6__* bus; int /*<<< orphan*/  irq; int /*<<< orphan*/  dma_dev; int /*<<< orphan*/  dev; } ;
struct bcma_chipinfo {int id; int pkg; } ;
struct TYPE_16__ {scalar_t__ of_node; } ;
struct TYPE_14__ {scalar_t__ core; } ;
struct TYPE_15__ {scalar_t__ hosttype; TYPE_5__ drv_gmac_cmn; struct ssb_sprom sprom; struct bcma_chipinfo chipinfo; } ;
struct TYPE_11__ {int /*<<< orphan*/  dev_addr; } ;
struct TYPE_10__ {int phy_id; int phy_id_mask; } ;

/* Variables and functions */
#define  BCMA_CHIP_ID_BCM4707 136 
#define  BCMA_CHIP_ID_BCM47094 135 
#define  BCMA_CHIP_ID_BCM4716 134 
#define  BCMA_CHIP_ID_BCM47162 133 
#define  BCMA_CHIP_ID_BCM4749 132 
#define  BCMA_CHIP_ID_BCM53018 131 
#define  BCMA_CHIP_ID_BCM5357 130 
#define  BCMA_CHIP_ID_BCM53572 129 
#define  BCMA_CHIP_ID_BCM53573 128 
 scalar_t__ BCMA_CORE_4706_MAC_GBIT ; 
 scalar_t__ BCMA_HOSTTYPE_PCI ; 
 int BCMA_PKG_ID_BCM47186 ; 
 int BCMA_PKG_ID_BCM47188 ; 
 int BCMA_PKG_ID_BCM47189 ; 
 int BCMA_PKG_ID_BCM5358 ; 
 int BGMAC_BFL_ENETADM ; 
 int BGMAC_BFL_ENETROBO ; 
 int /*<<< orphan*/  BGMAC_FEAT_CC4_IF_SW_TYPE ; 
 int /*<<< orphan*/  BGMAC_FEAT_CC4_IF_SW_TYPE_RGMII ; 
 int /*<<< orphan*/  BGMAC_FEAT_CC7_IF_TYPE_RGMII ; 
 int /*<<< orphan*/  BGMAC_FEAT_CLKCTLST ; 
 int /*<<< orphan*/  BGMAC_FEAT_CMDCFG_SR_REV4 ; 
 int /*<<< orphan*/  BGMAC_FEAT_CMN_PHY_CTL ; 
 int /*<<< orphan*/  BGMAC_FEAT_FLW_CTRL1 ; 
 int /*<<< orphan*/  BGMAC_FEAT_FLW_CTRL2 ; 
 int /*<<< orphan*/  BGMAC_FEAT_FORCE_SPEED_2500 ; 
 int /*<<< orphan*/  BGMAC_FEAT_IOST_ATTACHED ; 
 int /*<<< orphan*/  BGMAC_FEAT_IRQ_ID_OOB_6 ; 
 int /*<<< orphan*/  BGMAC_FEAT_MISC_PLL_REQ ; 
 int /*<<< orphan*/  BGMAC_FEAT_NO_CLR_MIB ; 
 int /*<<< orphan*/  BGMAC_FEAT_NO_RESET ; 
 int /*<<< orphan*/  BGMAC_FEAT_RX_MASK_SETUP ; 
 int /*<<< orphan*/  BGMAC_FEAT_SET_RXQ_CLK ; 
 int /*<<< orphan*/  BGMAC_FEAT_SW_TYPE_EPHYRMII ; 
 int /*<<< orphan*/  BGMAC_FEAT_SW_TYPE_PHY ; 
 int /*<<< orphan*/  BGMAC_FEAT_SW_TYPE_RGMII ; 
 int /*<<< orphan*/  BGMAC_FEAT_TX_MASK_SETUP ; 
 int /*<<< orphan*/  BGMAC_PHY_MASK ; 
 int /*<<< orphan*/  BGMAC_PHY_NOREGS ; 
 int ENODEV ; 
 int ENOMEM ; 
 int ENOTSUPP ; 
 scalar_t__ IS_ERR (struct mii_bus*) ; 
 scalar_t__ IS_ERR_OR_NULL (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  PHY_BRCM_EN_MASTER_MODE ; 
 int PHY_ID_BCM54210E ; 
 int PTR_ERR (struct mii_bus*) ; 
 int /*<<< orphan*/  bcma_bgmac_cco_ctl_maskset ; 
 int /*<<< orphan*/  bcma_bgmac_clk_enable ; 
 int /*<<< orphan*/  bcma_bgmac_clk_enabled ; 
 int /*<<< orphan*/  bcma_bgmac_cmn_maskset32 ; 
 int /*<<< orphan*/  bcma_bgmac_get_bus_clock ; 
 int /*<<< orphan*/  bcma_bgmac_idm_read ; 
 int /*<<< orphan*/  bcma_bgmac_idm_write ; 
 int /*<<< orphan*/  bcma_bgmac_read ; 
 int /*<<< orphan*/  bcma_bgmac_write ; 
 struct mii_bus* bcma_mdio_mii_register (struct bgmac*) ; 
 int /*<<< orphan*/  bcma_mdio_mii_unregister (struct mii_bus*) ; 
 int /*<<< orphan*/  bcma_phy_connect ; 
 int /*<<< orphan*/  bcma_set_drvdata (struct bcma_device*,struct bgmac*) ; 
 struct bgmac* bgmac_alloc (int /*<<< orphan*/ *) ; 
 int bgmac_enet_probe (struct bgmac*) ; 
 int /*<<< orphan*/  bgmac_is_bcm4707_family (struct bcma_device*) ; 
 int /*<<< orphan*/  bgmac_phy_connect_direct ; 
 int /*<<< orphan*/  dev_err (TYPE_7__*,char*,...) ; 
 int /*<<< orphan*/  dev_info (TYPE_7__*,char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_warn (TYPE_7__*,char*) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 struct phy_device* mdiobus_get_phy (struct mii_bus*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * of_get_mac_address (scalar_t__) ; 

__attribute__((used)) static int bgmac_probe(struct bcma_device *core)
{
	struct bcma_chipinfo *ci = &core->bus->chipinfo;
	struct ssb_sprom *sprom = &core->bus->sprom;
	struct mii_bus *mii_bus;
	struct bgmac *bgmac;
	const u8 *mac = NULL;
	int err;

	bgmac = bgmac_alloc(&core->dev);
	if (!bgmac)
		return -ENOMEM;

	bgmac->bcma.core = core;
	bgmac->dma_dev = core->dma_dev;
	bgmac->irq = core->irq;

	bcma_set_drvdata(core, bgmac);

	if (bgmac->dev->of_node)
		mac = of_get_mac_address(bgmac->dev->of_node);

	/* If no MAC address assigned via device tree, check SPROM */
	if (IS_ERR_OR_NULL(mac)) {
		switch (core->core_unit) {
		case 0:
			mac = sprom->et0mac;
			break;
		case 1:
			mac = sprom->et1mac;
			break;
		case 2:
			mac = sprom->et2mac;
			break;
		default:
			dev_err(bgmac->dev, "Unsupported core_unit %d\n",
				core->core_unit);
			err = -ENOTSUPP;
			goto err;
		}
	}

	ether_addr_copy(bgmac->net_dev->dev_addr, mac);

	/* On BCM4706 we need common core to access PHY */
	if (core->id.id == BCMA_CORE_4706_MAC_GBIT &&
	    !core->bus->drv_gmac_cmn.core) {
		dev_err(bgmac->dev, "GMAC CMN core not found (required for BCM4706)\n");
		err = -ENODEV;
		goto err;
	}
	bgmac->bcma.cmn = core->bus->drv_gmac_cmn.core;

	switch (core->core_unit) {
	case 0:
		bgmac->phyaddr = sprom->et0phyaddr;
		break;
	case 1:
		bgmac->phyaddr = sprom->et1phyaddr;
		break;
	case 2:
		bgmac->phyaddr = sprom->et2phyaddr;
		break;
	}
	bgmac->phyaddr &= BGMAC_PHY_MASK;
	if (bgmac->phyaddr == BGMAC_PHY_MASK) {
		dev_err(bgmac->dev, "No PHY found\n");
		err = -ENODEV;
		goto err;
	}
	dev_info(bgmac->dev, "Found PHY addr: %d%s\n", bgmac->phyaddr,
		 bgmac->phyaddr == BGMAC_PHY_NOREGS ? " (NOREGS)" : "");

	if (!bgmac_is_bcm4707_family(core) &&
	    !(ci->id == BCMA_CHIP_ID_BCM53573 && core->core_unit == 1)) {
		struct phy_device *phydev;

		mii_bus = bcma_mdio_mii_register(bgmac);
		if (IS_ERR(mii_bus)) {
			err = PTR_ERR(mii_bus);
			goto err;
		}
		bgmac->mii_bus = mii_bus;

		phydev = mdiobus_get_phy(bgmac->mii_bus, bgmac->phyaddr);
		if (ci->id == BCMA_CHIP_ID_BCM53573 && phydev &&
		    (phydev->drv->phy_id & phydev->drv->phy_id_mask) == PHY_ID_BCM54210E)
			phydev->dev_flags |= PHY_BRCM_EN_MASTER_MODE;
	}

	if (core->bus->hosttype == BCMA_HOSTTYPE_PCI) {
		dev_err(bgmac->dev, "PCI setup not implemented\n");
		err = -ENOTSUPP;
		goto err1;
	}

	bgmac->has_robosw = !!(sprom->boardflags_lo & BGMAC_BFL_ENETROBO);
	if (bgmac->has_robosw)
		dev_warn(bgmac->dev, "Support for Roboswitch not implemented\n");

	if (sprom->boardflags_lo & BGMAC_BFL_ENETADM)
		dev_warn(bgmac->dev, "Support for ADMtek ethernet switch not implemented\n");

	/* Feature Flags */
	switch (ci->id) {
	/* BCM 471X/535X family */
	case BCMA_CHIP_ID_BCM4716:
		bgmac->feature_flags |= BGMAC_FEAT_CLKCTLST;
		/* fallthrough */
	case BCMA_CHIP_ID_BCM47162:
		bgmac->feature_flags |= BGMAC_FEAT_FLW_CTRL2;
		bgmac->feature_flags |= BGMAC_FEAT_SET_RXQ_CLK;
		break;
	case BCMA_CHIP_ID_BCM5357:
	case BCMA_CHIP_ID_BCM53572:
		bgmac->feature_flags |= BGMAC_FEAT_SET_RXQ_CLK;
		bgmac->feature_flags |= BGMAC_FEAT_CLKCTLST;
		bgmac->feature_flags |= BGMAC_FEAT_FLW_CTRL1;
		bgmac->feature_flags |= BGMAC_FEAT_SW_TYPE_PHY;
		if (ci->pkg == BCMA_PKG_ID_BCM47188 ||
		    ci->pkg == BCMA_PKG_ID_BCM47186) {
			bgmac->feature_flags |= BGMAC_FEAT_SW_TYPE_RGMII;
			bgmac->feature_flags |= BGMAC_FEAT_IOST_ATTACHED;
		}
		if (ci->pkg == BCMA_PKG_ID_BCM5358)
			bgmac->feature_flags |= BGMAC_FEAT_SW_TYPE_EPHYRMII;
		break;
	case BCMA_CHIP_ID_BCM53573:
		bgmac->feature_flags |= BGMAC_FEAT_CLKCTLST;
		bgmac->feature_flags |= BGMAC_FEAT_SET_RXQ_CLK;
		if (ci->pkg == BCMA_PKG_ID_BCM47189)
			bgmac->feature_flags |= BGMAC_FEAT_IOST_ATTACHED;
		if (core->core_unit == 0) {
			bgmac->feature_flags |= BGMAC_FEAT_CC4_IF_SW_TYPE;
			if (ci->pkg == BCMA_PKG_ID_BCM47189)
				bgmac->feature_flags |=
					BGMAC_FEAT_CC4_IF_SW_TYPE_RGMII;
		} else if (core->core_unit == 1) {
			bgmac->feature_flags |= BGMAC_FEAT_IRQ_ID_OOB_6;
			bgmac->feature_flags |= BGMAC_FEAT_CC7_IF_TYPE_RGMII;
		}
		break;
	case BCMA_CHIP_ID_BCM4749:
		bgmac->feature_flags |= BGMAC_FEAT_SET_RXQ_CLK;
		bgmac->feature_flags |= BGMAC_FEAT_CLKCTLST;
		bgmac->feature_flags |= BGMAC_FEAT_FLW_CTRL1;
		bgmac->feature_flags |= BGMAC_FEAT_SW_TYPE_PHY;
		if (ci->pkg == 10) {
			bgmac->feature_flags |= BGMAC_FEAT_SW_TYPE_RGMII;
			bgmac->feature_flags |= BGMAC_FEAT_IOST_ATTACHED;
		}
		break;
	/* bcm4707_family */
	case BCMA_CHIP_ID_BCM4707:
	case BCMA_CHIP_ID_BCM47094:
	case BCMA_CHIP_ID_BCM53018:
		bgmac->feature_flags |= BGMAC_FEAT_CLKCTLST;
		bgmac->feature_flags |= BGMAC_FEAT_NO_RESET;
		bgmac->feature_flags |= BGMAC_FEAT_FORCE_SPEED_2500;
		break;
	default:
		bgmac->feature_flags |= BGMAC_FEAT_CLKCTLST;
		bgmac->feature_flags |= BGMAC_FEAT_SET_RXQ_CLK;
	}

	if (!bgmac_is_bcm4707_family(core) && core->id.rev > 2)
		bgmac->feature_flags |= BGMAC_FEAT_MISC_PLL_REQ;

	if (core->id.id == BCMA_CORE_4706_MAC_GBIT) {
		bgmac->feature_flags |= BGMAC_FEAT_CMN_PHY_CTL;
		bgmac->feature_flags |= BGMAC_FEAT_NO_CLR_MIB;
	}

	if (core->id.rev >= 4) {
		bgmac->feature_flags |= BGMAC_FEAT_CMDCFG_SR_REV4;
		bgmac->feature_flags |= BGMAC_FEAT_TX_MASK_SETUP;
		bgmac->feature_flags |= BGMAC_FEAT_RX_MASK_SETUP;
	}

	bgmac->read = bcma_bgmac_read;
	bgmac->write = bcma_bgmac_write;
	bgmac->idm_read = bcma_bgmac_idm_read;
	bgmac->idm_write = bcma_bgmac_idm_write;
	bgmac->clk_enabled = bcma_bgmac_clk_enabled;
	bgmac->clk_enable = bcma_bgmac_clk_enable;
	bgmac->cco_ctl_maskset = bcma_bgmac_cco_ctl_maskset;
	bgmac->get_bus_clock = bcma_bgmac_get_bus_clock;
	bgmac->cmn_maskset32 = bcma_bgmac_cmn_maskset32;
	if (bgmac->mii_bus)
		bgmac->phy_connect = bcma_phy_connect;
	else
		bgmac->phy_connect = bgmac_phy_connect_direct;

	err = bgmac_enet_probe(bgmac);
	if (err)
		goto err1;

	return 0;

err1:
	bcma_mdio_mii_unregister(bgmac->mii_bus);
err:
	bcma_set_drvdata(core, NULL);

	return err;
}