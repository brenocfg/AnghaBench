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
typedef  scalar_t__ u16 ;
struct ath_keyval {int /*<<< orphan*/  kv_mic; int /*<<< orphan*/  kv_txmic; } ;
struct ath_common {int crypt_caps; } ;

/* Variables and functions */
 int ATH_CRYPT_CAP_MIC_COMBINED ; 
 int NL80211_TKIP_DATA_OFFSET_RX_MIC_KEY ; 
 int NL80211_TKIP_DATA_OFFSET_TX_MIC_KEY ; 
 int /*<<< orphan*/  ath_err (struct ath_common*,char*) ; 
 int ath_hw_set_keycache_entry (struct ath_common*,scalar_t__,struct ath_keyval*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static int ath_setkey_tkip(struct ath_common *common, u16 keyix, const u8 *key,
			   struct ath_keyval *hk, const u8 *addr,
			   bool authenticator)
{
	const u8 *key_rxmic;
	const u8 *key_txmic;

	key_txmic = key + NL80211_TKIP_DATA_OFFSET_TX_MIC_KEY;
	key_rxmic = key + NL80211_TKIP_DATA_OFFSET_RX_MIC_KEY;

	if (addr == NULL) {
		/*
		 * Group key installation - only two key cache entries are used
		 * regardless of splitmic capability since group key is only
		 * used either for TX or RX.
		 */
		if (authenticator) {
			memcpy(hk->kv_mic, key_txmic, sizeof(hk->kv_mic));
			memcpy(hk->kv_txmic, key_txmic, sizeof(hk->kv_mic));
		} else {
			memcpy(hk->kv_mic, key_rxmic, sizeof(hk->kv_mic));
			memcpy(hk->kv_txmic, key_rxmic, sizeof(hk->kv_mic));
		}
		return ath_hw_set_keycache_entry(common, keyix, hk, addr);
	}
	if (common->crypt_caps & ATH_CRYPT_CAP_MIC_COMBINED) {
		/* TX and RX keys share the same key cache entry. */
		memcpy(hk->kv_mic, key_rxmic, sizeof(hk->kv_mic));
		memcpy(hk->kv_txmic, key_txmic, sizeof(hk->kv_txmic));
		return ath_hw_set_keycache_entry(common, keyix, hk, addr);
	}

	/* Separate key cache entries for TX and RX */

	/* TX key goes at first index, RX key at +32. */
	memcpy(hk->kv_mic, key_txmic, sizeof(hk->kv_mic));
	if (!ath_hw_set_keycache_entry(common, keyix, hk, NULL)) {
		/* TX MIC entry failed. No need to proceed further */
		ath_err(common, "Setting TX MIC Key Failed\n");
		return 0;
	}

	memcpy(hk->kv_mic, key_rxmic, sizeof(hk->kv_mic));
	/* XXX delete tx key on failure? */
	return ath_hw_set_keycache_entry(common, keyix + 32, hk, addr);
}