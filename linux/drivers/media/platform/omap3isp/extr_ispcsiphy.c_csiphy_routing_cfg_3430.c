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
typedef  scalar_t__ u32 ;
struct isp_csiphy {TYPE_1__* isp; } ;
struct TYPE_2__ {int /*<<< orphan*/  syscon_offset; int /*<<< orphan*/  syscon; } ;

/* Variables and functions */
 scalar_t__ ISP_INTERFACE_CCP2B_PHY1 ; 
 scalar_t__ OMAP343X_CONTROL_CSIRXFE_PWRDNZ ; 
 scalar_t__ OMAP343X_CONTROL_CSIRXFE_RESET ; 
 scalar_t__ OMAP343X_CONTROL_CSIRXFE_SELFORM ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void csiphy_routing_cfg_3430(struct isp_csiphy *phy, u32 iface, bool on,
				    bool ccp2_strobe)
{
	u32 csirxfe = OMAP343X_CONTROL_CSIRXFE_PWRDNZ
		| OMAP343X_CONTROL_CSIRXFE_RESET;

	/* Only the CCP2B on PHY1 is configurable. */
	if (iface != ISP_INTERFACE_CCP2B_PHY1)
		return;

	if (!on) {
		regmap_write(phy->isp->syscon, phy->isp->syscon_offset, 0);
		return;
	}

	if (ccp2_strobe)
		csirxfe |= OMAP343X_CONTROL_CSIRXFE_SELFORM;

	regmap_write(phy->isp->syscon, phy->isp->syscon_offset, csirxfe);
}