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
struct ath_hw {scalar_t__ is_clk_25mhz; int /*<<< orphan*/  enabled_cals; } ;

/* Variables and functions */
 int AR_ADHOC_MCAST_KEYID_ENABLE ; 
 int AR_AGG_WEP_ENABLE ; 
 int AR_AGG_WEP_ENABLE_FIX ; 
 int AR_DIAG_RX_ABORT ; 
 int AR_DIAG_RX_DIS ; 
 int /*<<< orphan*/  AR_DIAG_SW ; 
 int AR_GLB_SWREG_DISCONT_EN_BT_WLAN ; 
 int /*<<< orphan*/  AR_GLB_SWREG_DISCONT_MODE ; 
 int /*<<< orphan*/  AR_PCU_MISC_MODE2 ; 
 int AR_PCU_MISC_MODE2_CFP_IGNORE ; 
 int /*<<< orphan*/  AR_PHY_CL_CAL_CTL ; 
 int AR_PHY_CL_CAL_ENABLE ; 
 int /*<<< orphan*/  AR_PHY_TX_IQCAL_CONTROL_0 ; 
 int /*<<< orphan*/  AR_PHY_TX_IQCAL_CONTROL_0_ENABLE_TXIQ_CAL ; 
 int /*<<< orphan*/  AR_RTC_DERIVED_CLK ; 
 int /*<<< orphan*/  AR_SLP32_INC ; 
 int /*<<< orphan*/  AR_SLP32_MODE ; 
 scalar_t__ AR_SREV_9340 (struct ath_hw*) ; 
 scalar_t__ AR_SREV_9462 (struct ath_hw*) ; 
 scalar_t__ AR_SREV_9531 (struct ath_hw*) ; 
 scalar_t__ AR_SREV_9550 (struct ath_hw*) ; 
 scalar_t__ AR_SREV_9561 (struct ath_hw*) ; 
 scalar_t__ AR_SREV_9565 (struct ath_hw*) ; 
 int REG_READ (struct ath_hw*,int /*<<< orphan*/ ) ; 
 scalar_t__ REG_READ_FIELD (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_SET_BIT (struct ath_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_WRITE (struct ath_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TX_CL_CAL ; 
 int /*<<< orphan*/  TX_IQ_CAL ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void ar9003_hw_override_ini(struct ath_hw *ah)
{
	u32 val;

	/*
	 * Set the RX_ABORT and RX_DIS and clear it only after
	 * RXE is set for MAC. This prevents frames with
	 * corrupted descriptor status.
	 */
	REG_SET_BIT(ah, AR_DIAG_SW, (AR_DIAG_RX_DIS | AR_DIAG_RX_ABORT));

	/*
	 * For AR9280 and above, there is a new feature that allows
	 * Multicast search based on both MAC Address and Key ID. By default,
	 * this feature is enabled. But since the driver is not using this
	 * feature, we switch it off; otherwise multicast search based on
	 * MAC addr only will fail.
	 */
	val = REG_READ(ah, AR_PCU_MISC_MODE2) & (~AR_ADHOC_MCAST_KEYID_ENABLE);
	val |= AR_AGG_WEP_ENABLE_FIX |
	       AR_AGG_WEP_ENABLE |
	       AR_PCU_MISC_MODE2_CFP_IGNORE;
	REG_WRITE(ah, AR_PCU_MISC_MODE2, val);

	if (AR_SREV_9462(ah) || AR_SREV_9565(ah)) {
		REG_WRITE(ah, AR_GLB_SWREG_DISCONT_MODE,
			  AR_GLB_SWREG_DISCONT_EN_BT_WLAN);

		if (REG_READ_FIELD(ah, AR_PHY_TX_IQCAL_CONTROL_0,
				   AR_PHY_TX_IQCAL_CONTROL_0_ENABLE_TXIQ_CAL))
			ah->enabled_cals |= TX_IQ_CAL;
		else
			ah->enabled_cals &= ~TX_IQ_CAL;

	}

	if (REG_READ(ah, AR_PHY_CL_CAL_CTL) & AR_PHY_CL_CAL_ENABLE)
		ah->enabled_cals |= TX_CL_CAL;
	else
		ah->enabled_cals &= ~TX_CL_CAL;

	if (AR_SREV_9340(ah) || AR_SREV_9531(ah) || AR_SREV_9550(ah) ||
	    AR_SREV_9561(ah)) {
		if (ah->is_clk_25mhz) {
			REG_WRITE(ah, AR_RTC_DERIVED_CLK, 0x17c << 1);
			REG_WRITE(ah, AR_SLP32_MODE, 0x0010f3d7);
			REG_WRITE(ah, AR_SLP32_INC, 0x0001e7ae);
		} else {
			REG_WRITE(ah, AR_RTC_DERIVED_CLK, 0x261 << 1);
			REG_WRITE(ah, AR_SLP32_MODE, 0x0010f400);
			REG_WRITE(ah, AR_SLP32_INC, 0x0001e800);
		}
		udelay(100);
	}
}