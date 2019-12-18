#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_6__ {int speed; int ahbcfg; scalar_t__ service_interval; int /*<<< orphan*/  external_id_pin_ctl; scalar_t__ ipg_isoc_en; int /*<<< orphan*/  phy_type; } ;
struct dwc2_hsotg {int num_of_eps; int /*<<< orphan*/  dev; int /*<<< orphan*/  lx_state; TYPE_2__ params; TYPE_3__** eps_out; scalar_t__ dedicated_fifos; TYPE_1__** eps_in; } ;
struct TYPE_8__ {int /*<<< orphan*/  maxpacket; } ;
struct TYPE_7__ {TYPE_4__ ep; } ;
struct TYPE_5__ {TYPE_4__ ep; } ;

/* Variables and functions */
 int /*<<< orphan*/  DAINTMSK ; 
 int /*<<< orphan*/  DCFG ; 
 int DCFG_DESCDMA_EN ; 
 int DCFG_DEVSPD_FS ; 
 int DCFG_DEVSPD_FS48 ; 
 int DCFG_DEVSPD_HS ; 
 int DCFG_DEVSPD_LS ; 
 int DCFG_EPMISCNT (int) ; 
 int DCFG_IPG_ISOC_SUPPORDED ; 
 int /*<<< orphan*/  DCTL ; 
 int DCTL_CGNPINNAK ; 
 int DCTL_CGOUTNAK ; 
 int DCTL_PWRONPRGDONE ; 
 int DCTL_SERVICE_INTERVAL_SUPPORTED ; 
 int DCTL_SFTDISCON ; 
 int /*<<< orphan*/  DIEPCTL0 ; 
 int /*<<< orphan*/  DIEPMSK ; 
 int DIEPMSK_AHBERRMSK ; 
 int DIEPMSK_BNAININTRMSK ; 
 int DIEPMSK_EPDISBLDMSK ; 
 int DIEPMSK_INTKNTXFEMPMSK ; 
 int DIEPMSK_TIMEOUTMSK ; 
 int DIEPMSK_TXFIFOEMPTY ; 
 int DIEPMSK_XFERCOMPLMSK ; 
 int /*<<< orphan*/  DOEPCTL0 ; 
 int /*<<< orphan*/  DOEPMSK ; 
 int DOEPMSK_AHBERRMSK ; 
 int DOEPMSK_BNAMSK ; 
 int DOEPMSK_EPDISBLDMSK ; 
 int DOEPMSK_SETUPMSK ; 
 int DOEPMSK_STSPHSERCVDMSK ; 
 int /*<<< orphan*/  DOEPTSIZ0 ; 
 int /*<<< orphan*/  DWC2_L0 ; 
 int /*<<< orphan*/  DWC2_PHY_TYPE_PARAM_FS ; 
#define  DWC2_SPEED_PARAM_FULL 129 
#define  DWC2_SPEED_PARAM_LOW 128 
 int DXEPCTL_CNAK ; 
 int DXEPCTL_EPENA ; 
 int DXEPCTL_USBACTEP ; 
 int DXEPTSIZ_MC (int) ; 
 int DXEPTSIZ_PKTCNT (int) ; 
 int DXEPTSIZ_XFERSIZE (int) ; 
 int /*<<< orphan*/  ECONNRESET ; 
 int /*<<< orphan*/  GAHBCFG ; 
 int GAHBCFG_DMA_EN ; 
 int GAHBCFG_GLBL_INTR_EN ; 
 int GAHBCFG_NP_TXF_EMP_LVL ; 
 int GAHBCFG_P_TXF_EMP_LVL ; 
 int /*<<< orphan*/  GINTMSK ; 
 int /*<<< orphan*/  GINTSTS ; 
 int GINTSTS_CONIDSTSCHNG ; 
 int GINTSTS_ENUMDONE ; 
 int GINTSTS_ERLYSUSP ; 
 int GINTSTS_GINNAKEFF ; 
 int GINTSTS_GOUTNAKEFF ; 
 int GINTSTS_IEPINT ; 
 int GINTSTS_INCOMPL_SOIN ; 
 int GINTSTS_INCOMPL_SOOUT ; 
 int GINTSTS_LPMTRANRCVD ; 
 int GINTSTS_OEPINT ; 
 int GINTSTS_OTGINT ; 
 int GINTSTS_RESETDET ; 
 int GINTSTS_RXFLVL ; 
 int GINTSTS_SESSREQINT ; 
 int GINTSTS_USBRST ; 
 int GINTSTS_USBSUSP ; 
 int GINTSTS_WKUPINT ; 
 int /*<<< orphan*/  GOTGINT ; 
 int /*<<< orphan*/  GUSBCFG ; 
 int GUSBCFG_HNPCAP ; 
 int GUSBCFG_SRPCAP ; 
 int GUSBCFG_TOUTCAL (int) ; 
 int GUSBCFG_TOUTCAL_MASK ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  dwc2_clear_bit (struct dwc2_hsotg*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ dwc2_core_reset (struct dwc2_hsotg*,int) ; 
 int /*<<< orphan*/  dwc2_gadget_init_lpm (struct dwc2_hsotg*) ; 
 int /*<<< orphan*/  dwc2_gadget_program_ref_clk (struct dwc2_hsotg*) ; 
 int /*<<< orphan*/  dwc2_hsotg_ctrl_epint (struct dwc2_hsotg*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  dwc2_hsotg_en_gsint (struct dwc2_hsotg*,int) ; 
 int /*<<< orphan*/  dwc2_hsotg_enqueue_setup (struct dwc2_hsotg*) ; 
 int dwc2_hsotg_ep0_mps (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc2_hsotg_ep_disable (TYPE_4__*) ; 
 int /*<<< orphan*/  dwc2_hsotg_init_fifo (struct dwc2_hsotg*) ; 
 int /*<<< orphan*/  dwc2_phy_init (struct dwc2_hsotg*,int) ; 
 int dwc2_readl (struct dwc2_hsotg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc2_set_bit (struct dwc2_hsotg*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dwc2_writel (struct dwc2_hsotg*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kill_all_requests (struct dwc2_hsotg*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  udelay (int) ; 
 scalar_t__ using_desc_dma (struct dwc2_hsotg*) ; 
 scalar_t__ using_dma (struct dwc2_hsotg*) ; 

void dwc2_hsotg_core_init_disconnected(struct dwc2_hsotg *hsotg,
				       bool is_usb_reset)
{
	u32 intmsk;
	u32 val;
	u32 usbcfg;
	u32 dcfg = 0;
	int ep;

	/* Kill any ep0 requests as controller will be reinitialized */
	kill_all_requests(hsotg, hsotg->eps_out[0], -ECONNRESET);

	if (!is_usb_reset) {
		if (dwc2_core_reset(hsotg, true))
			return;
	} else {
		/* all endpoints should be shutdown */
		for (ep = 1; ep < hsotg->num_of_eps; ep++) {
			if (hsotg->eps_in[ep])
				dwc2_hsotg_ep_disable(&hsotg->eps_in[ep]->ep);
			if (hsotg->eps_out[ep])
				dwc2_hsotg_ep_disable(&hsotg->eps_out[ep]->ep);
		}
	}

	/*
	 * we must now enable ep0 ready for host detection and then
	 * set configuration.
	 */

	/* keep other bits untouched (so e.g. forced modes are not lost) */
	usbcfg = dwc2_readl(hsotg, GUSBCFG);
	usbcfg &= ~GUSBCFG_TOUTCAL_MASK;
	usbcfg |= GUSBCFG_TOUTCAL(7);

	/* remove the HNP/SRP and set the PHY */
	usbcfg &= ~(GUSBCFG_SRPCAP | GUSBCFG_HNPCAP);
        dwc2_writel(hsotg, usbcfg, GUSBCFG);

	dwc2_phy_init(hsotg, true);

	dwc2_hsotg_init_fifo(hsotg);

	if (!is_usb_reset)
		dwc2_set_bit(hsotg, DCTL, DCTL_SFTDISCON);

	dcfg |= DCFG_EPMISCNT(1);

	switch (hsotg->params.speed) {
	case DWC2_SPEED_PARAM_LOW:
		dcfg |= DCFG_DEVSPD_LS;
		break;
	case DWC2_SPEED_PARAM_FULL:
		if (hsotg->params.phy_type == DWC2_PHY_TYPE_PARAM_FS)
			dcfg |= DCFG_DEVSPD_FS48;
		else
			dcfg |= DCFG_DEVSPD_FS;
		break;
	default:
		dcfg |= DCFG_DEVSPD_HS;
	}

	if (hsotg->params.ipg_isoc_en)
		dcfg |= DCFG_IPG_ISOC_SUPPORDED;

	dwc2_writel(hsotg, dcfg,  DCFG);

	/* Clear any pending OTG interrupts */
	dwc2_writel(hsotg, 0xffffffff, GOTGINT);

	/* Clear any pending interrupts */
	dwc2_writel(hsotg, 0xffffffff, GINTSTS);
	intmsk = GINTSTS_ERLYSUSP | GINTSTS_SESSREQINT |
		GINTSTS_GOUTNAKEFF | GINTSTS_GINNAKEFF |
		GINTSTS_USBRST | GINTSTS_RESETDET |
		GINTSTS_ENUMDONE | GINTSTS_OTGINT |
		GINTSTS_USBSUSP | GINTSTS_WKUPINT |
		GINTSTS_LPMTRANRCVD;

	if (!using_desc_dma(hsotg))
		intmsk |= GINTSTS_INCOMPL_SOIN | GINTSTS_INCOMPL_SOOUT;

	if (!hsotg->params.external_id_pin_ctl)
		intmsk |= GINTSTS_CONIDSTSCHNG;

	dwc2_writel(hsotg, intmsk, GINTMSK);

	if (using_dma(hsotg)) {
		dwc2_writel(hsotg, GAHBCFG_GLBL_INTR_EN | GAHBCFG_DMA_EN |
			    hsotg->params.ahbcfg,
			    GAHBCFG);

		/* Set DDMA mode support in the core if needed */
		if (using_desc_dma(hsotg))
			dwc2_set_bit(hsotg, DCFG, DCFG_DESCDMA_EN);

	} else {
		dwc2_writel(hsotg, ((hsotg->dedicated_fifos) ?
						(GAHBCFG_NP_TXF_EMP_LVL |
						 GAHBCFG_P_TXF_EMP_LVL) : 0) |
			    GAHBCFG_GLBL_INTR_EN, GAHBCFG);
	}

	/*
	 * If INTknTXFEmpMsk is enabled, it's important to disable ep interrupts
	 * when we have no data to transfer. Otherwise we get being flooded by
	 * interrupts.
	 */

	dwc2_writel(hsotg, ((hsotg->dedicated_fifos && !using_dma(hsotg)) ?
		DIEPMSK_TXFIFOEMPTY | DIEPMSK_INTKNTXFEMPMSK : 0) |
		DIEPMSK_EPDISBLDMSK | DIEPMSK_XFERCOMPLMSK |
		DIEPMSK_TIMEOUTMSK | DIEPMSK_AHBERRMSK,
		DIEPMSK);

	/*
	 * don't need XferCompl, we get that from RXFIFO in slave mode. In
	 * DMA mode we may need this and StsPhseRcvd.
	 */
	dwc2_writel(hsotg, (using_dma(hsotg) ? (DIEPMSK_XFERCOMPLMSK |
		DOEPMSK_STSPHSERCVDMSK) : 0) |
		DOEPMSK_EPDISBLDMSK | DOEPMSK_AHBERRMSK |
		DOEPMSK_SETUPMSK,
		DOEPMSK);

	/* Enable BNA interrupt for DDMA */
	if (using_desc_dma(hsotg)) {
		dwc2_set_bit(hsotg, DOEPMSK, DOEPMSK_BNAMSK);
		dwc2_set_bit(hsotg, DIEPMSK, DIEPMSK_BNAININTRMSK);
	}

	/* Enable Service Interval mode if supported */
	if (using_desc_dma(hsotg) && hsotg->params.service_interval)
		dwc2_set_bit(hsotg, DCTL, DCTL_SERVICE_INTERVAL_SUPPORTED);

	dwc2_writel(hsotg, 0, DAINTMSK);

	dev_dbg(hsotg->dev, "EP0: DIEPCTL0=0x%08x, DOEPCTL0=0x%08x\n",
		dwc2_readl(hsotg, DIEPCTL0),
		dwc2_readl(hsotg, DOEPCTL0));

	/* enable in and out endpoint interrupts */
	dwc2_hsotg_en_gsint(hsotg, GINTSTS_OEPINT | GINTSTS_IEPINT);

	/*
	 * Enable the RXFIFO when in slave mode, as this is how we collect
	 * the data. In DMA mode, we get events from the FIFO but also
	 * things we cannot process, so do not use it.
	 */
	if (!using_dma(hsotg))
		dwc2_hsotg_en_gsint(hsotg, GINTSTS_RXFLVL);

	/* Enable interrupts for EP0 in and out */
	dwc2_hsotg_ctrl_epint(hsotg, 0, 0, 1);
	dwc2_hsotg_ctrl_epint(hsotg, 0, 1, 1);

	if (!is_usb_reset) {
		dwc2_set_bit(hsotg, DCTL, DCTL_PWRONPRGDONE);
		udelay(10);  /* see openiboot */
		dwc2_clear_bit(hsotg, DCTL, DCTL_PWRONPRGDONE);
	}

	dev_dbg(hsotg->dev, "DCTL=0x%08x\n", dwc2_readl(hsotg, DCTL));

	/*
	 * DxEPCTL_USBActEp says RO in manual, but seems to be set by
	 * writing to the EPCTL register..
	 */

	/* set to read 1 8byte packet */
	dwc2_writel(hsotg, DXEPTSIZ_MC(1) | DXEPTSIZ_PKTCNT(1) |
	       DXEPTSIZ_XFERSIZE(8), DOEPTSIZ0);

	dwc2_writel(hsotg, dwc2_hsotg_ep0_mps(hsotg->eps_out[0]->ep.maxpacket) |
	       DXEPCTL_CNAK | DXEPCTL_EPENA |
	       DXEPCTL_USBACTEP,
	       DOEPCTL0);

	/* enable, but don't activate EP0in */
	dwc2_writel(hsotg, dwc2_hsotg_ep0_mps(hsotg->eps_out[0]->ep.maxpacket) |
	       DXEPCTL_USBACTEP, DIEPCTL0);

	/* clear global NAKs */
	val = DCTL_CGOUTNAK | DCTL_CGNPINNAK;
	if (!is_usb_reset)
		val |= DCTL_SFTDISCON;
	dwc2_set_bit(hsotg, DCTL, val);

	/* configure the core to support LPM */
	dwc2_gadget_init_lpm(hsotg);

	/* program GREFCLK register if needed */
	if (using_desc_dma(hsotg) && hsotg->params.service_interval)
		dwc2_gadget_program_ref_clk(hsotg);

	/* must be at-least 3ms to allow bus to see disconnect */
	mdelay(3);

	hsotg->lx_state = DWC2_L0;

	dwc2_hsotg_enqueue_setup(hsotg);

	dev_dbg(hsotg->dev, "EP0: DIEPCTL0=0x%08x, DOEPCTL0=0x%08x\n",
		dwc2_readl(hsotg, DIEPCTL0),
		dwc2_readl(hsotg, DOEPCTL0));
}