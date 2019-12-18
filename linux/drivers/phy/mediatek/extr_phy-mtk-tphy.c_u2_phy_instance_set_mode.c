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
struct u2phy_banks {scalar_t__ com; } ;
struct mtk_tphy {int dummy; } ;
struct mtk_phy_instance {struct u2phy_banks u2_banks; } ;
typedef  enum phy_mode { ____Placeholder_phy_mode } phy_mode ;

/* Variables and functions */
 int P2C_FORCE_IDDIG ; 
 int P2C_RG_IDDIG ; 
#define  PHY_MODE_USB_DEVICE 130 
#define  PHY_MODE_USB_HOST 129 
#define  PHY_MODE_USB_OTG 128 
 scalar_t__ U3P_U2PHYDTM1 ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void u2_phy_instance_set_mode(struct mtk_tphy *tphy,
				     struct mtk_phy_instance *instance,
				     enum phy_mode mode)
{
	struct u2phy_banks *u2_banks = &instance->u2_banks;
	u32 tmp;

	tmp = readl(u2_banks->com + U3P_U2PHYDTM1);
	switch (mode) {
	case PHY_MODE_USB_DEVICE:
		tmp |= P2C_FORCE_IDDIG | P2C_RG_IDDIG;
		break;
	case PHY_MODE_USB_HOST:
		tmp |= P2C_FORCE_IDDIG;
		tmp &= ~P2C_RG_IDDIG;
		break;
	case PHY_MODE_USB_OTG:
		tmp &= ~(P2C_FORCE_IDDIG | P2C_RG_IDDIG);
		break;
	default:
		return;
	}
	writel(tmp, u2_banks->com + U3P_U2PHYDTM1);
}