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
struct tegra_xusb_padctl {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  XUSB_PADCTL_HSIC_PADX_CTL0 (unsigned int) ; 
 int XUSB_PADCTL_HSIC_PAD_CTL0_RPD_DATA0 ; 
 int XUSB_PADCTL_HSIC_PAD_CTL0_RPD_DATA1 ; 
 int XUSB_PADCTL_HSIC_PAD_CTL0_RPD_STROBE ; 
 int XUSB_PADCTL_HSIC_PAD_CTL0_RPU_DATA0 ; 
 int XUSB_PADCTL_HSIC_PAD_CTL0_RPU_DATA1 ; 
 int XUSB_PADCTL_HSIC_PAD_CTL0_RPU_STROBE ; 
 int padctl_readl (struct tegra_xusb_padctl*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  padctl_writel (struct tegra_xusb_padctl*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tegra210_hsic_set_idle(struct tegra_xusb_padctl *padctl,
				  unsigned int index, bool idle)
{
	u32 value;

	value = padctl_readl(padctl, XUSB_PADCTL_HSIC_PADX_CTL0(index));

	value &= ~(XUSB_PADCTL_HSIC_PAD_CTL0_RPU_DATA0 |
		   XUSB_PADCTL_HSIC_PAD_CTL0_RPU_DATA1 |
		   XUSB_PADCTL_HSIC_PAD_CTL0_RPD_STROBE);

	if (idle)
		value |= XUSB_PADCTL_HSIC_PAD_CTL0_RPD_DATA0 |
			 XUSB_PADCTL_HSIC_PAD_CTL0_RPD_DATA1 |
			 XUSB_PADCTL_HSIC_PAD_CTL0_RPU_STROBE;
	else
		value &= ~(XUSB_PADCTL_HSIC_PAD_CTL0_RPD_DATA0 |
			   XUSB_PADCTL_HSIC_PAD_CTL0_RPD_DATA1 |
			   XUSB_PADCTL_HSIC_PAD_CTL0_RPU_STROBE);

	padctl_writel(padctl, value, XUSB_PADCTL_HSIC_PADX_CTL0(index));

	return 0;
}