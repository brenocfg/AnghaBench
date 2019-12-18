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
 int /*<<< orphan*/  AR_NAV ; 
 int /*<<< orphan*/  BSTUCK ; 
 int REG_READ (struct ath_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_WRITE (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ath_common* ath9k_hw_common (struct ath_hw*) ; 
 int /*<<< orphan*/  ath_dbg (struct ath_common*,int /*<<< orphan*/ ,char*,int) ; 

void ath9k_hw_check_nav(struct ath_hw *ah)
{
	struct ath_common *common = ath9k_hw_common(ah);
	u32 val;

	val = REG_READ(ah, AR_NAV);
	if (val != 0xdeadbeef && val > 0x7fff) {
		ath_dbg(common, BSTUCK, "Abnormal NAV: 0x%x\n", val);
		REG_WRITE(ah, AR_NAV, 0);
	}
}