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
struct sun4i_usb_phy_data {TYPE_1__* cfg; } ;
struct sun4i_usb_phy {int index; int /*<<< orphan*/  pmu; } ;
struct TYPE_2__ {scalar_t__ type; } ;

/* Variables and functions */
 int SUNXI_AHB_ICHR8_EN ; 
 int SUNXI_AHB_INCR4_BURST_EN ; 
 int SUNXI_AHB_INCRX_ALIGN_EN ; 
 int SUNXI_EHCI_HS_FORCE ; 
 int SUNXI_HSIC ; 
 int SUNXI_HSIC_CONNECT_INT ; 
 int SUNXI_ULPI_BYPASS_EN ; 
 int readl (int /*<<< orphan*/ ) ; 
 scalar_t__ sun8i_a83t_phy ; 
 struct sun4i_usb_phy_data* to_sun4i_usb_phy_data (struct sun4i_usb_phy*) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sun4i_usb_phy_passby(struct sun4i_usb_phy *phy, int enable)
{
	struct sun4i_usb_phy_data *phy_data = to_sun4i_usb_phy_data(phy);
	u32 bits, reg_value;

	if (!phy->pmu)
		return;

	bits = SUNXI_AHB_ICHR8_EN | SUNXI_AHB_INCR4_BURST_EN |
		SUNXI_AHB_INCRX_ALIGN_EN | SUNXI_ULPI_BYPASS_EN;

	/* A83T USB2 is HSIC */
	if (phy_data->cfg->type == sun8i_a83t_phy && phy->index == 2)
		bits |= SUNXI_EHCI_HS_FORCE | SUNXI_HSIC_CONNECT_INT |
			SUNXI_HSIC;

	reg_value = readl(phy->pmu);

	if (enable)
		reg_value |= bits;
	else
		reg_value &= ~bits;

	writel(reg_value, phy->pmu);
}