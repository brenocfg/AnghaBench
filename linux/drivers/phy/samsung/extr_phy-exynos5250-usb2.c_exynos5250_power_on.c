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
struct samsung_usb2_phy_instance {TYPE_1__* cfg; struct samsung_usb2_phy_driver* drv; } ;
struct samsung_usb2_phy_driver {int ref_reg_val; scalar_t__ reg_phy; int /*<<< orphan*/  reg_sys; } ;
struct TYPE_2__ {int id; } ;

/* Variables and functions */
#define  EXYNOS5250_DEVICE 131 
#define  EXYNOS5250_HOST 130 
#define  EXYNOS5250_HSIC0 129 
#define  EXYNOS5250_HSIC1 128 
 scalar_t__ EXYNOS_5250_HOSTEHCICTRL ; 
 int EXYNOS_5250_HOSTEHCICTRL_ENAINCR16 ; 
 int EXYNOS_5250_HOSTEHCICTRL_ENAINCR4 ; 
 int EXYNOS_5250_HOSTEHCICTRL_ENAINCR8 ; 
 int EXYNOS_5250_HOSTEHCICTRL_ENAINCRXALIGN ; 
 scalar_t__ EXYNOS_5250_HOSTOHCICTRL ; 
 scalar_t__ EXYNOS_5250_HOSTPHYCTRL0 ; 
 int EXYNOS_5250_HOSTPHYCTRL0_COMMON_ON_N ; 
 int EXYNOS_5250_HOSTPHYCTRL0_FORCESLEEP ; 
 int EXYNOS_5250_HOSTPHYCTRL0_FORCESUSPEND ; 
 int EXYNOS_5250_HOSTPHYCTRL0_FSEL_MASK ; 
 int EXYNOS_5250_HOSTPHYCTRL0_FSEL_SHIFT ; 
 int EXYNOS_5250_HOSTPHYCTRL0_LINKSWRST ; 
 int EXYNOS_5250_HOSTPHYCTRL0_PHYSWRST ; 
 int EXYNOS_5250_HOSTPHYCTRL0_PHYSWRSTALL ; 
 int EXYNOS_5250_HOSTPHYCTRL0_SIDDQ ; 
 int EXYNOS_5250_HOSTPHYCTRL0_UTMISWRST ; 
 scalar_t__ EXYNOS_5250_HSICPHYCTRL1 ; 
 scalar_t__ EXYNOS_5250_HSICPHYCTRL2 ; 
 int EXYNOS_5250_HSICPHYCTRLX_PHYSWRST ; 
 int EXYNOS_5250_HSICPHYCTRLX_REFCLKDIV_12 ; 
 int EXYNOS_5250_HSICPHYCTRLX_REFCLKSEL_DEFAULT ; 
 int /*<<< orphan*/  EXYNOS_5250_MODE_SWITCH_DEVICE ; 
 int /*<<< orphan*/  EXYNOS_5250_MODE_SWITCH_MASK ; 
 int /*<<< orphan*/  EXYNOS_5250_MODE_SWITCH_OFFSET ; 
 int EXYNOS_5250_REFCLKSEL_CLKCORE ; 
 scalar_t__ EXYNOS_5250_USBOTGSYS ; 
 int EXYNOS_5250_USBOTGSYS_FORCE_SLEEP ; 
 int EXYNOS_5250_USBOTGSYS_FORCE_SUSPEND ; 
 int EXYNOS_5250_USBOTGSYS_FSEL_MASK ; 
 int EXYNOS_5250_USBOTGSYS_FSEL_SHIFT ; 
 int EXYNOS_5250_USBOTGSYS_LINK_SW_RST_UOTG ; 
 int EXYNOS_5250_USBOTGSYS_OTGDISABLE ; 
 int EXYNOS_5250_USBOTGSYS_PHYLINK_SW_RESET ; 
 int EXYNOS_5250_USBOTGSYS_PHY_SW_RST ; 
 int EXYNOS_5250_USBOTGSYS_REFCLKSEL_MASK ; 
 int EXYNOS_5250_USBOTGSYS_REFCLKSEL_SHIFT ; 
 int EXYNOS_5250_USBOTGSYS_SIDDQ_UOTG ; 
 int /*<<< orphan*/  exynos5250_isol (struct samsung_usb2_phy_instance*,int /*<<< orphan*/ ) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int exynos5250_power_on(struct samsung_usb2_phy_instance *inst)
{
	struct samsung_usb2_phy_driver *drv = inst->drv;
	u32 ctrl0;
	u32 otg;
	u32 ehci;
	u32 ohci;
	u32 hsic;

	switch (inst->cfg->id) {
	case EXYNOS5250_DEVICE:
		regmap_update_bits(drv->reg_sys,
				   EXYNOS_5250_MODE_SWITCH_OFFSET,
				   EXYNOS_5250_MODE_SWITCH_MASK,
				   EXYNOS_5250_MODE_SWITCH_DEVICE);

		/* OTG configuration */
		otg = readl(drv->reg_phy + EXYNOS_5250_USBOTGSYS);
		/* The clock */
		otg &= ~EXYNOS_5250_USBOTGSYS_FSEL_MASK;
		otg |= drv->ref_reg_val << EXYNOS_5250_USBOTGSYS_FSEL_SHIFT;
		/* Reset */
		otg &= ~(EXYNOS_5250_USBOTGSYS_FORCE_SUSPEND |
			EXYNOS_5250_USBOTGSYS_FORCE_SLEEP |
			EXYNOS_5250_USBOTGSYS_SIDDQ_UOTG);
		otg |=	EXYNOS_5250_USBOTGSYS_PHY_SW_RST |
			EXYNOS_5250_USBOTGSYS_PHYLINK_SW_RESET |
			EXYNOS_5250_USBOTGSYS_LINK_SW_RST_UOTG |
			EXYNOS_5250_USBOTGSYS_OTGDISABLE;
		/* Ref clock */
		otg &=	~EXYNOS_5250_USBOTGSYS_REFCLKSEL_MASK;
		otg |=  EXYNOS_5250_REFCLKSEL_CLKCORE <<
					EXYNOS_5250_USBOTGSYS_REFCLKSEL_SHIFT;
		writel(otg, drv->reg_phy + EXYNOS_5250_USBOTGSYS);
		udelay(100);
		otg &= ~(EXYNOS_5250_USBOTGSYS_PHY_SW_RST |
			EXYNOS_5250_USBOTGSYS_LINK_SW_RST_UOTG |
			EXYNOS_5250_USBOTGSYS_PHYLINK_SW_RESET |
			EXYNOS_5250_USBOTGSYS_OTGDISABLE);
		writel(otg, drv->reg_phy + EXYNOS_5250_USBOTGSYS);


		break;
	case EXYNOS5250_HOST:
	case EXYNOS5250_HSIC0:
	case EXYNOS5250_HSIC1:
		/* Host registers configuration */
		ctrl0 = readl(drv->reg_phy + EXYNOS_5250_HOSTPHYCTRL0);
		/* The clock */
		ctrl0 &= ~EXYNOS_5250_HOSTPHYCTRL0_FSEL_MASK;
		ctrl0 |= drv->ref_reg_val <<
					EXYNOS_5250_HOSTPHYCTRL0_FSEL_SHIFT;

		/* Reset */
		ctrl0 &=	~(EXYNOS_5250_HOSTPHYCTRL0_PHYSWRST |
				EXYNOS_5250_HOSTPHYCTRL0_PHYSWRSTALL |
				EXYNOS_5250_HOSTPHYCTRL0_SIDDQ |
				EXYNOS_5250_HOSTPHYCTRL0_FORCESUSPEND |
				EXYNOS_5250_HOSTPHYCTRL0_FORCESLEEP);
		ctrl0 |=	EXYNOS_5250_HOSTPHYCTRL0_LINKSWRST |
				EXYNOS_5250_HOSTPHYCTRL0_UTMISWRST |
				EXYNOS_5250_HOSTPHYCTRL0_COMMON_ON_N;
		writel(ctrl0, drv->reg_phy + EXYNOS_5250_HOSTPHYCTRL0);
		udelay(10);
		ctrl0 &=	~(EXYNOS_5250_HOSTPHYCTRL0_LINKSWRST |
				EXYNOS_5250_HOSTPHYCTRL0_UTMISWRST);
		writel(ctrl0, drv->reg_phy + EXYNOS_5250_HOSTPHYCTRL0);

		/* OTG configuration */
		otg = readl(drv->reg_phy + EXYNOS_5250_USBOTGSYS);
		/* The clock */
		otg &= ~EXYNOS_5250_USBOTGSYS_FSEL_MASK;
		otg |= drv->ref_reg_val << EXYNOS_5250_USBOTGSYS_FSEL_SHIFT;
		/* Reset */
		otg &= ~(EXYNOS_5250_USBOTGSYS_FORCE_SUSPEND |
			EXYNOS_5250_USBOTGSYS_FORCE_SLEEP |
			EXYNOS_5250_USBOTGSYS_SIDDQ_UOTG);
		otg |=	EXYNOS_5250_USBOTGSYS_PHY_SW_RST |
			EXYNOS_5250_USBOTGSYS_PHYLINK_SW_RESET |
			EXYNOS_5250_USBOTGSYS_LINK_SW_RST_UOTG |
			EXYNOS_5250_USBOTGSYS_OTGDISABLE;
		/* Ref clock */
		otg &=	~EXYNOS_5250_USBOTGSYS_REFCLKSEL_MASK;
		otg |=  EXYNOS_5250_REFCLKSEL_CLKCORE <<
					EXYNOS_5250_USBOTGSYS_REFCLKSEL_SHIFT;
		writel(otg, drv->reg_phy + EXYNOS_5250_USBOTGSYS);
		udelay(10);
		otg &= ~(EXYNOS_5250_USBOTGSYS_PHY_SW_RST |
			EXYNOS_5250_USBOTGSYS_LINK_SW_RST_UOTG |
			EXYNOS_5250_USBOTGSYS_PHYLINK_SW_RESET);

		/* HSIC phy configuration */
		hsic = (EXYNOS_5250_HSICPHYCTRLX_REFCLKDIV_12 |
				EXYNOS_5250_HSICPHYCTRLX_REFCLKSEL_DEFAULT |
				EXYNOS_5250_HSICPHYCTRLX_PHYSWRST);
		writel(hsic, drv->reg_phy + EXYNOS_5250_HSICPHYCTRL1);
		writel(hsic, drv->reg_phy + EXYNOS_5250_HSICPHYCTRL2);
		udelay(10);
		hsic &= ~EXYNOS_5250_HSICPHYCTRLX_PHYSWRST;
		writel(hsic, drv->reg_phy + EXYNOS_5250_HSICPHYCTRL1);
		writel(hsic, drv->reg_phy + EXYNOS_5250_HSICPHYCTRL2);
		/* The following delay is necessary for the reset sequence to be
		 * completed */
		udelay(80);

		/* Enable EHCI DMA burst */
		ehci = readl(drv->reg_phy + EXYNOS_5250_HOSTEHCICTRL);
		ehci |=	EXYNOS_5250_HOSTEHCICTRL_ENAINCRXALIGN |
			EXYNOS_5250_HOSTEHCICTRL_ENAINCR4 |
			EXYNOS_5250_HOSTEHCICTRL_ENAINCR8 |
			EXYNOS_5250_HOSTEHCICTRL_ENAINCR16;
		writel(ehci, drv->reg_phy + EXYNOS_5250_HOSTEHCICTRL);

		/* OHCI settings */
		ohci = readl(drv->reg_phy + EXYNOS_5250_HOSTOHCICTRL);
		/* Following code is based on the old driver */
		ohci |=	0x1 << 3;
		writel(ohci, drv->reg_phy + EXYNOS_5250_HOSTOHCICTRL);

		break;
	}
	exynos5250_isol(inst, 0);

	return 0;
}