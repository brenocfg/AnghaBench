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
typedef  int u16 ;
struct ath_hw {int /*<<< orphan*/  eeprom; } ;
struct ath_common {int dummy; } ;

/* Variables and functions */
 struct ath_common* ath9k_hw_common (struct ath_hw*) ; 
 int /*<<< orphan*/  ath_err (struct ath_common*,char*,int) ; 

bool ath9k_hw_nvram_validate_checksum(struct ath_hw *ah, int size)
{
	u32 i, sum = 0;
	u16 *eepdata = (u16 *)(&ah->eeprom);
	struct ath_common *common = ath9k_hw_common(ah);

	for (i = 0; i < size; i++)
		sum ^= eepdata[i];

	if (sum != 0xffff) {
		ath_err(common, "Bad EEPROM checksum 0x%x\n", sum);
		return false;
	}

	return true;
}