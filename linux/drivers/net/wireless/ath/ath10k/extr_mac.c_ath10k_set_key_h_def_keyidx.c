#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct ieee80211_key_conf {scalar_t__ cipher; int flags; int /*<<< orphan*/  keyidx; } ;
struct ath10k_vif {scalar_t__ vdev_type; int /*<<< orphan*/  vdev_id; TYPE_3__* ar; } ;
struct ath10k {int dummy; } ;
typedef  enum set_key_cmd { ____Placeholder_set_key_cmd } set_key_cmd ;
struct TYPE_5__ {TYPE_1__* vdev_param; } ;
struct TYPE_6__ {TYPE_2__ wmi; } ;
struct TYPE_4__ {int /*<<< orphan*/  def_keyid; } ;

/* Variables and functions */
 int IEEE80211_KEY_FLAG_PAIRWISE ; 
 int SET_KEY ; 
 scalar_t__ WLAN_CIPHER_SUITE_WEP104 ; 
 scalar_t__ WLAN_CIPHER_SUITE_WEP40 ; 
 scalar_t__ WMI_VDEV_TYPE_AP ; 
 scalar_t__ WMI_VDEV_TYPE_IBSS ; 
 int /*<<< orphan*/  ath10k_warn (struct ath10k*,char*,int /*<<< orphan*/ ,int) ; 
 int ath10k_wmi_vdev_set_param (struct ath10k*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ath10k_set_key_h_def_keyidx(struct ath10k *ar,
					struct ath10k_vif *arvif,
					enum set_key_cmd cmd,
					struct ieee80211_key_conf *key)
{
	u32 vdev_param = arvif->ar->wmi.vdev_param->def_keyid;
	int ret;

	/* 10.1 firmware branch requires default key index to be set to group
	 * key index after installing it. Otherwise FW/HW Txes corrupted
	 * frames with multi-vif APs. This is not required for main firmware
	 * branch (e.g. 636).
	 *
	 * This is also needed for 636 fw for IBSS-RSN to work more reliably.
	 *
	 * FIXME: It remains unknown if this is required for multi-vif STA
	 * interfaces on 10.1.
	 */

	if (arvif->vdev_type != WMI_VDEV_TYPE_AP &&
	    arvif->vdev_type != WMI_VDEV_TYPE_IBSS)
		return;

	if (key->cipher == WLAN_CIPHER_SUITE_WEP40)
		return;

	if (key->cipher == WLAN_CIPHER_SUITE_WEP104)
		return;

	if (key->flags & IEEE80211_KEY_FLAG_PAIRWISE)
		return;

	if (cmd != SET_KEY)
		return;

	ret = ath10k_wmi_vdev_set_param(ar, arvif->vdev_id, vdev_param,
					key->keyidx);
	if (ret)
		ath10k_warn(ar, "failed to set vdev %i group key as default key: %d\n",
			    arvif->vdev_id, ret);
}