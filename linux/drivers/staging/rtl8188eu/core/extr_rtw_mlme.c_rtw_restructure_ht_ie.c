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
typedef  int uint ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct qos_priv {int qos_option; } ;
struct ht_priv {int ht_option; } ;
struct mlme_priv {struct ht_priv htpriv; struct qos_priv qospriv; } ;
struct ieee80211_ht_cap {int ampdu_params_info; int /*<<< orphan*/  cap_info; } ;
struct ieee80211_ht_addt_info {int dummy; } ;
struct TYPE_2__ {scalar_t__ dot11PrivacyAlgrthm; } ;
struct adapter {TYPE_1__ securitypriv; struct mlme_priv mlmepriv; } ;
typedef  enum ht_cap_ampdu_factor { ____Placeholder_ht_cap_ampdu_factor } ht_cap_ampdu_factor ;

/* Variables and functions */
 int /*<<< orphan*/  HAL_DEF_MAX_RECVBUF_SZ ; 
 int /*<<< orphan*/  HAL_DEF_RX_PACKET_OFFSET ; 
 int /*<<< orphan*/  HW_VAR_MAX_RX_AMPDU_FACTOR ; 
 int IEEE80211_HT_CAP_AMPDU_DENSITY ; 
 int IEEE80211_HT_CAP_DSSSCCK40 ; 
 int IEEE80211_HT_CAP_SGI_20 ; 
 int IEEE80211_HT_CAP_SGI_40 ; 
 int IEEE80211_HT_CAP_SUP_WIDTH ; 
 int IEEE80211_HT_CAP_TX_STBC ; 
 scalar_t__ _AES_ ; 
 int /*<<< orphan*/  _HT_ADD_INFO_IE_ ; 
 int /*<<< orphan*/  _HT_CAPABILITY_IE_ ; 
 int /*<<< orphan*/  _VENDOR_SPECIFIC_IE_ ; 
 int _WMM_IE_Length_ ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int /*<<< orphan*/  memset (struct ieee80211_ht_cap*,int /*<<< orphan*/ ,int) ; 
 unsigned char* rtw_get_ie (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  rtw_hal_get_def_var (struct adapter*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  rtw_set_ie (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,unsigned char*,int*) ; 

unsigned int rtw_restructure_ht_ie(struct adapter *padapter, u8 *in_ie, u8 *out_ie, uint in_len, uint *pout_len)
{
	u32 ielen, out_len;
	enum ht_cap_ampdu_factor max_rx_ampdu_factor;
	unsigned char *p;
	unsigned char WMM_IE[] = {0x00, 0x50, 0xf2, 0x02, 0x00, 0x01, 0x00};
	struct mlme_priv *pmlmepriv = &padapter->mlmepriv;
	struct qos_priv *pqospriv = &pmlmepriv->qospriv;
	struct ht_priv *phtpriv = &pmlmepriv->htpriv;
	u32 rx_packet_offset, max_recvbuf_sz;

	phtpriv->ht_option = false;

	p = rtw_get_ie(in_ie+12, _HT_CAPABILITY_IE_, &ielen, in_len-12);

	if (p && ielen > 0) {
		struct ieee80211_ht_cap ht_cap;

		if (pqospriv->qos_option == 0) {
			out_len = *pout_len;
			rtw_set_ie(out_ie + out_len, _VENDOR_SPECIFIC_IE_,
				   _WMM_IE_Length_, WMM_IE, pout_len);

			pqospriv->qos_option = 1;
		}

		out_len = *pout_len;

		memset(&ht_cap, 0, sizeof(struct ieee80211_ht_cap));

		ht_cap.cap_info = cpu_to_le16(IEEE80211_HT_CAP_SUP_WIDTH |
					      IEEE80211_HT_CAP_SGI_20 |
					      IEEE80211_HT_CAP_SGI_40 |
					      IEEE80211_HT_CAP_TX_STBC |
					      IEEE80211_HT_CAP_DSSSCCK40);

		rtw_hal_get_def_var(padapter, HAL_DEF_RX_PACKET_OFFSET, &rx_packet_offset);
		rtw_hal_get_def_var(padapter, HAL_DEF_MAX_RECVBUF_SZ, &max_recvbuf_sz);

		/*
		ampdu_params_info [1:0]:Max AMPDU Len => 0:8k , 1:16k, 2:32k, 3:64k
		ampdu_params_info [4:2]:Min MPDU Start Spacing
		*/

		rtw_hal_get_def_var(padapter, HW_VAR_MAX_RX_AMPDU_FACTOR, &max_rx_ampdu_factor);
		ht_cap.ampdu_params_info = max_rx_ampdu_factor & 0x03;

		if (padapter->securitypriv.dot11PrivacyAlgrthm == _AES_)
			ht_cap.ampdu_params_info |= IEEE80211_HT_CAP_AMPDU_DENSITY & (0x07 << 2);
		else
			ht_cap.ampdu_params_info |= IEEE80211_HT_CAP_AMPDU_DENSITY & 0x00;

		rtw_set_ie(out_ie+out_len, _HT_CAPABILITY_IE_,
			   sizeof(struct ieee80211_ht_cap),
			   (unsigned char *)&ht_cap, pout_len);

		phtpriv->ht_option = true;

		p = rtw_get_ie(in_ie+12, _HT_ADD_INFO_IE_, &ielen, in_len-12);
		if (p && (ielen == sizeof(struct ieee80211_ht_addt_info))) {
			out_len = *pout_len;
			rtw_set_ie(out_ie+out_len, _HT_ADD_INFO_IE_, ielen, p+2, pout_len);
		}
	}
	return phtpriv->ht_option;
}