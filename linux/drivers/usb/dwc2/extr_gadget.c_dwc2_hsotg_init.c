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
struct dwc2_hsotg {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DAINTMSK ; 
 int /*<<< orphan*/  DCTL ; 
 int /*<<< orphan*/  DCTL_SFTDISCON ; 
 int /*<<< orphan*/  DIEPMSK ; 
 int DIEPMSK_AHBERRMSK ; 
 int DIEPMSK_EPDISBLDMSK ; 
 int DIEPMSK_TIMEOUTMSK ; 
 int DIEPMSK_XFERCOMPLMSK ; 
 int /*<<< orphan*/  DOEPMSK ; 
 int DOEPMSK_AHBERRMSK ; 
 int DOEPMSK_EPDISBLDMSK ; 
 int DOEPMSK_SETUPMSK ; 
 int DOEPMSK_XFERCOMPLMSK ; 
 int /*<<< orphan*/  GAHBCFG ; 
 int /*<<< orphan*/  GAHBCFG_DMA_EN ; 
 int /*<<< orphan*/  GNPTXFSIZ ; 
 int /*<<< orphan*/  GRXFSIZ ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc2_hsotg_init_fifo (struct dwc2_hsotg*) ; 
 int /*<<< orphan*/  dwc2_readl (struct dwc2_hsotg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc2_set_bit (struct dwc2_hsotg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc2_writel (struct dwc2_hsotg*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ using_dma (struct dwc2_hsotg*) ; 

__attribute__((used)) static void dwc2_hsotg_init(struct dwc2_hsotg *hsotg)
{
	/* unmask subset of endpoint interrupts */

	dwc2_writel(hsotg, DIEPMSK_TIMEOUTMSK | DIEPMSK_AHBERRMSK |
		    DIEPMSK_EPDISBLDMSK | DIEPMSK_XFERCOMPLMSK,
		    DIEPMSK);

	dwc2_writel(hsotg, DOEPMSK_SETUPMSK | DOEPMSK_AHBERRMSK |
		    DOEPMSK_EPDISBLDMSK | DOEPMSK_XFERCOMPLMSK,
		    DOEPMSK);

	dwc2_writel(hsotg, 0, DAINTMSK);

	/* Be in disconnected state until gadget is registered */
	dwc2_set_bit(hsotg, DCTL, DCTL_SFTDISCON);

	/* setup fifos */

	dev_dbg(hsotg->dev, "GRXFSIZ=0x%08x, GNPTXFSIZ=0x%08x\n",
		dwc2_readl(hsotg, GRXFSIZ),
		dwc2_readl(hsotg, GNPTXFSIZ));

	dwc2_hsotg_init_fifo(hsotg);

	if (using_dma(hsotg))
		dwc2_set_bit(hsotg, GAHBCFG, GAHBCFG_DMA_EN);
}