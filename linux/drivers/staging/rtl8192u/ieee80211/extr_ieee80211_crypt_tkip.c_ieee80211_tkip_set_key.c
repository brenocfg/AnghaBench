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
struct ieee80211_tkip_data {int key_idx; int key_set; int tx_iv16; int rx_iv32; int rx_iv16; int /*<<< orphan*/  key; struct crypto_sync_skcipher* rx_tfm_arc4; struct crypto_shash* rx_tfm_michael; struct crypto_sync_skcipher* tx_tfm_arc4; struct crypto_shash* tx_tfm_michael; } ;
struct crypto_sync_skcipher {int dummy; } ;
struct crypto_shash {int dummy; } ;

/* Variables and functions */
 int TKIP_KEY_LEN ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  memset (struct ieee80211_tkip_data*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ieee80211_tkip_set_key(void *key, int len, u8 *seq, void *priv)
{
	struct ieee80211_tkip_data *tkey = priv;
	int keyidx;
	struct crypto_shash *tfm = tkey->tx_tfm_michael;
	struct crypto_sync_skcipher *tfm2 = tkey->tx_tfm_arc4;
	struct crypto_shash *tfm3 = tkey->rx_tfm_michael;
	struct crypto_sync_skcipher *tfm4 = tkey->rx_tfm_arc4;

	keyidx = tkey->key_idx;
	memset(tkey, 0, sizeof(*tkey));
	tkey->key_idx = keyidx;
	tkey->tx_tfm_michael = tfm;
	tkey->tx_tfm_arc4 = tfm2;
	tkey->rx_tfm_michael = tfm3;
	tkey->rx_tfm_arc4 = tfm4;

	if (len == TKIP_KEY_LEN) {
		memcpy(tkey->key, key, TKIP_KEY_LEN);
		tkey->key_set = 1;
		tkey->tx_iv16 = 1; /* TSC is initialized to 1 */
		if (seq) {
			tkey->rx_iv32 = (seq[5] << 24) | (seq[4] << 16) |
				(seq[3] << 8) | seq[2];
			tkey->rx_iv16 = (seq[1] << 8) | seq[0];
		}
	} else if (len == 0)
		tkey->key_set = 0;
	else
		return -1;

	return 0;
}