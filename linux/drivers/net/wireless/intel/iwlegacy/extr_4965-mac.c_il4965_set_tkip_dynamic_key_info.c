#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
struct TYPE_6__ {size_t bcast_id; } ;
struct il_priv {int /*<<< orphan*/  sta_lock; TYPE_5__* stations; TYPE_1__ hw_params; } ;
struct ieee80211_key_conf {int keyidx; int /*<<< orphan*/  key; int /*<<< orphan*/  cipher; int /*<<< orphan*/  flags; } ;
typedef  int __le16 ;
struct TYPE_8__ {int key_flags; scalar_t__ key_offset; int /*<<< orphan*/  key; } ;
struct TYPE_9__ {TYPE_3__ key; } ;
struct TYPE_7__ {int keylen; int /*<<< orphan*/  key; int /*<<< orphan*/  cipher; } ;
struct TYPE_10__ {TYPE_4__ sta; TYPE_2__ keyinfo; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_KEY_FLAG_GENERATE_IV ; 
 int /*<<< orphan*/  IEEE80211_KEY_FLAG_GENERATE_MMIC ; 
 int STA_KEY_FLG_ENCRYPT_MSK ; 
 int STA_KEY_FLG_INVALID ; 
 int STA_KEY_FLG_KEYID_POS ; 
 int STA_KEY_FLG_MAP_KEY_MSK ; 
 int STA_KEY_FLG_NO_ENC ; 
 int STA_KEY_FLG_TKIP ; 
 int STA_KEY_MULTICAST_MSK ; 
 int /*<<< orphan*/  WARN (int,char*) ; 
 scalar_t__ WEP_INVALID_OFFSET ; 
 int cpu_to_le16 (int) ; 
 scalar_t__ il_get_free_ucode_key_idx (struct il_priv*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int
il4965_set_tkip_dynamic_key_info(struct il_priv *il,
				 struct ieee80211_key_conf *keyconf, u8 sta_id)
{
	unsigned long flags;
	int ret = 0;
	__le16 key_flags = 0;

	key_flags |= (STA_KEY_FLG_TKIP | STA_KEY_FLG_MAP_KEY_MSK);
	key_flags |= cpu_to_le16(keyconf->keyidx << STA_KEY_FLG_KEYID_POS);
	key_flags &= ~STA_KEY_FLG_INVALID;

	if (sta_id == il->hw_params.bcast_id)
		key_flags |= STA_KEY_MULTICAST_MSK;

	keyconf->flags |= IEEE80211_KEY_FLAG_GENERATE_IV;
	keyconf->flags |= IEEE80211_KEY_FLAG_GENERATE_MMIC;

	spin_lock_irqsave(&il->sta_lock, flags);

	il->stations[sta_id].keyinfo.cipher = keyconf->cipher;
	il->stations[sta_id].keyinfo.keylen = 16;

	if ((il->stations[sta_id].sta.key.
	     key_flags & STA_KEY_FLG_ENCRYPT_MSK) == STA_KEY_FLG_NO_ENC)
		il->stations[sta_id].sta.key.key_offset =
		    il_get_free_ucode_key_idx(il);
	/* else, we are overriding an existing key => no need to allocated room
	 * in uCode. */

	WARN(il->stations[sta_id].sta.key.key_offset == WEP_INVALID_OFFSET,
	     "no space for a new key");

	il->stations[sta_id].sta.key.key_flags = key_flags;

	/* This copy is acutally not needed: we get the key with each TX */
	memcpy(il->stations[sta_id].keyinfo.key, keyconf->key, 16);

	memcpy(il->stations[sta_id].sta.key.key, keyconf->key, 16);

	spin_unlock_irqrestore(&il->sta_lock, flags);

	return ret;
}