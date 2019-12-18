#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct ath_hw {TYPE_1__* eep_ops; } ;
struct TYPE_5__ {int (* check_eeprom ) (struct ath_hw*) ;int /*<<< orphan*/  (* fill_eeprom ) (struct ath_hw*) ;} ;

/* Variables and functions */
 scalar_t__ AR_SREV_9271 (struct ath_hw*) ; 
 scalar_t__ AR_SREV_9285 (struct ath_hw*) ; 
 scalar_t__ AR_SREV_9287 (struct ath_hw*) ; 
 scalar_t__ AR_SREV_9300_20_OR_LATER (struct ath_hw*) ; 
 int EIO ; 
 TYPE_1__ eep_4k_ops ; 
 TYPE_1__ eep_ar9287_ops ; 
 TYPE_1__ eep_ar9300_ops ; 
 TYPE_1__ eep_def_ops ; 
 int /*<<< orphan*/  stub1 (struct ath_hw*) ; 
 int stub2 (struct ath_hw*) ; 

int ath9k_hw_eeprom_init(struct ath_hw *ah)
{
	int status;

	if (AR_SREV_9300_20_OR_LATER(ah))
		ah->eep_ops = &eep_ar9300_ops;
	else if (AR_SREV_9287(ah)) {
		ah->eep_ops = &eep_ar9287_ops;
	} else if (AR_SREV_9285(ah) || AR_SREV_9271(ah)) {
		ah->eep_ops = &eep_4k_ops;
	} else {
		ah->eep_ops = &eep_def_ops;
	}

	if (!ah->eep_ops->fill_eeprom(ah))
		return -EIO;

	status = ah->eep_ops->check_eeprom(ah);

	return status;
}