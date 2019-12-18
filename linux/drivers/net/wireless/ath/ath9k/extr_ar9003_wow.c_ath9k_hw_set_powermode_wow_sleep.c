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
struct ath_hw {int dummy; } ;
struct ath_common {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AH_WAIT_TIMEOUT ; 
 int /*<<< orphan*/  AR_CR ; 
 int AR_CR_RXD ; 
 int /*<<< orphan*/  AR_CR_RXE ; 
 int /*<<< orphan*/  AR_DC_TSF2_ENABLE ; 
 int /*<<< orphan*/  AR_DIAG_SW ; 
 int /*<<< orphan*/  AR_DIRECT_CONNECT ; 
 int AR_GEN_TIMERS2_MODE_ENABLE_MASK ; 
 int /*<<< orphan*/  AR_MAC_PCU_GEN_TIMER_TSF_SEL ; 
 int /*<<< orphan*/  AR_NDP2_TIMER_MODE ; 
 int /*<<< orphan*/  AR_RTC_FORCE_WAKE ; 
 int AR_RTC_FORCE_WAKE_ON_INT ; 
 int /*<<< orphan*/  AR_RTC_KEEP_AWAKE ; 
 scalar_t__ AR_SREV_9462 (struct ath_hw*) ; 
 scalar_t__ AR_SREV_9485 (struct ath_hw*) ; 
 scalar_t__ AR_SREV_9565 (struct ath_hw*) ; 
 int /*<<< orphan*/  REG_CLR_BIT (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int REG_READ (struct ath_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_WRITE (struct ath_hw*,int /*<<< orphan*/ ,int) ; 
 struct ath_common* ath9k_hw_common (struct ath_hw*) ; 
 scalar_t__ ath9k_hw_mci_is_enabled (struct ath_hw*) ; 
 int /*<<< orphan*/  ath9k_hw_set_sta_powersave (struct ath_hw*) ; 
 int /*<<< orphan*/  ath9k_hw_wait (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath_err (struct ath_common*,char*,int,int) ; 

__attribute__((used)) static void ath9k_hw_set_powermode_wow_sleep(struct ath_hw *ah)
{
	struct ath_common *common = ath9k_hw_common(ah);

	ath9k_hw_set_sta_powersave(ah);

	/* set rx disable bit */
	REG_WRITE(ah, AR_CR, AR_CR_RXD);

	if (!ath9k_hw_wait(ah, AR_CR, AR_CR_RXE, 0, AH_WAIT_TIMEOUT)) {
		ath_err(common, "Failed to stop Rx DMA in 10ms AR_CR=0x%08x AR_DIAG_SW=0x%08x\n",
			REG_READ(ah, AR_CR), REG_READ(ah, AR_DIAG_SW));
		return;
	}

	if (AR_SREV_9462(ah) || AR_SREV_9565(ah)) {
		if (!REG_READ(ah, AR_MAC_PCU_GEN_TIMER_TSF_SEL))
			REG_CLR_BIT(ah, AR_DIRECT_CONNECT, AR_DC_TSF2_ENABLE);
	} else if (AR_SREV_9485(ah)){
		if (!(REG_READ(ah, AR_NDP2_TIMER_MODE) &
		      AR_GEN_TIMERS2_MODE_ENABLE_MASK))
			REG_CLR_BIT(ah, AR_DIRECT_CONNECT, AR_DC_TSF2_ENABLE);
	}

	if (ath9k_hw_mci_is_enabled(ah))
		REG_WRITE(ah, AR_RTC_KEEP_AWAKE, 0x2);

	REG_WRITE(ah, AR_RTC_FORCE_WAKE, AR_RTC_FORCE_WAKE_ON_INT);
}