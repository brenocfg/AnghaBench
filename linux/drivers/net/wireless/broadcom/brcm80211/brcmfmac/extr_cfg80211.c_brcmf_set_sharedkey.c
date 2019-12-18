#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  void* u32 ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int* ciphers_pairwise; } ;
struct cfg80211_connect_params {scalar_t__ key_len; TYPE_1__ crypto; int /*<<< orphan*/  key; scalar_t__ key_idx; } ;
struct brcmf_wsec_key {int len; int /*<<< orphan*/  data; int /*<<< orphan*/  algo; void* index; int /*<<< orphan*/  flags; } ;
struct brcmf_pub {int dummy; } ;
struct brcmf_if {struct brcmf_pub* drvr; } ;
struct brcmf_cfg80211_security {int wpa_versions; int cipher_pairwise; scalar_t__ auth_type; } ;
struct brcmf_cfg80211_profile {struct brcmf_cfg80211_security sec; } ;
typedef  int s32 ;
typedef  int /*<<< orphan*/  key ;

/* Variables and functions */
 int /*<<< orphan*/  BRCMF_PRIMARY_KEY ; 
 int /*<<< orphan*/  CONN ; 
 int /*<<< orphan*/  CRYPTO_ALGO_WEP1 ; 
 int /*<<< orphan*/  CRYPTO_ALGO_WEP128 ; 
 int EINVAL ; 
 scalar_t__ NL80211_AUTHTYPE_SHARED_KEY ; 
 int NL80211_WPA_VERSION_1 ; 
 int NL80211_WPA_VERSION_2 ; 
#define  WLAN_CIPHER_SUITE_WEP104 129 
#define  WLAN_CIPHER_SUITE_WEP40 128 
 int WL_AUTH_SHARED_KEY ; 
 int /*<<< orphan*/  bphy_err (struct brcmf_pub*,char*,int) ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int brcmf_fil_bsscfg_int_set (struct brcmf_if*,char*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct brcmf_wsec_key*,int /*<<< orphan*/ ,int) ; 
 struct brcmf_cfg80211_profile* ndev_to_prof (struct net_device*) ; 
 struct brcmf_if* netdev_priv (struct net_device*) ; 
 int send_key_to_dongle (struct brcmf_if*,struct brcmf_wsec_key*) ; 

__attribute__((used)) static s32
brcmf_set_sharedkey(struct net_device *ndev,
		    struct cfg80211_connect_params *sme)
{
	struct brcmf_if *ifp = netdev_priv(ndev);
	struct brcmf_pub *drvr = ifp->drvr;
	struct brcmf_cfg80211_profile *profile = ndev_to_prof(ndev);
	struct brcmf_cfg80211_security *sec;
	struct brcmf_wsec_key key;
	s32 val;
	s32 err = 0;

	brcmf_dbg(CONN, "key len (%d)\n", sme->key_len);

	if (sme->key_len == 0)
		return 0;

	sec = &profile->sec;
	brcmf_dbg(CONN, "wpa_versions 0x%x cipher_pairwise 0x%x\n",
		  sec->wpa_versions, sec->cipher_pairwise);

	if (sec->wpa_versions & (NL80211_WPA_VERSION_1 | NL80211_WPA_VERSION_2))
		return 0;

	if (!(sec->cipher_pairwise &
	    (WLAN_CIPHER_SUITE_WEP40 | WLAN_CIPHER_SUITE_WEP104)))
		return 0;

	memset(&key, 0, sizeof(key));
	key.len = (u32) sme->key_len;
	key.index = (u32) sme->key_idx;
	if (key.len > sizeof(key.data)) {
		bphy_err(drvr, "Too long key length (%u)\n", key.len);
		return -EINVAL;
	}
	memcpy(key.data, sme->key, key.len);
	key.flags = BRCMF_PRIMARY_KEY;
	switch (sec->cipher_pairwise) {
	case WLAN_CIPHER_SUITE_WEP40:
		key.algo = CRYPTO_ALGO_WEP1;
		break;
	case WLAN_CIPHER_SUITE_WEP104:
		key.algo = CRYPTO_ALGO_WEP128;
		break;
	default:
		bphy_err(drvr, "Invalid algorithm (%d)\n",
			 sme->crypto.ciphers_pairwise[0]);
		return -EINVAL;
	}
	/* Set the new key/index */
	brcmf_dbg(CONN, "key length (%d) key index (%d) algo (%d)\n",
		  key.len, key.index, key.algo);
	brcmf_dbg(CONN, "key \"%s\"\n", key.data);
	err = send_key_to_dongle(ifp, &key);
	if (err)
		return err;

	if (sec->auth_type == NL80211_AUTHTYPE_SHARED_KEY) {
		brcmf_dbg(CONN, "set auth_type to shared key\n");
		val = WL_AUTH_SHARED_KEY;	/* shared key */
		err = brcmf_fil_bsscfg_int_set(ifp, "auth", val);
		if (err)
			bphy_err(drvr, "set auth failed (%d)\n", err);
	}
	return err;
}