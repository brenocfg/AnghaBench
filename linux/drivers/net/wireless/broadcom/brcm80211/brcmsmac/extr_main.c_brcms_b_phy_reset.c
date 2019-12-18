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
struct brcms_phy_pub {int dummy; } ;
struct brcms_hardware {TYPE_1__* band; int /*<<< orphan*/  unit; int /*<<< orphan*/  d11core; } ;
struct TYPE_2__ {int /*<<< orphan*/  phyrev; struct brcms_phy_pub* pi; } ;

/* Variables and functions */
 scalar_t__ BRCMS_ISNPHY (TYPE_1__*) ; 
 scalar_t__ NREV_GE (int /*<<< orphan*/ ,int) ; 
 scalar_t__ NREV_LE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ON ; 
 int SICF_BWMASK ; 
 int SICF_PCLKE ; 
 int SICF_PRST ; 
 int /*<<< orphan*/  brcms_b_core_ioctl (struct brcms_hardware*,int,int) ; 
 int /*<<< orphan*/  brcms_b_core_phy_clk (struct brcms_hardware*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcms_b_core_phypll_reset (struct brcms_hardware*) ; 
 int /*<<< orphan*/  brcms_dbg_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  wlc_phy_anacore (struct brcms_phy_pub*,int /*<<< orphan*/ ) ; 
 int wlc_phy_clk_bwbits (struct brcms_phy_pub*) ; 

void brcms_b_phy_reset(struct brcms_hardware *wlc_hw)
{
	struct brcms_phy_pub *pih = wlc_hw->band->pi;
	u32 phy_bw_clkbits;
	bool phy_in_reset = false;

	brcms_dbg_info(wlc_hw->d11core, "wl%d: reset phy\n", wlc_hw->unit);

	if (pih == NULL)
		return;

	phy_bw_clkbits = wlc_phy_clk_bwbits(wlc_hw->band->pi);

	/* Specific reset sequence required for NPHY rev 3 and 4 */
	if (BRCMS_ISNPHY(wlc_hw->band) && NREV_GE(wlc_hw->band->phyrev, 3) &&
	    NREV_LE(wlc_hw->band->phyrev, 4)) {
		/* Set the PHY bandwidth */
		brcms_b_core_ioctl(wlc_hw, SICF_BWMASK, phy_bw_clkbits);

		udelay(1);

		/* Perform a soft reset of the PHY PLL */
		brcms_b_core_phypll_reset(wlc_hw);

		/* reset the PHY */
		brcms_b_core_ioctl(wlc_hw, (SICF_PRST | SICF_PCLKE),
				   (SICF_PRST | SICF_PCLKE));
		phy_in_reset = true;
	} else {
		brcms_b_core_ioctl(wlc_hw,
				   (SICF_PRST | SICF_PCLKE | SICF_BWMASK),
				   (SICF_PRST | SICF_PCLKE | phy_bw_clkbits));
	}

	udelay(2);
	brcms_b_core_phy_clk(wlc_hw, ON);

	if (pih)
		wlc_phy_anacore(pih, ON);
}