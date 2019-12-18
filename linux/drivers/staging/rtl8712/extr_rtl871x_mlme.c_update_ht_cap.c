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
typedef  scalar_t__ uint ;
typedef  int u8 ;
struct TYPE_2__ {int /*<<< orphan*/  MacAddress; } ;
struct wlan_network {TYPE_1__ network; } ;
struct sta_info {struct recv_reorder_ctrl* recvreorder_ctrl; } ;
struct registry_priv {int ampdu_enable; } ;
struct recv_reorder_ctrl {int indicate_seq; int wend_b; } ;
struct ht_priv {int ampdu_enable; int rx_ampdu_maxlen; int /*<<< orphan*/  ht_option; } ;
struct mlme_priv {struct wlan_network cur_network; struct ht_priv htpriv; } ;
struct ieee80211_ht_cap {int ampdu_params_info; } ;
struct _adapter {int /*<<< orphan*/  stapriv; struct registry_priv registrypriv; struct mlme_priv mlmepriv; } ;
struct NDIS_802_11_FIXED_IEs {int dummy; } ;

/* Variables and functions */
 int IEEE80211_HT_CAP_AMPDU_FACTOR ; 
 int /*<<< orphan*/  _HT_ADD_INFO_IE_ ; 
 int /*<<< orphan*/  _HT_CAPABILITY_IE_ ; 
 struct sta_info* r8712_get_bcmc_stainfo (struct _adapter*) ; 
 int* r8712_get_ie (int*,int /*<<< orphan*/ ,scalar_t__*,scalar_t__) ; 
 struct sta_info* r8712_get_stainfo (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void update_ht_cap(struct _adapter *padapter, u8 *pie, uint ie_len)
{
	u8 *p, max_ampdu_sz;
	int i;
	uint len;
	struct sta_info *bmc_sta, *psta;
	struct ieee80211_ht_cap *pht_capie;
	struct recv_reorder_ctrl *preorder_ctrl;
	struct mlme_priv *pmlmepriv = &padapter->mlmepriv;
	struct ht_priv *phtpriv = &pmlmepriv->htpriv;
	struct registry_priv *pregistrypriv = &padapter->registrypriv;
	struct wlan_network *pcur_network = &(pmlmepriv->cur_network);

	if (!phtpriv->ht_option)
		return;
	/* maybe needs check if ap supports rx ampdu. */
	if (!phtpriv->ampdu_enable &&
	    (pregistrypriv->ampdu_enable == 1))
		phtpriv->ampdu_enable = true;
	/*check Max Rx A-MPDU Size*/
	len = 0;
	p = r8712_get_ie(pie + sizeof(struct NDIS_802_11_FIXED_IEs),
				_HT_CAPABILITY_IE_,
				&len, ie_len -
				sizeof(struct NDIS_802_11_FIXED_IEs));
	if (p && len > 0) {
		pht_capie = (struct ieee80211_ht_cap *)(p + 2);
		max_ampdu_sz = (pht_capie->ampdu_params_info &
				IEEE80211_HT_CAP_AMPDU_FACTOR);
		/* max_ampdu_sz (kbytes); */
		max_ampdu_sz = 1 << (max_ampdu_sz + 3);
		phtpriv->rx_ampdu_maxlen = max_ampdu_sz;
	}
	/* for A-MPDU Rx reordering buffer control for bmc_sta & sta_info
	 * if A-MPDU Rx is enabled, resetting rx_ordering_ctrl
	 * wstart_b(indicate_seq) to default value=0xffff
	 * todo: check if AP can send A-MPDU packets
	 */
	bmc_sta = r8712_get_bcmc_stainfo(padapter);
	if (bmc_sta) {
		for (i = 0; i < 16; i++) {
			preorder_ctrl = &bmc_sta->recvreorder_ctrl[i];
			preorder_ctrl->indicate_seq = 0xffff;
			preorder_ctrl->wend_b = 0xffff;
		}
	}
	psta = r8712_get_stainfo(&padapter->stapriv,
				 pcur_network->network.MacAddress);
	if (psta) {
		for (i = 0; i < 16; i++) {
			preorder_ctrl = &psta->recvreorder_ctrl[i];
			preorder_ctrl->indicate_seq = 0xffff;
			preorder_ctrl->wend_b = 0xffff;
		}
	}
	len = 0;
	p = r8712_get_ie(pie + sizeof(struct NDIS_802_11_FIXED_IEs),
		   _HT_ADD_INFO_IE_, &len,
		   ie_len - sizeof(struct NDIS_802_11_FIXED_IEs));
}