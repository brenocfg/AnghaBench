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
struct ath9k_channel {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR_CST ; 
 int AR_CST_TIMEOUT_LIMIT_S ; 
 int /*<<< orphan*/  AR_GTXTO ; 
 int AR_GTXTO_TIMEOUT_LIMIT_S ; 
 int AR_PHY_FC_DYN2040_EN ; 
 int AR_PHY_FC_DYN2040_PRI_CH ; 
 int AR_PHY_FC_ENABLE_DAC_FIFO ; 
 int AR_PHY_FC_HT_EN ; 
 int AR_PHY_FC_SHORT_GI_40 ; 
 int AR_PHY_FC_SINGLE_HT_LTF1 ; 
 int AR_PHY_FC_WALSH ; 
 int /*<<< orphan*/  AR_PHY_TURBO ; 
 scalar_t__ AR_SREV_9285_12_OR_LATER (struct ath_hw*) ; 
 int /*<<< orphan*/  ENABLE_REGWRITE_BUFFER (struct ath_hw*) ; 
 scalar_t__ IS_CHAN_HT40 (struct ath9k_channel*) ; 
 scalar_t__ IS_CHAN_HT40PLUS (struct ath9k_channel*) ; 
 int /*<<< orphan*/  REGWRITE_BUFFER_FLUSH (struct ath_hw*) ; 
 int REG_READ (struct ath_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_WRITE (struct ath_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ath9k_hw_set11nmac2040 (struct ath_hw*,struct ath9k_channel*) ; 

__attribute__((used)) static void ar5008_hw_set_channel_regs(struct ath_hw *ah,
				       struct ath9k_channel *chan)
{
	u32 phymode;
	u32 enableDacFifo = 0;

	if (AR_SREV_9285_12_OR_LATER(ah))
		enableDacFifo = (REG_READ(ah, AR_PHY_TURBO) &
					 AR_PHY_FC_ENABLE_DAC_FIFO);

	phymode = AR_PHY_FC_HT_EN | AR_PHY_FC_SHORT_GI_40
		| AR_PHY_FC_SINGLE_HT_LTF1 | AR_PHY_FC_WALSH | enableDacFifo;

	if (IS_CHAN_HT40(chan)) {
		phymode |= AR_PHY_FC_DYN2040_EN;

		if (IS_CHAN_HT40PLUS(chan))
			phymode |= AR_PHY_FC_DYN2040_PRI_CH;

	}
	ENABLE_REGWRITE_BUFFER(ah);
	REG_WRITE(ah, AR_PHY_TURBO, phymode);

	/* This function do only REG_WRITE, so
	 * we can include it to REGWRITE_BUFFER. */
	ath9k_hw_set11nmac2040(ah, chan);

	REG_WRITE(ah, AR_GTXTO, 25 << AR_GTXTO_TIMEOUT_LIMIT_S);
	REG_WRITE(ah, AR_CST, 0xF << AR_CST_TIMEOUT_LIMIT_S);

	REGWRITE_BUFFER_FLUSH(ah);
}