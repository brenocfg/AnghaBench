#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_5__ {int featureEnable; } ;
struct ar9300_eeprom {TYPE_2__ baseEepHeader; } ;
struct TYPE_4__ {struct ar9300_eeprom ar9300_eep; } ;
struct ath_hw {TYPE_1__ eeprom; } ;
struct TYPE_6__ {int /*<<< orphan*/  txFrameToXpaOn; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR_PHY_XPA_TIMING_CTL ; 
 int /*<<< orphan*/  AR_PHY_XPA_TIMING_CTL_FRAME_XPAA_ON ; 
 int /*<<< orphan*/  AR_PHY_XPA_TIMING_CTL_FRAME_XPAB_ON ; 
 int /*<<< orphan*/  AR_SREV_9300 (struct ath_hw*) ; 
 int /*<<< orphan*/  AR_SREV_9340 (struct ath_hw*) ; 
 int /*<<< orphan*/  AR_SREV_9531 (struct ath_hw*) ; 
 int /*<<< orphan*/  AR_SREV_9561 (struct ath_hw*) ; 
 int /*<<< orphan*/  AR_SREV_9580 (struct ath_hw*) ; 
 int /*<<< orphan*/  REG_RMW_FIELD (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* ar9003_modal_header (struct ath_hw*,int) ; 

__attribute__((used)) static void ar9003_hw_xpa_timing_control_apply(struct ath_hw *ah, bool is2ghz)
{
	struct ar9300_eeprom *eep = &ah->eeprom.ar9300_eep;
	u8 xpa_ctl;

	if (!(eep->baseEepHeader.featureEnable & 0x80))
		return;

	if (!AR_SREV_9300(ah) &&
	    !AR_SREV_9340(ah) &&
	    !AR_SREV_9580(ah) &&
	    !AR_SREV_9531(ah) &&
	    !AR_SREV_9561(ah))
		return;

	xpa_ctl = ar9003_modal_header(ah, is2ghz)->txFrameToXpaOn;
	if (is2ghz)
		REG_RMW_FIELD(ah, AR_PHY_XPA_TIMING_CTL,
			      AR_PHY_XPA_TIMING_CTL_FRAME_XPAB_ON, xpa_ctl);
	else
		REG_RMW_FIELD(ah, AR_PHY_XPA_TIMING_CTL,
			      AR_PHY_XPA_TIMING_CTL_FRAME_XPAA_ON, xpa_ctl);
}