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
struct TYPE_2__ {int /*<<< orphan*/  hwparams3; } ;
struct dwc3 {scalar_t__ revision; int hsphy_mode; int /*<<< orphan*/  regs; scalar_t__ dis_u2_freeclk_exists_quirk; scalar_t__ dis_enblslpm_quirk; scalar_t__ dis_u2_susphy_quirk; int /*<<< orphan*/  hsphy_interface; TYPE_1__ hwparams; scalar_t__ dis_del_phy_power_chg_quirk; scalar_t__ dis_u3_susphy_quirk; int /*<<< orphan*/  tx_de_emphasis; scalar_t__ tx_de_emphasis_quirk; scalar_t__ rx_detect_poll_quirk; scalar_t__ lfps_filter_quirk; scalar_t__ del_phy_power_chg_quirk; scalar_t__ del_p1p2p3_quirk; scalar_t__ req_p1p2p3_quirk; scalar_t__ dis_rxdet_inp3_quirk; scalar_t__ u2ss_inp3_quirk; } ;

/* Variables and functions */
 int DWC3_GHWPARAMS3_HSPHY_IFC (int /*<<< orphan*/ ) ; 
#define  DWC3_GHWPARAMS3_HSPHY_IFC_ULPI 131 
#define  DWC3_GHWPARAMS3_HSPHY_IFC_UTMI_ULPI 130 
 int /*<<< orphan*/  DWC3_GUSB2PHYCFG (int /*<<< orphan*/ ) ; 
 int DWC3_GUSB2PHYCFG_ENBLSLPM ; 
 int DWC3_GUSB2PHYCFG_PHYIF (int /*<<< orphan*/ ) ; 
 int DWC3_GUSB2PHYCFG_PHYIF_MASK ; 
 int DWC3_GUSB2PHYCFG_SUSPHY ; 
 int DWC3_GUSB2PHYCFG_U2_FREECLK_EXISTS ; 
 int DWC3_GUSB2PHYCFG_ULPI_UTMI ; 
 int DWC3_GUSB2PHYCFG_USBTRDTIM (int /*<<< orphan*/ ) ; 
 int DWC3_GUSB2PHYCFG_USBTRDTIM_MASK ; 
 int /*<<< orphan*/  DWC3_GUSB3PIPECTL (int /*<<< orphan*/ ) ; 
 int DWC3_GUSB3PIPECTL_DEP1P2P3_EN ; 
 int DWC3_GUSB3PIPECTL_DEPOCHANGE ; 
 int DWC3_GUSB3PIPECTL_DISRXDETINP3 ; 
 int DWC3_GUSB3PIPECTL_LFPSFILT ; 
 int DWC3_GUSB3PIPECTL_REQP1P2P3 ; 
 int DWC3_GUSB3PIPECTL_RX_DETOPOLL ; 
 int DWC3_GUSB3PIPECTL_SUSPHY ; 
 int DWC3_GUSB3PIPECTL_TX_DEEPH (int /*<<< orphan*/ ) ; 
 int DWC3_GUSB3PIPECTL_U2SSINP3OK ; 
 int DWC3_GUSB3PIPECTL_UX_EXIT_PX ; 
 scalar_t__ DWC3_REVISION_194A ; 
#define  USBPHY_INTERFACE_MODE_UTMI 129 
#define  USBPHY_INTERFACE_MODE_UTMIW 128 
 int /*<<< orphan*/  USBTRDTIM_UTMI_16_BIT ; 
 int /*<<< orphan*/  USBTRDTIM_UTMI_8_BIT ; 
 int /*<<< orphan*/  UTMI_PHYIF_16_BIT ; 
 int /*<<< orphan*/  UTMI_PHYIF_8_BIT ; 
 int dwc3_readl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc3_writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strncmp (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int dwc3_phy_setup(struct dwc3 *dwc)
{
	u32 reg;

	reg = dwc3_readl(dwc->regs, DWC3_GUSB3PIPECTL(0));

	/*
	 * Make sure UX_EXIT_PX is cleared as that causes issues with some
	 * PHYs. Also, this bit is not supposed to be used in normal operation.
	 */
	reg &= ~DWC3_GUSB3PIPECTL_UX_EXIT_PX;

	/*
	 * Above 1.94a, it is recommended to set DWC3_GUSB3PIPECTL_SUSPHY
	 * to '0' during coreConsultant configuration. So default value
	 * will be '0' when the core is reset. Application needs to set it
	 * to '1' after the core initialization is completed.
	 */
	if (dwc->revision > DWC3_REVISION_194A)
		reg |= DWC3_GUSB3PIPECTL_SUSPHY;

	if (dwc->u2ss_inp3_quirk)
		reg |= DWC3_GUSB3PIPECTL_U2SSINP3OK;

	if (dwc->dis_rxdet_inp3_quirk)
		reg |= DWC3_GUSB3PIPECTL_DISRXDETINP3;

	if (dwc->req_p1p2p3_quirk)
		reg |= DWC3_GUSB3PIPECTL_REQP1P2P3;

	if (dwc->del_p1p2p3_quirk)
		reg |= DWC3_GUSB3PIPECTL_DEP1P2P3_EN;

	if (dwc->del_phy_power_chg_quirk)
		reg |= DWC3_GUSB3PIPECTL_DEPOCHANGE;

	if (dwc->lfps_filter_quirk)
		reg |= DWC3_GUSB3PIPECTL_LFPSFILT;

	if (dwc->rx_detect_poll_quirk)
		reg |= DWC3_GUSB3PIPECTL_RX_DETOPOLL;

	if (dwc->tx_de_emphasis_quirk)
		reg |= DWC3_GUSB3PIPECTL_TX_DEEPH(dwc->tx_de_emphasis);

	if (dwc->dis_u3_susphy_quirk)
		reg &= ~DWC3_GUSB3PIPECTL_SUSPHY;

	if (dwc->dis_del_phy_power_chg_quirk)
		reg &= ~DWC3_GUSB3PIPECTL_DEPOCHANGE;

	dwc3_writel(dwc->regs, DWC3_GUSB3PIPECTL(0), reg);

	reg = dwc3_readl(dwc->regs, DWC3_GUSB2PHYCFG(0));

	/* Select the HS PHY interface */
	switch (DWC3_GHWPARAMS3_HSPHY_IFC(dwc->hwparams.hwparams3)) {
	case DWC3_GHWPARAMS3_HSPHY_IFC_UTMI_ULPI:
		if (dwc->hsphy_interface &&
				!strncmp(dwc->hsphy_interface, "utmi", 4)) {
			reg &= ~DWC3_GUSB2PHYCFG_ULPI_UTMI;
			break;
		} else if (dwc->hsphy_interface &&
				!strncmp(dwc->hsphy_interface, "ulpi", 4)) {
			reg |= DWC3_GUSB2PHYCFG_ULPI_UTMI;
			dwc3_writel(dwc->regs, DWC3_GUSB2PHYCFG(0), reg);
		} else {
			/* Relying on default value. */
			if (!(reg & DWC3_GUSB2PHYCFG_ULPI_UTMI))
				break;
		}
		/* FALLTHROUGH */
	case DWC3_GHWPARAMS3_HSPHY_IFC_ULPI:
		/* FALLTHROUGH */
	default:
		break;
	}

	switch (dwc->hsphy_mode) {
	case USBPHY_INTERFACE_MODE_UTMI:
		reg &= ~(DWC3_GUSB2PHYCFG_PHYIF_MASK |
		       DWC3_GUSB2PHYCFG_USBTRDTIM_MASK);
		reg |= DWC3_GUSB2PHYCFG_PHYIF(UTMI_PHYIF_8_BIT) |
		       DWC3_GUSB2PHYCFG_USBTRDTIM(USBTRDTIM_UTMI_8_BIT);
		break;
	case USBPHY_INTERFACE_MODE_UTMIW:
		reg &= ~(DWC3_GUSB2PHYCFG_PHYIF_MASK |
		       DWC3_GUSB2PHYCFG_USBTRDTIM_MASK);
		reg |= DWC3_GUSB2PHYCFG_PHYIF(UTMI_PHYIF_16_BIT) |
		       DWC3_GUSB2PHYCFG_USBTRDTIM(USBTRDTIM_UTMI_16_BIT);
		break;
	default:
		break;
	}

	/*
	 * Above 1.94a, it is recommended to set DWC3_GUSB2PHYCFG_SUSPHY to
	 * '0' during coreConsultant configuration. So default value will
	 * be '0' when the core is reset. Application needs to set it to
	 * '1' after the core initialization is completed.
	 */
	if (dwc->revision > DWC3_REVISION_194A)
		reg |= DWC3_GUSB2PHYCFG_SUSPHY;

	if (dwc->dis_u2_susphy_quirk)
		reg &= ~DWC3_GUSB2PHYCFG_SUSPHY;

	if (dwc->dis_enblslpm_quirk)
		reg &= ~DWC3_GUSB2PHYCFG_ENBLSLPM;
	else
		reg |= DWC3_GUSB2PHYCFG_ENBLSLPM;

	if (dwc->dis_u2_freeclk_exists_quirk)
		reg &= ~DWC3_GUSB2PHYCFG_U2_FREECLK_EXISTS;

	dwc3_writel(dwc->regs, DWC3_GUSB2PHYCFG(0), reg);

	return 0;
}