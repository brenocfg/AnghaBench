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
struct wiphy {int dummy; } ;
struct security_priv {int /*<<< orphan*/  ndisauthtype; int /*<<< orphan*/  dot11AuthAlgrthm; void* dot118021XGrpPrivacy; void* dot11PrivacyAlgrthm; int /*<<< orphan*/  ndisencryptstatus; } ;
struct net_device {int dummy; } ;
struct ndis_802_11_ssid {int /*<<< orphan*/  Ssid; int /*<<< orphan*/  SsidLength; } ;
struct mlme_priv {int dummy; } ;
struct cfg80211_ibss_params {int /*<<< orphan*/  ssid_len; scalar_t__ ssid; } ;
struct adapter {struct mlme_priv mlmepriv; struct security_priv securitypriv; } ;

/* Variables and functions */
 int E2BIG ; 
 int EINVAL ; 
 int EPERM ; 
 int /*<<< orphan*/  IW_ESSID_MAX_SIZE ; 
 int /*<<< orphan*/  NL80211_AUTHTYPE_OPEN_SYSTEM ; 
 int /*<<< orphan*/  Ndis802_11AuthModeOpen ; 
 int /*<<< orphan*/  Ndis802_11EncryptionDisabled ; 
 int /*<<< orphan*/  WIFI_AP_STATE ; 
 scalar_t__ _FAIL ; 
 void* _NO_PRIVACY_ ; 
 scalar_t__ check_fwstate (struct mlme_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dot11AuthAlgrthm_Open ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct ndis_802_11_ssid*,int /*<<< orphan*/ ,int) ; 
 int rtw_cfg80211_set_auth_type (struct security_priv*,int /*<<< orphan*/ ) ; 
 scalar_t__ rtw_netdev_priv (struct net_device*) ; 
 scalar_t__ rtw_pwr_wakeup (struct adapter*) ; 
 int /*<<< orphan*/  rtw_set_802_11_authentication_mode (struct adapter*,int /*<<< orphan*/ ) ; 
 int rtw_set_802_11_ssid (struct adapter*,struct ndis_802_11_ssid*) ; 

__attribute__((used)) static int cfg80211_rtw_join_ibss(struct wiphy *wiphy, struct net_device *ndev,
				  struct cfg80211_ibss_params *params)
{
	struct adapter *padapter = (struct adapter *)rtw_netdev_priv(ndev);
	struct ndis_802_11_ssid ndis_ssid;
	struct security_priv *psecuritypriv = &padapter->securitypriv;
	struct mlme_priv *pmlmepriv = &padapter->mlmepriv;
	int ret = 0;

	if (_FAIL == rtw_pwr_wakeup(padapter)) {
		ret = -EPERM;
		goto exit;
	}

	if (check_fwstate(pmlmepriv, WIFI_AP_STATE)) {
		ret = -EPERM;
		goto exit;
	}

	if (!params->ssid || !params->ssid_len)
	{
		ret = -EINVAL;
		goto exit;
	}

	if (params->ssid_len > IW_ESSID_MAX_SIZE) {

		ret = -E2BIG;
		goto exit;
	}

	memset(&ndis_ssid, 0, sizeof(struct ndis_802_11_ssid));
	ndis_ssid.SsidLength = params->ssid_len;
	memcpy(ndis_ssid.Ssid, (u8 *)params->ssid, params->ssid_len);

	/* DBG_8192C("ssid =%s, len =%zu\n", ndis_ssid.Ssid, params->ssid_len); */

	psecuritypriv->ndisencryptstatus = Ndis802_11EncryptionDisabled;
	psecuritypriv->dot11PrivacyAlgrthm = _NO_PRIVACY_;
	psecuritypriv->dot118021XGrpPrivacy = _NO_PRIVACY_;
	psecuritypriv->dot11AuthAlgrthm = dot11AuthAlgrthm_Open; /* open system */
	psecuritypriv->ndisauthtype = Ndis802_11AuthModeOpen;

	ret = rtw_cfg80211_set_auth_type(psecuritypriv, NL80211_AUTHTYPE_OPEN_SYSTEM);
	rtw_set_802_11_authentication_mode(padapter, psecuritypriv->ndisauthtype);

	if (rtw_set_802_11_ssid(padapter, &ndis_ssid) == false)
	{
		ret = -1;
		goto exit;
	}

exit:
	return ret;
}