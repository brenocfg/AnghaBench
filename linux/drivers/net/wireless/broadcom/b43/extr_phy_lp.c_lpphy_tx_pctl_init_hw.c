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
typedef  int u16 ;
struct TYPE_2__ {int rev; } ;
struct b43_wldev {TYPE_1__ phy; } ;

/* Variables and functions */
 int /*<<< orphan*/  B2063_IQ_CALIB_CTL2 ; 
 int /*<<< orphan*/  B43_LPPHY_LP_PHY_CTL ; 
 int /*<<< orphan*/  B43_LPPHY_RF_OVERRIDE_0 ; 
 int /*<<< orphan*/  B43_LPPHY_RF_OVERRIDE_VAL_0 ; 
 int /*<<< orphan*/  B43_LPPHY_TX_PWR_CTL_CMD ; 
 int B43_LPPHY_TX_PWR_CTL_CMD_MODE ; 
 int B43_LPPHY_TX_PWR_CTL_CMD_MODE_OFF ; 
 int B43_LPPHY_TX_PWR_CTL_CMD_MODE_SW ; 
 int /*<<< orphan*/  B43_LPPHY_TX_PWR_CTL_DELTAPWR_LIMIT ; 
 int /*<<< orphan*/  B43_LPPHY_TX_PWR_CTL_IDLETSSI ; 
 int /*<<< orphan*/  B43_LPPHY_TX_PWR_CTL_NNUM ; 
 int /*<<< orphan*/  B43_LPPHY_TX_PWR_CTL_STAT ; 
 int /*<<< orphan*/  B43_LPTAB32 (int,int) ; 
 int /*<<< orphan*/  B43_PHY_OFDM (int) ; 
 int /*<<< orphan*/  TSSI_MUX_POSTPA ; 
 int /*<<< orphan*/  b43_dummy_transmission (struct b43_wldev*,int,int) ; 
 int /*<<< orphan*/  b43_lptab_write (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  b43_phy_mask (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  b43_phy_maskset (struct b43_wldev*,int /*<<< orphan*/ ,int,int) ; 
 int b43_phy_read (struct b43_wldev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_phy_write (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  b43_radio_maskset (struct b43_wldev*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  lpphy_set_tssi_mux (struct b43_wldev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpphy_set_tx_power_by_index (struct b43_wldev*,int) ; 

__attribute__((used)) static void lpphy_tx_pctl_init_hw(struct b43_wldev *dev)
{
	u16 tmp;
	int i;

	//SPEC TODO Call LP PHY Clear TX Power offsets
	for (i = 0; i < 64; i++) {
		if (dev->phy.rev >= 2)
			b43_lptab_write(dev, B43_LPTAB32(7, i + 1), i);
		else
			b43_lptab_write(dev, B43_LPTAB32(10, i + 1), i);
	}

	b43_phy_maskset(dev, B43_LPPHY_TX_PWR_CTL_NNUM, 0xFF00, 0xFF);
	b43_phy_maskset(dev, B43_LPPHY_TX_PWR_CTL_NNUM, 0x8FFF, 0x5000);
	b43_phy_maskset(dev, B43_LPPHY_TX_PWR_CTL_IDLETSSI, 0xFFC0, 0x1F);
	if (dev->phy.rev < 2) {
		b43_phy_mask(dev, B43_LPPHY_LP_PHY_CTL, 0xEFFF);
		b43_phy_maskset(dev, B43_LPPHY_LP_PHY_CTL, 0xDFFF, 0x2000);
	} else {
		b43_phy_mask(dev, B43_PHY_OFDM(0x103), 0xFFFE);
		b43_phy_maskset(dev, B43_PHY_OFDM(0x103), 0xFFFB, 0x4);
		b43_phy_maskset(dev, B43_PHY_OFDM(0x103), 0xFFEF, 0x10);
		b43_radio_maskset(dev, B2063_IQ_CALIB_CTL2, 0xF3, 0x1);
		lpphy_set_tssi_mux(dev, TSSI_MUX_POSTPA);
	}
	b43_phy_maskset(dev, B43_LPPHY_TX_PWR_CTL_IDLETSSI, 0x7FFF, 0x8000);
	b43_phy_mask(dev, B43_LPPHY_TX_PWR_CTL_DELTAPWR_LIMIT, 0xFF);
	b43_phy_write(dev, B43_LPPHY_TX_PWR_CTL_DELTAPWR_LIMIT, 0xA);
	b43_phy_maskset(dev, B43_LPPHY_TX_PWR_CTL_CMD,
			~B43_LPPHY_TX_PWR_CTL_CMD_MODE & 0xFFFF,
			B43_LPPHY_TX_PWR_CTL_CMD_MODE_OFF);
	b43_phy_mask(dev, B43_LPPHY_TX_PWR_CTL_NNUM, 0xF8FF);
	b43_phy_maskset(dev, B43_LPPHY_TX_PWR_CTL_CMD,
			~B43_LPPHY_TX_PWR_CTL_CMD_MODE & 0xFFFF,
			B43_LPPHY_TX_PWR_CTL_CMD_MODE_SW);

	if (dev->phy.rev < 2) {
		b43_phy_maskset(dev, B43_LPPHY_RF_OVERRIDE_0, 0xEFFF, 0x1000);
		b43_phy_mask(dev, B43_LPPHY_RF_OVERRIDE_VAL_0, 0xEFFF);
	} else {
		lpphy_set_tx_power_by_index(dev, 0x7F);
	}

	b43_dummy_transmission(dev, true, true);

	tmp = b43_phy_read(dev, B43_LPPHY_TX_PWR_CTL_STAT);
	if (tmp & 0x8000) {
		b43_phy_maskset(dev, B43_LPPHY_TX_PWR_CTL_IDLETSSI,
				0xFFC0, (tmp & 0xFF) - 32);
	}

	b43_phy_mask(dev, B43_LPPHY_RF_OVERRIDE_0, 0xEFFF);

	// (SPEC?) TODO Set "Target TX frequency" variable to 0
	// SPEC FIXME "Set BB Multiplier to 0xE000" impossible - bb_mult is u8!
}