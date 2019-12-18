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
struct sk_buff {int* data; int len; } ;
struct ieee80211_rx_status {int flag; } ;
struct ieee80211_hdr {int /*<<< orphan*/  frame_control; } ;
struct ath_rx_status {int rs_keyix; } ;
struct ath_hw {scalar_t__ sw_mgmt_crypto_rx; } ;
struct ath_common {int /*<<< orphan*/  keymap; struct ath_hw* ah; } ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int ATH9K_RXKEYIX_INVALID ; 
 int FCS_LEN ; 
 int RX_FLAG_DECRYPTED ; 
 int ieee80211_get_hdrlen_from_skb (struct sk_buff*) ; 
 scalar_t__ ieee80211_has_protected (int /*<<< orphan*/ ) ; 
 int ieee80211_hdrlen (int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_is_mgmt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 
 scalar_t__ test_bit (int,int /*<<< orphan*/ ) ; 

void ath9k_cmn_rx_skb_postprocess(struct ath_common *common,
				  struct sk_buff *skb,
				  struct ath_rx_status *rx_stats,
				  struct ieee80211_rx_status *rxs,
				  bool decrypt_error)
{
	struct ath_hw *ah = common->ah;
	struct ieee80211_hdr *hdr;
	int hdrlen, padpos, padsize;
	u8 keyix;
	__le16 fc;

	/* see if any padding is done by the hw and remove it */
	hdr = (struct ieee80211_hdr *) skb->data;
	hdrlen = ieee80211_get_hdrlen_from_skb(skb);
	fc = hdr->frame_control;
	padpos = ieee80211_hdrlen(fc);

	/* The MAC header is padded to have 32-bit boundary if the
	 * packet payload is non-zero. The general calculation for
	 * padsize would take into account odd header lengths:
	 * padsize = (4 - padpos % 4) % 4; However, since only
	 * even-length headers are used, padding can only be 0 or 2
	 * bytes and we can optimize this a bit. In addition, we must
	 * not try to remove padding from short control frames that do
	 * not have payload. */
	padsize = padpos & 3;
	if (padsize && skb->len>=padpos+padsize+FCS_LEN) {
		memmove(skb->data + padsize, skb->data, padpos);
		skb_pull(skb, padsize);
	}

	keyix = rx_stats->rs_keyix;

	if (!(keyix == ATH9K_RXKEYIX_INVALID) && !decrypt_error &&
	    ieee80211_has_protected(fc)) {
		rxs->flag |= RX_FLAG_DECRYPTED;
	} else if (ieee80211_has_protected(fc)
		   && !decrypt_error && skb->len >= hdrlen + 4) {
		keyix = skb->data[hdrlen + 3] >> 6;

		if (test_bit(keyix, common->keymap))
			rxs->flag |= RX_FLAG_DECRYPTED;
	}
	if (ah->sw_mgmt_crypto_rx &&
	    (rxs->flag & RX_FLAG_DECRYPTED) &&
	    ieee80211_is_mgmt(fc))
		/* Use software decrypt for management frames. */
		rxs->flag &= ~RX_FLAG_DECRYPTED;
}