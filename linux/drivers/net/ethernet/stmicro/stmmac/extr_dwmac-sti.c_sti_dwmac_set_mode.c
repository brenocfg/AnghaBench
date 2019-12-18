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
typedef  int /*<<< orphan*/  u32 ;
struct sti_dwmac {int interface; int /*<<< orphan*/  speed; int /*<<< orphan*/  (* fix_retime_src ) (struct sti_dwmac*,int /*<<< orphan*/ ) ;scalar_t__ gmac_en; int /*<<< orphan*/  ctrl_reg; struct regmap* regmap; } ;
struct regmap {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EN ; 
 int /*<<< orphan*/  ENMII ; 
 int /*<<< orphan*/  ENMII_MASK ; 
 int /*<<< orphan*/  EN_MASK ; 
 int /*<<< orphan*/  MII_PHY_SEL_MASK ; 
 int PHY_INTERFACE_MODE_REVMII ; 
 int /*<<< orphan*/ * phy_intf_sels ; 
 int /*<<< orphan*/  regmap_update_bits (struct regmap*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct sti_dwmac*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sti_dwmac_set_mode(struct sti_dwmac *dwmac)
{
	struct regmap *regmap = dwmac->regmap;
	int iface = dwmac->interface;
	u32 reg = dwmac->ctrl_reg;
	u32 val;

	if (dwmac->gmac_en)
		regmap_update_bits(regmap, reg, EN_MASK, EN);

	regmap_update_bits(regmap, reg, MII_PHY_SEL_MASK, phy_intf_sels[iface]);

	val = (iface == PHY_INTERFACE_MODE_REVMII) ? 0 : ENMII;
	regmap_update_bits(regmap, reg, ENMII_MASK, val);

	dwmac->fix_retime_src(dwmac, dwmac->speed);

	return 0;
}