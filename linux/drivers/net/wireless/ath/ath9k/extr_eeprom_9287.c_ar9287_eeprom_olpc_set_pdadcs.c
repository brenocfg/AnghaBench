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
typedef  int txPower ;
struct ath_hw {int dummy; } ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int REG_READ (struct ath_hw*,int) ; 
 int /*<<< orphan*/  REG_WRITE (struct ath_hw*,int,int) ; 

__attribute__((used)) static void ar9287_eeprom_olpc_set_pdadcs(struct ath_hw *ah,
					  int32_t txPower, u16 chain)
{
	u32 tmpVal;
	u32 a;

	/* Enable OLPC for chain 0 */

	tmpVal = REG_READ(ah, 0xa270);
	tmpVal = tmpVal & 0xFCFFFFFF;
	tmpVal = tmpVal | (0x3 << 24);
	REG_WRITE(ah, 0xa270, tmpVal);

	/* Enable OLPC for chain 1 */

	tmpVal = REG_READ(ah, 0xb270);
	tmpVal = tmpVal & 0xFCFFFFFF;
	tmpVal = tmpVal | (0x3 << 24);
	REG_WRITE(ah, 0xb270, tmpVal);

	/* Write the OLPC ref power for chain 0 */

	if (chain == 0) {
		tmpVal = REG_READ(ah, 0xa398);
		tmpVal = tmpVal & 0xff00ffff;
		a = (txPower)&0xff;
		tmpVal = tmpVal | (a << 16);
		REG_WRITE(ah, 0xa398, tmpVal);
	}

	/* Write the OLPC ref power for chain 1 */

	if (chain == 1) {
		tmpVal = REG_READ(ah, 0xb398);
		tmpVal = tmpVal & 0xff00ffff;
		a = (txPower)&0xff;
		tmpVal = tmpVal | (a << 16);
		REG_WRITE(ah, 0xb398, tmpVal);
	}
}