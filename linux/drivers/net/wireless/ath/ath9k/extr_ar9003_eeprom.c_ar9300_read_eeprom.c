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
typedef  int /*<<< orphan*/  u8 ;
struct ath_hw {int dummy; } ;
struct ath_common {int dummy; } ;

/* Variables and functions */
 int AR9300_EEPROM_SIZE ; 
 int /*<<< orphan*/  EEPROM ; 
 int /*<<< orphan*/  ar9300_eeprom_read_byte (struct ath_hw*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ar9300_eeprom_read_word (struct ath_hw*,int,int /*<<< orphan*/ *) ; 
 struct ath_common* ath9k_hw_common (struct ath_hw*) ; 
 int /*<<< orphan*/  ath_dbg (struct ath_common*,int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static bool ar9300_read_eeprom(struct ath_hw *ah, int address, u8 *buffer,
			       int count)
{
	struct ath_common *common = ath9k_hw_common(ah);
	int i;

	if ((address < 0) || ((address + count) / 2 > AR9300_EEPROM_SIZE - 1)) {
		ath_dbg(common, EEPROM, "eeprom address not in range\n");
		return false;
	}

	/*
	 * Since we're reading the bytes in reverse order from a little-endian
	 * word stream, an even address means we only use the lower half of
	 * the 16-bit word at that address
	 */
	if (address % 2 == 0) {
		if (!ar9300_eeprom_read_byte(ah, address--, buffer++))
			goto error;

		count--;
	}

	for (i = 0; i < count / 2; i++) {
		if (!ar9300_eeprom_read_word(ah, address, buffer))
			goto error;

		address -= 2;
		buffer += 2;
	}

	if (count % 2)
		if (!ar9300_eeprom_read_byte(ah, address, buffer))
			goto error;

	return true;

error:
	ath_dbg(common, EEPROM, "unable to read eeprom region at offset %d\n",
		address);
	return false;
}