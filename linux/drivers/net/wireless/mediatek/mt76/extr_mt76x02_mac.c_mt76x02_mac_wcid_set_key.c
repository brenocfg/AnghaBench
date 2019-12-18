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
typedef  int u64 ;
struct mt76x02_dev {int dummy; } ;
struct ieee80211_key_conf {int flags; int keyidx; int /*<<< orphan*/  tx_pn; } ;
typedef  int /*<<< orphan*/  key_data ;
typedef  int /*<<< orphan*/  iv_data ;
typedef  enum mt76x02_cipher_type { ____Placeholder_mt76x02_cipher_type } mt76x02_cipher_type ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int IEEE80211_KEY_FLAG_PAIRWISE ; 
 int MT_CIPHER_AES_CCMP ; 
 int MT_CIPHER_NONE ; 
 int MT_CIPHER_TKIP ; 
 int /*<<< orphan*/  MT_WCID_ATTR (int) ; 
 int /*<<< orphan*/  MT_WCID_ATTR_PAIRWISE ; 
 int /*<<< orphan*/  MT_WCID_ATTR_PKEY_MODE ; 
 int /*<<< orphan*/  MT_WCID_IV (int) ; 
 int /*<<< orphan*/  MT_WCID_KEY (int) ; 
 int atomic64_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mt76_rmw_field (struct mt76x02_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mt76_wr_copy (struct mt76x02_dev*,int /*<<< orphan*/ ,int*,int) ; 
 int mt76x02_mac_get_key_info (struct ieee80211_key_conf*,int*) ; 
 int /*<<< orphan*/  put_unaligned_le16 (int,int*) ; 
 int /*<<< orphan*/  put_unaligned_le32 (int,int*) ; 

int mt76x02_mac_wcid_set_key(struct mt76x02_dev *dev, u8 idx,
			     struct ieee80211_key_conf *key)
{
	enum mt76x02_cipher_type cipher;
	u8 key_data[32];
	u8 iv_data[8];
	u64 pn;

	cipher = mt76x02_mac_get_key_info(key, key_data);
	if (cipher == MT_CIPHER_NONE && key)
		return -EOPNOTSUPP;

	mt76_wr_copy(dev, MT_WCID_KEY(idx), key_data, sizeof(key_data));
	mt76_rmw_field(dev, MT_WCID_ATTR(idx), MT_WCID_ATTR_PKEY_MODE, cipher);

	memset(iv_data, 0, sizeof(iv_data));
	if (key) {
		mt76_rmw_field(dev, MT_WCID_ATTR(idx), MT_WCID_ATTR_PAIRWISE,
			       !!(key->flags & IEEE80211_KEY_FLAG_PAIRWISE));

		pn = atomic64_read(&key->tx_pn);

		iv_data[3] = key->keyidx << 6;
		if (cipher >= MT_CIPHER_TKIP) {
			iv_data[3] |= 0x20;
			put_unaligned_le32(pn >> 16, &iv_data[4]);
		}

		if (cipher == MT_CIPHER_TKIP) {
			iv_data[0] = (pn >> 8) & 0xff;
			iv_data[1] = (iv_data[0] | 0x20) & 0x7f;
			iv_data[2] = pn & 0xff;
		} else if (cipher >= MT_CIPHER_AES_CCMP) {
			put_unaligned_le16((pn & 0xffff), &iv_data[0]);
		}
	}

	mt76_wr_copy(dev, MT_WCID_IV(idx), iv_data, sizeof(iv_data));

	return 0;
}