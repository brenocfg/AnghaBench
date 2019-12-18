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
struct skge_port {int port; int /*<<< orphan*/  speed; struct skge_hw* hw; } ;
struct skge_hw {int /*<<< orphan*/  phy_lock; int /*<<< orphan*/  phy_type; } ;
typedef  enum led_mode { ____Placeholder_led_mode } led_mode ;

/* Variables and functions */
 int /*<<< orphan*/  BLINK_84MS ; 
#define  LED_MODE_OFF 130 
#define  LED_MODE_ON 129 
#define  LED_MODE_TST 128 
 int /*<<< orphan*/  LED_START ; 
 int /*<<< orphan*/  LED_T_OFF ; 
 int /*<<< orphan*/  LED_T_ON ; 
 int /*<<< orphan*/  LINKLED_LINKSYNC_ON ; 
 int /*<<< orphan*/  LINKLED_OFF ; 
 int /*<<< orphan*/  LINKLED_ON ; 
 int /*<<< orphan*/  LNK_LED_REG ; 
 int /*<<< orphan*/  MO_LED_OFF ; 
 int /*<<< orphan*/  MO_LED_ON ; 
 int /*<<< orphan*/  PHY_BCOM_P_EXT_CTRL ; 
 int /*<<< orphan*/  PHY_B_PEC_LED_OFF ; 
 int /*<<< orphan*/  PHY_B_PEC_LED_ON ; 
 int /*<<< orphan*/  PHY_MARV_LED_CTRL ; 
 int /*<<< orphan*/  PHY_MARV_LED_OVER ; 
 int PHY_M_LEDC_DP_CTRL ; 
 int PHY_M_LEDC_TX_CTRL ; 
 int PHY_M_LED_BLINK_RT (int /*<<< orphan*/ ) ; 
 int PHY_M_LED_MO_10 (int /*<<< orphan*/ ) ; 
 int PHY_M_LED_MO_100 (int /*<<< orphan*/ ) ; 
 int PHY_M_LED_MO_1000 (int /*<<< orphan*/ ) ; 
 int PHY_M_LED_MO_DUP (int /*<<< orphan*/ ) ; 
 int PHY_M_LED_MO_RX (int /*<<< orphan*/ ) ; 
 int PHY_M_LED_PULS_DUR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PULS_170MS ; 
 int /*<<< orphan*/  RX_LED_CTRL ; 
 int /*<<< orphan*/  RX_LED_TST ; 
 int /*<<< orphan*/  RX_LED_VAL ; 
 int /*<<< orphan*/  SK_PHY_BCOM ; 
 int /*<<< orphan*/  SK_REG (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPEED_100 ; 
 int /*<<< orphan*/  TX_LED_CTRL ; 
 int /*<<< orphan*/  TX_LED_TST ; 
 int /*<<< orphan*/  TX_LED_VAL ; 
 int /*<<< orphan*/  gm_phy_write (struct skge_hw*,int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ is_genesis (struct skge_hw*) ; 
 int /*<<< orphan*/  skge_write32 (struct skge_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  skge_write8 (struct skge_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xm_phy_write (struct skge_hw*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void skge_led(struct skge_port *skge, enum led_mode mode)
{
	struct skge_hw *hw = skge->hw;
	int port = skge->port;

	spin_lock_bh(&hw->phy_lock);
	if (is_genesis(hw)) {
		switch (mode) {
		case LED_MODE_OFF:
			if (hw->phy_type == SK_PHY_BCOM)
				xm_phy_write(hw, port, PHY_BCOM_P_EXT_CTRL, PHY_B_PEC_LED_OFF);
			else {
				skge_write32(hw, SK_REG(port, TX_LED_VAL), 0);
				skge_write8(hw, SK_REG(port, TX_LED_CTRL), LED_T_OFF);
			}
			skge_write8(hw, SK_REG(port, LNK_LED_REG), LINKLED_OFF);
			skge_write32(hw, SK_REG(port, RX_LED_VAL), 0);
			skge_write8(hw, SK_REG(port, RX_LED_CTRL), LED_T_OFF);
			break;

		case LED_MODE_ON:
			skge_write8(hw, SK_REG(port, LNK_LED_REG), LINKLED_ON);
			skge_write8(hw, SK_REG(port, LNK_LED_REG), LINKLED_LINKSYNC_ON);

			skge_write8(hw, SK_REG(port, RX_LED_CTRL), LED_START);
			skge_write8(hw, SK_REG(port, TX_LED_CTRL), LED_START);

			break;

		case LED_MODE_TST:
			skge_write8(hw, SK_REG(port, RX_LED_TST), LED_T_ON);
			skge_write32(hw, SK_REG(port, RX_LED_VAL), 100);
			skge_write8(hw, SK_REG(port, RX_LED_CTRL), LED_START);

			if (hw->phy_type == SK_PHY_BCOM)
				xm_phy_write(hw, port, PHY_BCOM_P_EXT_CTRL, PHY_B_PEC_LED_ON);
			else {
				skge_write8(hw, SK_REG(port, TX_LED_TST), LED_T_ON);
				skge_write32(hw, SK_REG(port, TX_LED_VAL), 100);
				skge_write8(hw, SK_REG(port, TX_LED_CTRL), LED_START);
			}

		}
	} else {
		switch (mode) {
		case LED_MODE_OFF:
			gm_phy_write(hw, port, PHY_MARV_LED_CTRL, 0);
			gm_phy_write(hw, port, PHY_MARV_LED_OVER,
				     PHY_M_LED_MO_DUP(MO_LED_OFF)  |
				     PHY_M_LED_MO_10(MO_LED_OFF)   |
				     PHY_M_LED_MO_100(MO_LED_OFF)  |
				     PHY_M_LED_MO_1000(MO_LED_OFF) |
				     PHY_M_LED_MO_RX(MO_LED_OFF));
			break;
		case LED_MODE_ON:
			gm_phy_write(hw, port, PHY_MARV_LED_CTRL,
				     PHY_M_LED_PULS_DUR(PULS_170MS) |
				     PHY_M_LED_BLINK_RT(BLINK_84MS) |
				     PHY_M_LEDC_TX_CTRL |
				     PHY_M_LEDC_DP_CTRL);

			gm_phy_write(hw, port, PHY_MARV_LED_OVER,
				     PHY_M_LED_MO_RX(MO_LED_OFF) |
				     (skge->speed == SPEED_100 ?
				      PHY_M_LED_MO_100(MO_LED_ON) : 0));
			break;
		case LED_MODE_TST:
			gm_phy_write(hw, port, PHY_MARV_LED_CTRL, 0);
			gm_phy_write(hw, port, PHY_MARV_LED_OVER,
				     PHY_M_LED_MO_DUP(MO_LED_ON)  |
				     PHY_M_LED_MO_10(MO_LED_ON)   |
				     PHY_M_LED_MO_100(MO_LED_ON)  |
				     PHY_M_LED_MO_1000(MO_LED_ON) |
				     PHY_M_LED_MO_RX(MO_LED_ON));
		}
	}
	spin_unlock_bh(&hw->phy_lock);
}