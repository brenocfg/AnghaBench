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
typedef  int u64 ;
typedef  int u32 ;
struct mt76x02_dev {int dummy; } ;
struct ieee80211_key_conf {int /*<<< orphan*/  tx_pn; } ;
typedef  enum mt76x02_cipher_type { ____Placeholder_mt76x02_cipher_type } mt76x02_cipher_type ;

/* Variables and functions */
 int MT_CIPHER_AES_CCMP ; 
 int MT_CIPHER_TKIP ; 
 scalar_t__ MT_WCID_IV (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic64_set (int /*<<< orphan*/ *,int) ; 
 int mt76_rr (struct mt76x02_dev*,scalar_t__) ; 
 int mt76x02_mac_get_key_info (struct ieee80211_key_conf*,int /*<<< orphan*/ *) ; 

void mt76x02_mac_wcid_sync_pn(struct mt76x02_dev *dev, u8 idx,
			      struct ieee80211_key_conf *key)
{
	enum mt76x02_cipher_type cipher;
	u8 key_data[32];
	u32 iv, eiv;
	u64 pn;

	cipher = mt76x02_mac_get_key_info(key, key_data);
	iv = mt76_rr(dev, MT_WCID_IV(idx));
	eiv = mt76_rr(dev, MT_WCID_IV(idx) + 4);

	pn = (u64)eiv << 16;
	if (cipher == MT_CIPHER_TKIP) {
		pn |= (iv >> 16) & 0xff;
		pn |= (iv & 0xff) << 8;
	} else if (cipher >= MT_CIPHER_AES_CCMP) {
		pn |= iv & 0xffff;
	} else {
		return;
	}

	atomic64_set(&key->tx_pn, pn);
}