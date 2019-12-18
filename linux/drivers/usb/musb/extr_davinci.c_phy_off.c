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

/* Variables and functions */
 int USBPHY_OSCPDWN ; 
 int USBPHY_OTGPDWN ; 
 int USBPHY_PHYPDWN ; 
 int USBPHY_PHYPLLON ; 
 int USBPHY_SESNDEN ; 
 int USBPHY_VBDTCTEN ; 
 int /*<<< orphan*/  USB_PHY_CTRL ; 
 int __raw_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void phy_off(void)
{
	u32	phy_ctrl = __raw_readl(USB_PHY_CTRL);

	/* powerdown the on-chip PHY, its PLL, and the OTG block */
	phy_ctrl &= ~(USBPHY_SESNDEN | USBPHY_VBDTCTEN | USBPHY_PHYPLLON);
	phy_ctrl |= USBPHY_OSCPDWN | USBPHY_OTGPDWN | USBPHY_PHYPDWN;
	__raw_writel(phy_ctrl, USB_PHY_CTRL);
}