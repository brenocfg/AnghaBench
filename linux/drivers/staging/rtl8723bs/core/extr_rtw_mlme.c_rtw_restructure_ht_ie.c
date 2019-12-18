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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct rtw_ieee80211_ht_cap {int ampdu_params_info; int /*<<< orphan*/  supp_mcs_set; int /*<<< orphan*/  cap_info; } ;
struct registry_priv {int bw_mode; int rx_stbc; int wifi_spec; } ;
struct ht_priv {int ht_option; int /*<<< orphan*/  stbc_cap; scalar_t__ sgi_40m; scalar_t__ sgi_20m; } ;
struct mlme_priv {struct ht_priv htpriv; } ;
struct mlme_ext_priv {scalar_t__ cur_bwmode; int /*<<< orphan*/  default_supported_mcs_set; } ;
struct ieee80211_ht_addt_info {int dummy; } ;
struct TYPE_2__ {scalar_t__ dot11PrivacyAlgrthm; } ;
struct adapter {int driver_rx_ampdu_factor; TYPE_1__ securitypriv; struct mlme_ext_priv mlmeextpriv; struct mlme_priv mlmepriv; struct registry_priv registrypriv; } ;
struct HT_info_element {int* infos; } ;
typedef  enum HT_CAP_AMPDU_FACTOR { ____Placeholder_HT_CAP_AMPDU_FACTOR } HT_CAP_AMPDU_FACTOR ;

/* Variables and functions */
 int BIT (int) ; 
 scalar_t__ CHANNEL_WIDTH_20 ; 
 scalar_t__ CHANNEL_WIDTH_40 ; 
 int /*<<< orphan*/  DBG_871X (char*) ; 
 int /*<<< orphan*/  HAL_DEF_MAX_RECVBUF_SZ ; 
 int /*<<< orphan*/  HAL_DEF_RX_PACKET_OFFSET ; 
 int /*<<< orphan*/  HW_VAR_MAX_RX_AMPDU_FACTOR ; 
 int /*<<< orphan*/  HW_VAR_RF_TYPE ; 
 int IEEE80211_HT_CAP_AMPDU_DENSITY ; 
 int /*<<< orphan*/  IEEE80211_HT_CAP_DSSSCCK40 ; 
 int /*<<< orphan*/  IEEE80211_HT_CAP_RX_STBC_1R ; 
 int /*<<< orphan*/  IEEE80211_HT_CAP_RX_STBC_2R ; 
 int /*<<< orphan*/  IEEE80211_HT_CAP_SGI_20 ; 
 int /*<<< orphan*/  IEEE80211_HT_CAP_SGI_40 ; 
 int /*<<< orphan*/  IEEE80211_HT_CAP_SM_PS ; 
 int /*<<< orphan*/  IEEE80211_HT_CAP_SUP_WIDTH ; 
 int /*<<< orphan*/  IEEE80211_HT_CAP_TX_STBC ; 
 int /*<<< orphan*/  MCS_RATE_1R ; 
 int /*<<< orphan*/  MCS_RATE_2R ; 
 int /*<<< orphan*/  MCS_RATE_2R_13TO15_OFF ; 
#define  RF_1T1R 130 
#define  RF_1T2R 129 
#define  RF_2T2R 128 
 int /*<<< orphan*/  STBC_HT_ENABLE_RX ; 
 int /*<<< orphan*/  STBC_HT_ENABLE_TX ; 
 scalar_t__ TEST_FLAG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WIFI_STATION_STATE ; 
 scalar_t__ _AES_ ; 
 int /*<<< orphan*/  _HT_ADD_INFO_IE_ ; 
 int /*<<< orphan*/  _HT_CAPABILITY_IE_ ; 
 scalar_t__ check_fwstate (struct mlme_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct rtw_ieee80211_ht_cap*,int /*<<< orphan*/ ,int) ; 
 unsigned char* rtw_get_ie (scalar_t__*,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  rtw_hal_get_def_var (struct adapter*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  rtw_hal_get_hwreg (struct adapter*,int /*<<< orphan*/ ,scalar_t__*) ; 
 unsigned char* rtw_set_ie (scalar_t__*,int /*<<< orphan*/ ,int,unsigned char*,int*) ; 
 int /*<<< orphan*/  set_mcs_rate_by_mask (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

unsigned int rtw_restructure_ht_ie(struct adapter *padapter, u8 *in_ie, u8 *out_ie, uint in_len, uint *pout_len, u8 channel)
{
	u32 ielen, out_len;
	enum HT_CAP_AMPDU_FACTOR max_rx_ampdu_factor;
	unsigned char *p, *pframe;
	struct rtw_ieee80211_ht_cap ht_capie;
	u8 cbw40_enable = 0, stbc_rx_enable = 0, rf_type = 0, operation_bw = 0;
	struct registry_priv *pregistrypriv = &padapter->registrypriv;
	struct mlme_priv *pmlmepriv = &padapter->mlmepriv;
	struct ht_priv 	*phtpriv = &pmlmepriv->htpriv;
	struct mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;

	phtpriv->ht_option = false;

	out_len = *pout_len;

	memset(&ht_capie, 0, sizeof(struct rtw_ieee80211_ht_cap));

	ht_capie.cap_info = cpu_to_le16(IEEE80211_HT_CAP_DSSSCCK40);

	if (phtpriv->sgi_20m)
		ht_capie.cap_info |= cpu_to_le16(IEEE80211_HT_CAP_SGI_20);

	/* Get HT BW */
	if (in_ie == NULL) {
		/* TDLS: TODO 20/40 issue */
		if (check_fwstate(pmlmepriv, WIFI_STATION_STATE)) {
			operation_bw = padapter->mlmeextpriv.cur_bwmode;
			if (operation_bw > CHANNEL_WIDTH_40)
				operation_bw = CHANNEL_WIDTH_40;
		} else
			/* TDLS: TODO 40? */
			operation_bw = CHANNEL_WIDTH_40;
	} else {
		p = rtw_get_ie(in_ie, _HT_ADD_INFO_IE_, &ielen, in_len);
		if (p && (ielen == sizeof(struct ieee80211_ht_addt_info))) {
			struct HT_info_element *pht_info = (struct HT_info_element *)(p+2);
			if (pht_info->infos[0] & BIT(2)) {
				switch (pht_info->infos[0] & 0x3) {
				case 1:
				case 3:
					operation_bw = CHANNEL_WIDTH_40;
					break;
				default:
					operation_bw = CHANNEL_WIDTH_20;
					break;
				}
			} else {
				operation_bw = CHANNEL_WIDTH_20;
			}
		}
	}

	/* to disable 40M Hz support while gd_bw_40MHz_en = 0 */
	if (channel > 14) {
		if ((pregistrypriv->bw_mode & 0xf0) > 0)
			cbw40_enable = 1;
	} else {
		if ((pregistrypriv->bw_mode & 0x0f) > 0)
			cbw40_enable = 1;
	}

	if ((cbw40_enable == 1) && (operation_bw == CHANNEL_WIDTH_40)) {
		ht_capie.cap_info |= cpu_to_le16(IEEE80211_HT_CAP_SUP_WIDTH);
		if (phtpriv->sgi_40m)
			ht_capie.cap_info |= cpu_to_le16(IEEE80211_HT_CAP_SGI_40);
	}

	if (TEST_FLAG(phtpriv->stbc_cap, STBC_HT_ENABLE_TX))
		ht_capie.cap_info |= cpu_to_le16(IEEE80211_HT_CAP_TX_STBC);

	/* todo: disable SM power save mode */
	ht_capie.cap_info |= cpu_to_le16(IEEE80211_HT_CAP_SM_PS);

	if (TEST_FLAG(phtpriv->stbc_cap, STBC_HT_ENABLE_RX)) {
		if ((channel <= 14 && pregistrypriv->rx_stbc == 0x1) ||	/* enable for 2.4GHz */
			(pregistrypriv->wifi_spec == 1)) {
			stbc_rx_enable = 1;
			DBG_871X("declare supporting RX STBC\n");
		}
	}

	/* fill default supported_mcs_set */
	memcpy(ht_capie.supp_mcs_set, pmlmeext->default_supported_mcs_set, 16);

	/* update default supported_mcs_set */
	rtw_hal_get_hwreg(padapter, HW_VAR_RF_TYPE, (u8 *)(&rf_type));

	switch (rf_type) {
	case RF_1T1R:
		if (stbc_rx_enable)
			ht_capie.cap_info |= cpu_to_le16(IEEE80211_HT_CAP_RX_STBC_1R);/* RX STBC One spatial stream */

		set_mcs_rate_by_mask(ht_capie.supp_mcs_set, MCS_RATE_1R);
		break;

	case RF_2T2R:
	case RF_1T2R:
	default:
		if (stbc_rx_enable)
			ht_capie.cap_info |= cpu_to_le16(IEEE80211_HT_CAP_RX_STBC_2R);/* RX STBC two spatial stream */

		#ifdef CONFIG_DISABLE_MCS13TO15
		if (((cbw40_enable == 1) && (operation_bw == CHANNEL_WIDTH_40)) && (pregistrypriv->wifi_spec != 1))
				set_mcs_rate_by_mask(ht_capie.supp_mcs_set, MCS_RATE_2R_13TO15_OFF);
		else
				set_mcs_rate_by_mask(ht_capie.supp_mcs_set, MCS_RATE_2R);
		#else /* CONFIG_DISABLE_MCS13TO15 */
			set_mcs_rate_by_mask(ht_capie.supp_mcs_set, MCS_RATE_2R);
		#endif /* CONFIG_DISABLE_MCS13TO15 */
		break;
	}

	{
		u32 rx_packet_offset, max_recvbuf_sz;
		rtw_hal_get_def_var(padapter, HAL_DEF_RX_PACKET_OFFSET, &rx_packet_offset);
		rtw_hal_get_def_var(padapter, HAL_DEF_MAX_RECVBUF_SZ, &max_recvbuf_sz);
	}

	if (padapter->driver_rx_ampdu_factor != 0xFF)
		max_rx_ampdu_factor =
		  (enum HT_CAP_AMPDU_FACTOR)padapter->driver_rx_ampdu_factor;
	else
		rtw_hal_get_def_var(padapter, HW_VAR_MAX_RX_AMPDU_FACTOR,
				    &max_rx_ampdu_factor);

	/* rtw_hal_get_def_var(padapter, HW_VAR_MAX_RX_AMPDU_FACTOR, &max_rx_ampdu_factor); */
	ht_capie.ampdu_params_info = (max_rx_ampdu_factor&0x03);

	if (padapter->securitypriv.dot11PrivacyAlgrthm == _AES_)
		ht_capie.ampdu_params_info |= (IEEE80211_HT_CAP_AMPDU_DENSITY&(0x07<<2));
	else
		ht_capie.ampdu_params_info |= (IEEE80211_HT_CAP_AMPDU_DENSITY&0x00);

	pframe = rtw_set_ie(out_ie+out_len, _HT_CAPABILITY_IE_,
						sizeof(struct rtw_ieee80211_ht_cap), (unsigned char *)&ht_capie, pout_len);

	phtpriv->ht_option = true;

	if (in_ie != NULL) {
		p = rtw_get_ie(in_ie, _HT_ADD_INFO_IE_, &ielen, in_len);
		if (p && (ielen == sizeof(struct ieee80211_ht_addt_info))) {
			out_len = *pout_len;
			pframe = rtw_set_ie(out_ie+out_len, _HT_ADD_INFO_IE_, ielen, p+2, pout_len);
		}
	}

	return phtpriv->ht_option;

}