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
struct ath_hw {int /*<<< orphan*/  analogBank6Data; } ;
struct ath_common {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR_SREV_5416 (struct ath_hw*) ; 
 int /*<<< orphan*/  AR_SREV_9280_20_OR_LATER (struct ath_hw*) ; 
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CONFIG ; 
 int /*<<< orphan*/  ar5008_hw_phy_modify_rx_buffer (int /*<<< orphan*/ ,int,int,int,int) ; 
 int /*<<< orphan*/  ar5008_write_bank6 (struct ath_hw*,int*) ; 
 struct ath_common* ath9k_hw_common (struct ath_hw*) ; 
 int ath9k_hw_reverse_bits (int,int) ; 
 int /*<<< orphan*/  ath_dbg (struct ath_common*,int /*<<< orphan*/ ,char*,int,int) ; 

__attribute__((used)) static void ar5008_hw_force_bias(struct ath_hw *ah, u16 synth_freq)
{
	struct ath_common *common = ath9k_hw_common(ah);
	u32 tmp_reg;
	int reg_writes = 0;
	u32 new_bias = 0;

	if (!AR_SREV_5416(ah) || synth_freq >= 3000)
		return;

	BUG_ON(AR_SREV_9280_20_OR_LATER(ah));

	if (synth_freq < 2412)
		new_bias = 0;
	else if (synth_freq < 2422)
		new_bias = 1;
	else
		new_bias = 2;

	/* pre-reverse this field */
	tmp_reg = ath9k_hw_reverse_bits(new_bias, 3);

	ath_dbg(common, CONFIG, "Force rf_pwd_icsyndiv to %1d on %4d\n",
		new_bias, synth_freq);

	/* swizzle rf_pwd_icsyndiv */
	ar5008_hw_phy_modify_rx_buffer(ah->analogBank6Data, tmp_reg, 3, 181, 3);

	/* write Bank 6 with new params */
	ar5008_write_bank6(ah, &reg_writes);
}