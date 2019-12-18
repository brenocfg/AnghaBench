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
typedef  int /*<<< orphan*/  u16 ;
struct ath_hw {int dummy; } ;
struct ath_common {TYPE_1__* ops; scalar_t__ ah; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* read ) (struct ath_hw*,scalar_t__) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  AH_WAIT_TIMEOUT ; 
 scalar_t__ AR5416_EEPROM_OFFSET ; 
 int AR5416_EEPROM_S ; 
 scalar_t__ AR_EEPROM_STATUS_DATA ; 
 int AR_EEPROM_STATUS_DATA_BUSY ; 
 int AR_EEPROM_STATUS_DATA_PROT_ACCESS ; 
 int /*<<< orphan*/  AR_EEPROM_STATUS_DATA_VAL ; 
 int /*<<< orphan*/  MS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath9k_hw_wait (struct ath_hw*,scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct ath_hw*,scalar_t__) ; 
 int /*<<< orphan*/  stub2 (struct ath_hw*,scalar_t__) ; 

__attribute__((used)) static bool ath_pci_eeprom_read(struct ath_common *common, u32 off, u16 *data)
{
	struct ath_hw *ah = (struct ath_hw *) common->ah;

	common->ops->read(ah, AR5416_EEPROM_OFFSET + (off << AR5416_EEPROM_S));

	if (!ath9k_hw_wait(ah,
				AR_EEPROM_STATUS_DATA,
				AR_EEPROM_STATUS_DATA_BUSY |
				AR_EEPROM_STATUS_DATA_PROT_ACCESS, 0,
				AH_WAIT_TIMEOUT)) {
		return false;
	}

	*data = MS(common->ops->read(ah, AR_EEPROM_STATUS_DATA),
			AR_EEPROM_STATUS_DATA_VAL);

	return true;
}