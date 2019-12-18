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
typedef  int /*<<< orphan*/  u32 ;
struct ath_hw {int /*<<< orphan*/  curchan; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCK_SIFS_TIME ; 
 scalar_t__ IS_CHAN_HALF_RATE (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_CHAN_QUARTER_RATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OFDM_SIFS_TIME ; 
 int /*<<< orphan*/  OFDM_SIFS_TIME_HALF ; 
 int /*<<< orphan*/  OFDM_SIFS_TIME_QUARTER ; 
 int WLAN_RC_PHY_OFDM ; 

__attribute__((used)) static inline u32 ath_dynack_get_sifs(struct ath_hw *ah, int phy)
{
	u32 sifs = CCK_SIFS_TIME;

	if (phy == WLAN_RC_PHY_OFDM) {
		if (IS_CHAN_QUARTER_RATE(ah->curchan))
			sifs = OFDM_SIFS_TIME_QUARTER;
		else if (IS_CHAN_HALF_RATE(ah->curchan))
			sifs = OFDM_SIFS_TIME_HALF;
		else
			sifs = OFDM_SIFS_TIME;
	}
	return sifs;
}