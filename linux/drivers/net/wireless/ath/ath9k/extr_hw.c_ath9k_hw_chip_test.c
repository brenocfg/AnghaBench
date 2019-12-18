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
struct ath_hw {int dummy; } ;
struct ath_common {int dummy; } ;

/* Variables and functions */
 int AR_PHY_BASE ; 
 int /*<<< orphan*/  AR_SREV_9300_20_OR_LATER (struct ath_hw*) ; 
 int AR_STA_ID0 ; 
 int REG_READ (struct ath_hw*,int) ; 
 int /*<<< orphan*/  REG_WRITE (struct ath_hw*,int,int) ; 
 struct ath_common* ath9k_hw_common (struct ath_hw*) ; 
 int /*<<< orphan*/  ath_err (struct ath_common*,char*,int,int,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static bool ath9k_hw_chip_test(struct ath_hw *ah)
{
	struct ath_common *common = ath9k_hw_common(ah);
	u32 regAddr[2] = { AR_STA_ID0 };
	u32 regHold[2];
	static const u32 patternData[4] = {
		0x55555555, 0xaaaaaaaa, 0x66666666, 0x99999999
	};
	int i, j, loop_max;

	if (!AR_SREV_9300_20_OR_LATER(ah)) {
		loop_max = 2;
		regAddr[1] = AR_PHY_BASE + (8 << 2);
	} else
		loop_max = 1;

	for (i = 0; i < loop_max; i++) {
		u32 addr = regAddr[i];
		u32 wrData, rdData;

		regHold[i] = REG_READ(ah, addr);
		for (j = 0; j < 0x100; j++) {
			wrData = (j << 16) | j;
			REG_WRITE(ah, addr, wrData);
			rdData = REG_READ(ah, addr);
			if (rdData != wrData) {
				ath_err(common,
					"address test failed addr: 0x%08x - wr:0x%08x != rd:0x%08x\n",
					addr, wrData, rdData);
				return false;
			}
		}
		for (j = 0; j < 4; j++) {
			wrData = patternData[j];
			REG_WRITE(ah, addr, wrData);
			rdData = REG_READ(ah, addr);
			if (wrData != rdData) {
				ath_err(common,
					"address test failed addr: 0x%08x - wr:0x%08x != rd:0x%08x\n",
					addr, wrData, rdData);
				return false;
			}
		}
		REG_WRITE(ah, regAddr[i], regHold[i]);
	}
	udelay(100);

	return true;
}