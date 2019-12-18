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
struct rt2x00lib_crypto {scalar_t__ cmd; int bssidx; int cipher; int /*<<< orphan*/  address; int /*<<< orphan*/  rx_mic; int /*<<< orphan*/  tx_mic; int /*<<< orphan*/  key; } ;
struct rt2x00_field32 {int bit_offset; int bit_mask; } ;
struct rt2x00_dev {int dummy; } ;
struct ieee80211_key_conf {int hw_key_idx; int keyidx; } ;
struct hw_key_entry {int /*<<< orphan*/  rx_mic; int /*<<< orphan*/  tx_mic; int /*<<< orphan*/  key; } ;
typedef  int /*<<< orphan*/  key_entry ;

/* Variables and functions */
 scalar_t__ SET_KEY ; 
 int /*<<< orphan*/  SHARED_KEY_ENTRY (int) ; 
 int /*<<< orphan*/  SHARED_KEY_MODE_ENTRY (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rt2800_config_wcid (struct rt2x00_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rt2800_config_wcid_attr_bssidx (struct rt2x00_dev*,int,int) ; 
 int /*<<< orphan*/  rt2800_config_wcid_attr_cipher (struct rt2x00_dev*,struct rt2x00lib_crypto*,struct ieee80211_key_conf*) ; 
 int /*<<< orphan*/  rt2800_register_multiwrite (struct rt2x00_dev*,int /*<<< orphan*/ ,struct hw_key_entry*,int) ; 
 int /*<<< orphan*/  rt2800_register_read (struct rt2x00_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2800_register_write (struct rt2x00_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2x00_set_field32 (int /*<<< orphan*/ *,struct rt2x00_field32,int) ; 

int rt2800_config_shared_key(struct rt2x00_dev *rt2x00dev,
			     struct rt2x00lib_crypto *crypto,
			     struct ieee80211_key_conf *key)
{
	struct hw_key_entry key_entry;
	struct rt2x00_field32 field;
	u32 offset;
	u32 reg;

	if (crypto->cmd == SET_KEY) {
		key->hw_key_idx = (4 * crypto->bssidx) + key->keyidx;

		memcpy(key_entry.key, crypto->key,
		       sizeof(key_entry.key));
		memcpy(key_entry.tx_mic, crypto->tx_mic,
		       sizeof(key_entry.tx_mic));
		memcpy(key_entry.rx_mic, crypto->rx_mic,
		       sizeof(key_entry.rx_mic));

		offset = SHARED_KEY_ENTRY(key->hw_key_idx);
		rt2800_register_multiwrite(rt2x00dev, offset,
					      &key_entry, sizeof(key_entry));
	}

	/*
	 * The cipher types are stored over multiple registers
	 * starting with SHARED_KEY_MODE_BASE each word will have
	 * 32 bits and contains the cipher types for 2 bssidx each.
	 * Using the correct defines correctly will cause overhead,
	 * so just calculate the correct offset.
	 */
	field.bit_offset = 4 * (key->hw_key_idx % 8);
	field.bit_mask = 0x7 << field.bit_offset;

	offset = SHARED_KEY_MODE_ENTRY(key->hw_key_idx / 8);

	reg = rt2800_register_read(rt2x00dev, offset);
	rt2x00_set_field32(&reg, field,
			   (crypto->cmd == SET_KEY) * crypto->cipher);
	rt2800_register_write(rt2x00dev, offset, reg);

	/*
	 * Update WCID information
	 */
	rt2800_config_wcid(rt2x00dev, crypto->address, key->hw_key_idx);
	rt2800_config_wcid_attr_bssidx(rt2x00dev, key->hw_key_idx,
				       crypto->bssidx);
	rt2800_config_wcid_attr_cipher(rt2x00dev, crypto, key);

	return 0;
}