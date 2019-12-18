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
typedef  int u32 ;
struct mt76x02_dev {int dummy; } ;
struct ieee80211_key_conf {int dummy; } ;
typedef  int /*<<< orphan*/  key_data ;
typedef  enum mt76x02_cipher_type { ____Placeholder_mt76x02_cipher_type } mt76x02_cipher_type ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int MT_CIPHER_NONE ; 
 int /*<<< orphan*/  MT_SKEY (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MT_SKEY_MODE (int /*<<< orphan*/ ) ; 
 int MT_SKEY_MODE_MASK ; 
 int MT_SKEY_MODE_SHIFT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mt76_rr (struct mt76x02_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt76_wr (struct mt76x02_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mt76_wr_copy (struct mt76x02_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int mt76x02_mac_get_key_info (struct ieee80211_key_conf*,int /*<<< orphan*/ *) ; 

int mt76x02_mac_shared_key_setup(struct mt76x02_dev *dev, u8 vif_idx,
				 u8 key_idx, struct ieee80211_key_conf *key)
{
	enum mt76x02_cipher_type cipher;
	u8 key_data[32];
	u32 val;

	cipher = mt76x02_mac_get_key_info(key, key_data);
	if (cipher == MT_CIPHER_NONE && key)
		return -EOPNOTSUPP;

	val = mt76_rr(dev, MT_SKEY_MODE(vif_idx));
	val &= ~(MT_SKEY_MODE_MASK << MT_SKEY_MODE_SHIFT(vif_idx, key_idx));
	val |= cipher << MT_SKEY_MODE_SHIFT(vif_idx, key_idx);
	mt76_wr(dev, MT_SKEY_MODE(vif_idx), val);

	mt76_wr_copy(dev, MT_SKEY(vif_idx, key_idx), key_data,
		     sizeof(key_data));

	return 0;
}