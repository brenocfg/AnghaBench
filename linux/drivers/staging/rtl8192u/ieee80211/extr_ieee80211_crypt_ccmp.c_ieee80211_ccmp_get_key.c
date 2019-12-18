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
struct ieee80211_ccmp_data {int /*<<< orphan*/ * tx_pn; int /*<<< orphan*/  key; int /*<<< orphan*/  key_set; } ;

/* Variables and functions */
 int CCMP_TK_LEN ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ieee80211_ccmp_get_key(void *key, int len, u8 *seq, void *priv)
{
	struct ieee80211_ccmp_data *data = priv;

	if (len < CCMP_TK_LEN)
		return -1;

	if (!data->key_set)
		return 0;
	memcpy(key, data->key, CCMP_TK_LEN);

	if (seq) {
		seq[0] = data->tx_pn[5];
		seq[1] = data->tx_pn[4];
		seq[2] = data->tx_pn[3];
		seq[3] = data->tx_pn[2];
		seq[4] = data->tx_pn[1];
		seq[5] = data->tx_pn[0];
	}

	return CCMP_TK_LEN;
}