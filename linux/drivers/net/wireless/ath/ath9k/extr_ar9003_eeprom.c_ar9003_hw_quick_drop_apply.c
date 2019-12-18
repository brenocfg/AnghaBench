#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct TYPE_8__ {int quick_drop_low; int quick_drop_high; } ;
struct TYPE_7__ {int quick_drop; } ;
struct TYPE_6__ {int quick_drop; } ;
struct ar9300_base_eep_hdr {int miscConfiguration; } ;
struct ar9300_eeprom {TYPE_4__ base_ext1; TYPE_3__ modalHeader5G; TYPE_2__ modalHeader2G; struct ar9300_base_eep_hdr baseEepHeader; } ;
struct TYPE_5__ {struct ar9300_eeprom ar9300_eep; } ;
struct ath_hw {TYPE_1__ eeprom; } ;
typedef  int s32 ;

/* Variables and functions */
 int /*<<< orphan*/  AR_PHY_AGC ; 
 int /*<<< orphan*/  AR_PHY_AGC_QUICK_DROP ; 
 scalar_t__ AR_SREV_9300 (struct ath_hw*) ; 
 scalar_t__ AR_SREV_9340 (struct ath_hw*) ; 
 scalar_t__ AR_SREV_9580 (struct ath_hw*) ; 
 int BIT (int) ; 
 int /*<<< orphan*/  REG_RMW_FIELD (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int ar9003_hw_power_interpolate (int,int*,int*,int) ; 

__attribute__((used)) static void ar9003_hw_quick_drop_apply(struct ath_hw *ah, u16 freq)
{
	struct ar9300_eeprom *eep = &ah->eeprom.ar9300_eep;
	struct ar9300_base_eep_hdr *pBase = &eep->baseEepHeader;
	int quick_drop;
	s32 t[3], f[3] = {5180, 5500, 5785};

	if (!(pBase->miscConfiguration & BIT(4)))
		return;

	if (AR_SREV_9300(ah) || AR_SREV_9580(ah) || AR_SREV_9340(ah)) {
		if (freq < 4000) {
			quick_drop = eep->modalHeader2G.quick_drop;
		} else {
			t[0] = eep->base_ext1.quick_drop_low;
			t[1] = eep->modalHeader5G.quick_drop;
			t[2] = eep->base_ext1.quick_drop_high;
			quick_drop = ar9003_hw_power_interpolate(freq, f, t, 3);
		}
		REG_RMW_FIELD(ah, AR_PHY_AGC, AR_PHY_AGC_QUICK_DROP, quick_drop);
	}
}