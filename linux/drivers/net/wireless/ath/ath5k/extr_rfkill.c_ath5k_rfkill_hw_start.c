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
struct TYPE_4__ {int /*<<< orphan*/  ee_header; int /*<<< orphan*/  ee_rfkill_pol; int /*<<< orphan*/  ee_rfkill_pin; } ;
struct TYPE_5__ {TYPE_1__ cap_eeprom; } ;
struct TYPE_6__ {int /*<<< orphan*/  toggleq; int /*<<< orphan*/  polarity; int /*<<< orphan*/  gpio; } ;
struct ath5k_hw {TYPE_2__ ah_capabilities; TYPE_3__ rf_kill; } ;

/* Variables and functions */
 scalar_t__ AR5K_EEPROM_HDR_RFKILL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath5k_rfkill_disable (struct ath5k_hw*) ; 
 int /*<<< orphan*/  ath5k_rfkill_set_intr (struct ath5k_hw*,int) ; 
 int /*<<< orphan*/  ath5k_tasklet_rfkill_toggle ; 
 int /*<<< orphan*/  tasklet_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 

void
ath5k_rfkill_hw_start(struct ath5k_hw *ah)
{
	/* read rfkill GPIO configuration from EEPROM header */
	ah->rf_kill.gpio = ah->ah_capabilities.cap_eeprom.ee_rfkill_pin;
	ah->rf_kill.polarity = ah->ah_capabilities.cap_eeprom.ee_rfkill_pol;

	tasklet_init(&ah->rf_kill.toggleq, ath5k_tasklet_rfkill_toggle,
		(unsigned long)ah);

	ath5k_rfkill_disable(ah);

	/* enable interrupt for rfkill switch */
	if (AR5K_EEPROM_HDR_RFKILL(ah->ah_capabilities.cap_eeprom.ee_header))
		ath5k_rfkill_set_intr(ah, true);
}