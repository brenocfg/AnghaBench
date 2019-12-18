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
struct TYPE_2__ {int macVersion; void* phyRev; int /*<<< orphan*/  macRev; } ;
struct ath_hw {int WARegVal; int is_pciexpress; TYPE_1__ hw_version; } ;
struct ath_common {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR_PHY_CHIP_ID ; 
 scalar_t__ AR_SREV_9100 (struct ath_hw*) ; 
 scalar_t__ AR_SREV_9271 (struct ath_hw*) ; 
 scalar_t__ AR_SREV_9300_20_OR_LATER (struct ath_hw*) ; 
 scalar_t__ AR_SREV_9330 (struct ath_hw*) ; 
 scalar_t__ AR_SREV_9340 (struct ath_hw*) ; 
 scalar_t__ AR_SREV_9550 (struct ath_hw*) ; 
 scalar_t__ AR_SREV_9565 (struct ath_hw*) ; 
#define  AR_SREV_VERSION_5416_PCI 144 
#define  AR_SREV_VERSION_5416_PCIE 143 
#define  AR_SREV_VERSION_9100 142 
#define  AR_SREV_VERSION_9160 141 
#define  AR_SREV_VERSION_9271 140 
#define  AR_SREV_VERSION_9280 139 
#define  AR_SREV_VERSION_9285 138 
#define  AR_SREV_VERSION_9287 137 
#define  AR_SREV_VERSION_9300 136 
#define  AR_SREV_VERSION_9330 135 
#define  AR_SREV_VERSION_9340 134 
#define  AR_SREV_VERSION_9462 133 
#define  AR_SREV_VERSION_9485 132 
#define  AR_SREV_VERSION_9531 131 
#define  AR_SREV_VERSION_9550 130 
#define  AR_SREV_VERSION_9561 129 
#define  AR_SREV_VERSION_9565 128 
 int /*<<< orphan*/  AR_WA ; 
 int AR_WA_ASPM_TIMER_BASED_DISABLE ; 
 int AR_WA_BIT22 ; 
 int AR_WA_D3_L1_DISABLE ; 
 int /*<<< orphan*/  ATH9K_PM_AWAKE ; 
 int /*<<< orphan*/  ATH9K_RESET_POWER_ON ; 
 int /*<<< orphan*/  ATH_HW_INITIALIZED ; 
 int EIO ; 
 int EOPNOTSUPP ; 
 void* REG_READ (struct ath_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_WRITE (struct ath_hw*,int /*<<< orphan*/ ,int) ; 
 int ath9k_hw_attach_ops (struct ath_hw*) ; 
 struct ath_common* ath9k_hw_common (struct ath_hw*) ; 
 int /*<<< orphan*/  ath9k_hw_disablepcie (struct ath_hw*) ; 
 int ath9k_hw_fill_cap_info (struct ath_hw*) ; 
 int /*<<< orphan*/  ath9k_hw_init_cal_settings (struct ath_hw*) ; 
 int /*<<< orphan*/  ath9k_hw_init_config (struct ath_hw*) ; 
 int /*<<< orphan*/  ath9k_hw_init_defaults (struct ath_hw*) ; 
 int /*<<< orphan*/  ath9k_hw_init_hang_checks (struct ath_hw*) ; 
 int /*<<< orphan*/  ath9k_hw_init_macaddr (struct ath_hw*) ; 
 int /*<<< orphan*/  ath9k_hw_init_mode_gain_regs (struct ath_hw*) ; 
 int ath9k_hw_post_init (struct ath_hw*) ; 
 int /*<<< orphan*/  ath9k_hw_read_revisions (struct ath_hw*) ; 
 int /*<<< orphan*/  ath9k_hw_set_reset_reg (struct ath_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath9k_hw_setpower (struct ath_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath_err (struct ath_common*,char*,...) ; 

__attribute__((used)) static int __ath9k_hw_init(struct ath_hw *ah)
{
	struct ath_common *common = ath9k_hw_common(ah);
	int r = 0;

	if (!ath9k_hw_read_revisions(ah)) {
		ath_err(common, "Could not read hardware revisions");
		return -EOPNOTSUPP;
	}

	switch (ah->hw_version.macVersion) {
	case AR_SREV_VERSION_5416_PCI:
	case AR_SREV_VERSION_5416_PCIE:
	case AR_SREV_VERSION_9160:
	case AR_SREV_VERSION_9100:
	case AR_SREV_VERSION_9280:
	case AR_SREV_VERSION_9285:
	case AR_SREV_VERSION_9287:
	case AR_SREV_VERSION_9271:
	case AR_SREV_VERSION_9300:
	case AR_SREV_VERSION_9330:
	case AR_SREV_VERSION_9485:
	case AR_SREV_VERSION_9340:
	case AR_SREV_VERSION_9462:
	case AR_SREV_VERSION_9550:
	case AR_SREV_VERSION_9565:
	case AR_SREV_VERSION_9531:
	case AR_SREV_VERSION_9561:
		break;
	default:
		ath_err(common,
			"Mac Chip Rev 0x%02x.%x is not supported by this driver\n",
			ah->hw_version.macVersion, ah->hw_version.macRev);
		return -EOPNOTSUPP;
	}

	/*
	 * Read back AR_WA into a permanent copy and set bits 14 and 17.
	 * We need to do this to avoid RMW of this register. We cannot
	 * read the reg when chip is asleep.
	 */
	if (AR_SREV_9300_20_OR_LATER(ah)) {
		ah->WARegVal = REG_READ(ah, AR_WA);
		ah->WARegVal |= (AR_WA_D3_L1_DISABLE |
				 AR_WA_ASPM_TIMER_BASED_DISABLE);
	}

	if (!ath9k_hw_set_reset_reg(ah, ATH9K_RESET_POWER_ON)) {
		ath_err(common, "Couldn't reset chip\n");
		return -EIO;
	}

	if (AR_SREV_9565(ah)) {
		ah->WARegVal |= AR_WA_BIT22;
		REG_WRITE(ah, AR_WA, ah->WARegVal);
	}

	ath9k_hw_init_defaults(ah);
	ath9k_hw_init_config(ah);

	r = ath9k_hw_attach_ops(ah);
	if (r)
		return r;

	if (!ath9k_hw_setpower(ah, ATH9K_PM_AWAKE)) {
		ath_err(common, "Couldn't wakeup chip\n");
		return -EIO;
	}

	if (AR_SREV_9271(ah) || AR_SREV_9100(ah) || AR_SREV_9340(ah) ||
	    AR_SREV_9330(ah) || AR_SREV_9550(ah))
		ah->is_pciexpress = false;

	ah->hw_version.phyRev = REG_READ(ah, AR_PHY_CHIP_ID);
	ath9k_hw_init_cal_settings(ah);

	if (!ah->is_pciexpress)
		ath9k_hw_disablepcie(ah);

	r = ath9k_hw_post_init(ah);
	if (r)
		return r;

	ath9k_hw_init_mode_gain_regs(ah);
	r = ath9k_hw_fill_cap_info(ah);
	if (r)
		return r;

	ath9k_hw_init_macaddr(ah);
	ath9k_hw_init_hang_checks(ah);

	common->state = ATH_HW_INITIALIZED;

	return 0;
}