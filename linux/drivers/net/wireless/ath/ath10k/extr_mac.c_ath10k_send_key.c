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
typedef  int /*<<< orphan*/  u32 ;
struct wmi_vdev_install_key_arg {int key_txmic_len; int key_rxmic_len; int /*<<< orphan*/ * key_data; int /*<<< orphan*/  key_cipher; int /*<<< orphan*/  const* macaddr; int /*<<< orphan*/  key_flags; int /*<<< orphan*/  key_len; int /*<<< orphan*/  key_idx; int /*<<< orphan*/  vdev_id; } ;
struct ieee80211_key_conf {int cipher; int /*<<< orphan*/  flags; int /*<<< orphan*/ * key; int /*<<< orphan*/  keylen; int /*<<< orphan*/  keyidx; } ;
struct ath10k_vif {struct ath10k* ar; int /*<<< orphan*/  vdev_id; } ;
struct ath10k {int /*<<< orphan*/ * wmi_key_cipher; int /*<<< orphan*/  dev_flags; int /*<<< orphan*/  conf_mutex; } ;
typedef  enum set_key_cmd { ____Placeholder_set_key_cmd } set_key_cmd ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_FLAG_RAW_MODE ; 
 int DISABLE_KEY ; 
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  IEEE80211_KEY_FLAG_GENERATE_IV ; 
 int /*<<< orphan*/  IEEE80211_KEY_FLAG_GENERATE_IV_MGMT ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
#define  WLAN_CIPHER_SUITE_AES_CMAC 138 
#define  WLAN_CIPHER_SUITE_BIP_CMAC_256 137 
#define  WLAN_CIPHER_SUITE_BIP_GMAC_128 136 
#define  WLAN_CIPHER_SUITE_BIP_GMAC_256 135 
#define  WLAN_CIPHER_SUITE_CCMP 134 
#define  WLAN_CIPHER_SUITE_CCMP_256 133 
#define  WLAN_CIPHER_SUITE_GCMP 132 
#define  WLAN_CIPHER_SUITE_GCMP_256 131 
#define  WLAN_CIPHER_SUITE_TKIP 130 
#define  WLAN_CIPHER_SUITE_WEP104 129 
#define  WLAN_CIPHER_SUITE_WEP40 128 
 size_t WMI_CIPHER_AES_CCM ; 
 size_t WMI_CIPHER_AES_GCM ; 
 size_t WMI_CIPHER_NONE ; 
 size_t WMI_CIPHER_TKIP ; 
 size_t WMI_CIPHER_WEP ; 
 int /*<<< orphan*/  ath10k_warn (struct ath10k*,char*,int) ; 
 int ath10k_wmi_vdev_install_key (struct ath10k*,struct wmi_vdev_install_key_arg*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ath10k_send_key(struct ath10k_vif *arvif,
			   struct ieee80211_key_conf *key,
			   enum set_key_cmd cmd,
			   const u8 *macaddr, u32 flags)
{
	struct ath10k *ar = arvif->ar;
	struct wmi_vdev_install_key_arg arg = {
		.vdev_id = arvif->vdev_id,
		.key_idx = key->keyidx,
		.key_len = key->keylen,
		.key_data = key->key,
		.key_flags = flags,
		.macaddr = macaddr,
	};

	lockdep_assert_held(&arvif->ar->conf_mutex);

	switch (key->cipher) {
	case WLAN_CIPHER_SUITE_CCMP:
		arg.key_cipher = ar->wmi_key_cipher[WMI_CIPHER_AES_CCM];
		key->flags |= IEEE80211_KEY_FLAG_GENERATE_IV_MGMT;
		break;
	case WLAN_CIPHER_SUITE_TKIP:
		arg.key_cipher = ar->wmi_key_cipher[WMI_CIPHER_TKIP];
		arg.key_txmic_len = 8;
		arg.key_rxmic_len = 8;
		break;
	case WLAN_CIPHER_SUITE_WEP40:
	case WLAN_CIPHER_SUITE_WEP104:
		arg.key_cipher = ar->wmi_key_cipher[WMI_CIPHER_WEP];
		break;
	case WLAN_CIPHER_SUITE_CCMP_256:
		arg.key_cipher = ar->wmi_key_cipher[WMI_CIPHER_AES_CCM];
		break;
	case WLAN_CIPHER_SUITE_GCMP:
	case WLAN_CIPHER_SUITE_GCMP_256:
		arg.key_cipher = ar->wmi_key_cipher[WMI_CIPHER_AES_GCM];
		break;
	case WLAN_CIPHER_SUITE_BIP_GMAC_128:
	case WLAN_CIPHER_SUITE_BIP_GMAC_256:
	case WLAN_CIPHER_SUITE_BIP_CMAC_256:
	case WLAN_CIPHER_SUITE_AES_CMAC:
		WARN_ON(1);
		return -EINVAL;
	default:
		ath10k_warn(ar, "cipher %d is not supported\n", key->cipher);
		return -EOPNOTSUPP;
	}

	if (test_bit(ATH10K_FLAG_RAW_MODE, &ar->dev_flags))
		key->flags |= IEEE80211_KEY_FLAG_GENERATE_IV;

	if (cmd == DISABLE_KEY) {
		arg.key_cipher = ar->wmi_key_cipher[WMI_CIPHER_NONE];
		arg.key_data = NULL;
	}

	return ath10k_wmi_vdev_install_key(arvif->ar, &arg);
}