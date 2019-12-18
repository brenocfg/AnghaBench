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
 int /*<<< orphan*/  AR_PHY_MODE ; 
 int AR_PHY_MODE_DYNAMIC ; 
 int AR_PHY_MODE_DYN_CCK_DISABLE ; 
 int AR_PHY_MODE_OFDM ; 
 int AR_PHY_MODE_RF2GHZ ; 
 int AR_PHY_MODE_RF5GHZ ; 
 int /*<<< orphan*/  AR_SREV_9280_20_OR_LATER (struct ath_hw*) ; 
 scalar_t__ IS_CHAN_2GHZ (struct ath9k_channel*) ; 
 scalar_t__ IS_CHAN_5GHZ (struct ath9k_channel*) ; 
 scalar_t__ IS_CHAN_A_FAST_CLOCK (struct ath_hw*,struct ath9k_channel*) ; 
 int /*<<< orphan*/  REG_WRITE (struct ath_hw*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ar5008_hw_set_rfmode(struct ath_hw *ah, struct ath9k_channel *chan)
{
	u32 rfMode = 0;

	if (chan == NULL)
		return;

	if (IS_CHAN_2GHZ(chan))
		rfMode |= AR_PHY_MODE_DYNAMIC;
	else
		rfMode |= AR_PHY_MODE_OFDM;

	if (!AR_SREV_9280_20_OR_LATER(ah))
		rfMode |= (IS_CHAN_5GHZ(chan)) ?
			AR_PHY_MODE_RF5GHZ : AR_PHY_MODE_RF2GHZ;

	if (IS_CHAN_A_FAST_CLOCK(ah, chan))
		rfMode |= (AR_PHY_MODE_DYNAMIC | AR_PHY_MODE_DYN_CCK_DISABLE);

	REG_WRITE(ah, AR_PHY_MODE, rfMode);
}