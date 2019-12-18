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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct musb {int /*<<< orphan*/  xceiv; int /*<<< orphan*/  controller; int /*<<< orphan*/  mregs; int /*<<< orphan*/  dev_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  DM355_DEEPSLEEP ; 
 int /*<<< orphan*/  DRVVBUS_FORCE ; 
 int /*<<< orphan*/  DRVVBUS_OVERRIDE ; 
 int /*<<< orphan*/  MUSB_DEVCTL ; 
 int MUSB_DEVCTL_VBUS ; 
 int MUSB_DEVCTL_VBUS_SHIFT ; 
 int /*<<< orphan*/  __raw_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ cpu_is_davinci_dm355 () ; 
 int /*<<< orphan*/  davinci_musb_source_power (struct musb*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int musb_readb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_off () ; 
 int /*<<< orphan*/  usb_put_phy (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int davinci_musb_exit(struct musb *musb)
{
	int	maxdelay = 30;
	u8	devctl, warn = 0;

	del_timer_sync(&musb->dev_timer);

	/* force VBUS off */
	if (cpu_is_davinci_dm355()) {
		u32	deepsleep = __raw_readl(DM355_DEEPSLEEP);

		deepsleep &= ~DRVVBUS_FORCE;
		deepsleep |= DRVVBUS_OVERRIDE;
		__raw_writel(deepsleep, DM355_DEEPSLEEP);
	}

	davinci_musb_source_power(musb, 0 /*off*/, 1);

	/*
	 * delay, to avoid problems with module reload.
	 * if there's no peripheral connected, this can take a
	 * long time to fall, especially on EVM with huge C133.
	 */
	do {
		devctl = musb_readb(musb->mregs, MUSB_DEVCTL);
		if (!(devctl & MUSB_DEVCTL_VBUS))
			break;
		if ((devctl & MUSB_DEVCTL_VBUS) != warn) {
			warn = devctl & MUSB_DEVCTL_VBUS;
			dev_dbg(musb->controller, "VBUS %d\n",
				warn >> MUSB_DEVCTL_VBUS_SHIFT);
		}
		msleep(1000);
		maxdelay--;
	} while (maxdelay > 0);

	/* in OTG mode, another host might be connected */
	if (devctl & MUSB_DEVCTL_VBUS)
		dev_dbg(musb->controller, "VBUS off timeout (devctl %02x)\n", devctl);

	phy_off();

	usb_put_phy(musb->xceiv);

	return 0;
}