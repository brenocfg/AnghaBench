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
typedef  int u8 ;
typedef  int u32 ;
struct ath_hw {int txchainmask; int /*<<< orphan*/  curchan; } ;
struct ath_common {int /*<<< orphan*/  curbssid; int /*<<< orphan*/  macaddr; } ;

/* Variables and functions */
 scalar_t__ AR_SREV_9462_20_OR_LATER (struct ath_hw*) ; 
 scalar_t__ AR_SREV_9565 (struct ath_hw*) ; 
 int AR_WOW_KA_DESC_WORD2 ; 
 int AR_WOW_TXBUF (int) ; 
 int ETH_ALEN ; 
 scalar_t__ IS_CHAN_2GHZ (int /*<<< orphan*/ ) ; 
 int KAL_DURATION_ID ; 
 int KAL_FRAME_LEN ; 
 int KAL_FRAME_SUB_TYPE ; 
 int KAL_FRAME_TYPE ; 
 int KAL_NUM_DATA_WORDS ; 
 int KAL_NUM_DESC_WORDS ; 
 int KAL_TO_DS ; 
 int MAX_RATE_POWER ; 
 int /*<<< orphan*/  REG_WRITE (struct ath_hw*,int,int) ; 
 struct ath_common* ath9k_hw_common (struct ath_hw*) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ath9k_wow_create_keep_alive_pattern(struct ath_hw *ah)
{
	struct ath_common *common = ath9k_hw_common(ah);
	u8 sta_mac_addr[ETH_ALEN], ap_mac_addr[ETH_ALEN];
	u32 ctl[13] = {0};
	u32 data_word[KAL_NUM_DATA_WORDS];
	u8 i;
	u32 wow_ka_data_word0;

	memcpy(sta_mac_addr, common->macaddr, ETH_ALEN);
	memcpy(ap_mac_addr, common->curbssid, ETH_ALEN);

	/* set the transmit buffer */
	ctl[0] = (KAL_FRAME_LEN | (MAX_RATE_POWER << 16));
	ctl[1] = 0;
	ctl[4] = 0;
	ctl[7] = (ah->txchainmask) << 2;
	ctl[2] = 0xf << 16; /* tx_tries 0 */

	if (IS_CHAN_2GHZ(ah->curchan))
		ctl[3] = 0x1b;	/* CCK_1M */
	else
		ctl[3] = 0xb;	/* OFDM_6M */

	for (i = 0; i < KAL_NUM_DESC_WORDS; i++)
		REG_WRITE(ah, (AR_WOW_KA_DESC_WORD2 + i * 4), ctl[i]);

	data_word[0] = (KAL_FRAME_TYPE << 2) | (KAL_FRAME_SUB_TYPE << 4) |
		       (KAL_TO_DS << 8) | (KAL_DURATION_ID << 16);
	data_word[1] = (ap_mac_addr[3] << 24) | (ap_mac_addr[2] << 16) |
		       (ap_mac_addr[1] << 8) | (ap_mac_addr[0]);
	data_word[2] = (sta_mac_addr[1] << 24) | (sta_mac_addr[0] << 16) |
		       (ap_mac_addr[5] << 8) | (ap_mac_addr[4]);
	data_word[3] = (sta_mac_addr[5] << 24) | (sta_mac_addr[4] << 16) |
		       (sta_mac_addr[3] << 8) | (sta_mac_addr[2]);
	data_word[4] = (ap_mac_addr[3] << 24) | (ap_mac_addr[2] << 16) |
		       (ap_mac_addr[1] << 8) | (ap_mac_addr[0]);
	data_word[5] = (ap_mac_addr[5] << 8) | (ap_mac_addr[4]);

	if (AR_SREV_9462_20_OR_LATER(ah) || AR_SREV_9565(ah)) {
		/*
		 * AR9462 2.0 and AR9565 have an extra descriptor word
		 * (time based discard) compared to other chips.
		 */
		REG_WRITE(ah, (AR_WOW_KA_DESC_WORD2 + (12 * 4)), 0);
		wow_ka_data_word0 = AR_WOW_TXBUF(13);
	} else {
		wow_ka_data_word0 = AR_WOW_TXBUF(12);
	}

	for (i = 0; i < KAL_NUM_DATA_WORDS; i++)
		REG_WRITE(ah, (wow_ka_data_word0 + i*4), data_word[i]);
}