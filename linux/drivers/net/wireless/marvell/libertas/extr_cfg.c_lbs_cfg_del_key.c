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
struct wiphy {int dummy; } ;
struct net_device {int dummy; } ;
struct lbs_private {scalar_t__* wep_key_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  lbs_deb_assoc (char*,int,int const*) ; 
 int /*<<< orphan*/  lbs_set_wep_keys (struct lbs_private*) ; 
 struct lbs_private* wiphy_priv (struct wiphy*) ; 

__attribute__((used)) static int lbs_cfg_del_key(struct wiphy *wiphy, struct net_device *netdev,
			   u8 key_index, bool pairwise, const u8 *mac_addr)
{

	lbs_deb_assoc("del_key: key_idx %d, mac_addr %pM\n",
		      key_index, mac_addr);

#ifdef TODO
	struct lbs_private *priv = wiphy_priv(wiphy);
	/*
	 * I think can keep this a NO-OP, because:

	 * - we clear all keys whenever we do lbs_cfg_connect() anyway
	 * - neither "iw" nor "wpa_supplicant" won't call this during
	 *   an ongoing connection
	 * - TODO: but I have to check if this is still true when
	 *   I set the AP to periodic re-keying
	 * - we've not kzallec() something when we've added a key at
	 *   lbs_cfg_connect() or lbs_cfg_add_key().
	 *
	 * This causes lbs_cfg_del_key() only called at disconnect time,
	 * where we'd just waste time deleting a key that is not going
	 * to be used anyway.
	 */
	if (key_index < 3 && priv->wep_key_len[key_index]) {
		priv->wep_key_len[key_index] = 0;
		lbs_set_wep_keys(priv);
	}
#endif

	return 0;
}