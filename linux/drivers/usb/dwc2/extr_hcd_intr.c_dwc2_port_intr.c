#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_5__ {int port_enable_change; int port_over_current_change; } ;
struct TYPE_6__ {TYPE_2__ b; } ;
struct TYPE_4__ {int dma_desc_enable; scalar_t__ dma_desc_fs_enable; } ;
struct dwc2_hsotg {int new_connection; TYPE_3__ flags; int /*<<< orphan*/  dev; TYPE_1__ params; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCFG ; 
 int HCFG_DESCDMA ; 
 int /*<<< orphan*/  HPRT0 ; 
 int HPRT0_CONNDET ; 
 int HPRT0_ENA ; 
 int HPRT0_ENACHG ; 
 int HPRT0_OVRCURRCHG ; 
 int /*<<< orphan*/  dev_vdbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dwc2_hcd_connect (struct dwc2_hsotg*) ; 
 int /*<<< orphan*/  dwc2_hprt0_enable (struct dwc2_hsotg*,int,int*) ; 
 int dwc2_readl (struct dwc2_hsotg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc2_writel (struct dwc2_hsotg*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dwc2_port_intr(struct dwc2_hsotg *hsotg)
{
	u32 hprt0;
	u32 hprt0_modify;

	dev_vdbg(hsotg->dev, "--Port Interrupt--\n");

	hprt0 = dwc2_readl(hsotg, HPRT0);
	hprt0_modify = hprt0;

	/*
	 * Clear appropriate bits in HPRT0 to clear the interrupt bit in
	 * GINTSTS
	 */
	hprt0_modify &= ~(HPRT0_ENA | HPRT0_CONNDET | HPRT0_ENACHG |
			  HPRT0_OVRCURRCHG);

	/*
	 * Port Connect Detected
	 * Set flag and clear if detected
	 */
	if (hprt0 & HPRT0_CONNDET) {
		dwc2_writel(hsotg, hprt0_modify | HPRT0_CONNDET, HPRT0);

		dev_vdbg(hsotg->dev,
			 "--Port Interrupt HPRT0=0x%08x Port Connect Detected--\n",
			 hprt0);
		dwc2_hcd_connect(hsotg);

		/*
		 * The Hub driver asserts a reset when it sees port connect
		 * status change flag
		 */
	}

	/*
	 * Port Enable Changed
	 * Clear if detected - Set internal flag if disabled
	 */
	if (hprt0 & HPRT0_ENACHG) {
		dwc2_writel(hsotg, hprt0_modify | HPRT0_ENACHG, HPRT0);
		dev_vdbg(hsotg->dev,
			 "  --Port Interrupt HPRT0=0x%08x Port Enable Changed (now %d)--\n",
			 hprt0, !!(hprt0 & HPRT0_ENA));
		if (hprt0 & HPRT0_ENA) {
			hsotg->new_connection = true;
			dwc2_hprt0_enable(hsotg, hprt0, &hprt0_modify);
		} else {
			hsotg->flags.b.port_enable_change = 1;
			if (hsotg->params.dma_desc_fs_enable) {
				u32 hcfg;

				hsotg->params.dma_desc_enable = false;
				hsotg->new_connection = false;
				hcfg = dwc2_readl(hsotg, HCFG);
				hcfg &= ~HCFG_DESCDMA;
				dwc2_writel(hsotg, hcfg, HCFG);
			}
		}
	}

	/* Overcurrent Change Interrupt */
	if (hprt0 & HPRT0_OVRCURRCHG) {
		dwc2_writel(hsotg, hprt0_modify | HPRT0_OVRCURRCHG,
			    HPRT0);
		dev_vdbg(hsotg->dev,
			 "  --Port Interrupt HPRT0=0x%08x Port Overcurrent Changed--\n",
			 hprt0);
		hsotg->flags.b.port_over_current_change = 1;
	}
}