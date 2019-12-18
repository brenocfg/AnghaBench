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
typedef  void* u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct security_priv {scalar_t__ dot11AuthAlgrthm; int dot118021XGrpKeyid; void* ndisencryptstatus; void* ndisauthtype; void* dot118021XGrpPrivacy; scalar_t__ dot11PrivacyKeyIndex; void* dot11PrivacyAlgrthm; int /*<<< orphan*/  btkip_countermeasure_time; void* btkip_countermeasure; void* PMKIDIndex; int /*<<< orphan*/ * PMKIDList; } ;
struct mlme_ext_priv {scalar_t__ mgnt_80211w_IPN_rx; } ;
struct adapter {int /*<<< orphan*/  security_key_mutex; struct security_priv securitypriv; struct mlme_ext_priv mlmeextpriv; } ;
typedef  int /*<<< orphan*/  RT_PMKID_LIST ;

/* Variables and functions */
 int NUM_PMKID_CACHE ; 
 void* Ndis802_11AuthModeOpen ; 
 void* Ndis802_11WEPDisabled ; 
 void* _NO_PRIVACY_ ; 
 int /*<<< orphan*/ * backupPMKIDList ; 
 scalar_t__ dot11AuthAlgrthm_8021X ; 
 scalar_t__ dot11AuthAlgrthm_Open ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void rtw_reset_securitypriv(struct adapter *adapter)
{
	u8 backupPMKIDIndex = 0;
	u8 backupTKIPCountermeasure = 0x00;
	u32 backupTKIPcountermeasure_time = 0;
	/*  add for CONFIG_IEEE80211W, none 11w also can use */
	struct mlme_ext_priv *pmlmeext = &adapter->mlmeextpriv;

	spin_lock_bh(&adapter->security_key_mutex);

	if (adapter->securitypriv.dot11AuthAlgrthm == dot11AuthAlgrthm_8021X) {
		/* 802.1x */
		/*  Added by Albert 2009/02/18 */
		/*  We have to backup the PMK information for WiFi PMK Caching test item. */
		/*  */
		/*  Backup the btkip_countermeasure information. */
		/*  When the countermeasure is trigger, the driver have to disconnect with AP for 60 seconds. */

		memcpy(&backupPMKIDList[ 0 ], &adapter->securitypriv.PMKIDList[ 0 ], sizeof(RT_PMKID_LIST) * NUM_PMKID_CACHE);
		backupPMKIDIndex = adapter->securitypriv.PMKIDIndex;
		backupTKIPCountermeasure = adapter->securitypriv.btkip_countermeasure;
		backupTKIPcountermeasure_time = adapter->securitypriv.btkip_countermeasure_time;

		/* reset RX BIP packet number */
		pmlmeext->mgnt_80211w_IPN_rx = 0;

		memset((unsigned char *)&adapter->securitypriv, 0, sizeof(struct security_priv));

		/*  Added by Albert 2009/02/18 */
		/*  Restore the PMK information to securitypriv structure for the following connection. */
		memcpy(&adapter->securitypriv.PMKIDList[ 0 ], &backupPMKIDList[ 0 ], sizeof(RT_PMKID_LIST) * NUM_PMKID_CACHE);
		adapter->securitypriv.PMKIDIndex = backupPMKIDIndex;
		adapter->securitypriv.btkip_countermeasure = backupTKIPCountermeasure;
		adapter->securitypriv.btkip_countermeasure_time = backupTKIPcountermeasure_time;

		adapter->securitypriv.ndisauthtype = Ndis802_11AuthModeOpen;
		adapter->securitypriv.ndisencryptstatus = Ndis802_11WEPDisabled;

	} else {
		/* reset values in securitypriv */
		/* if (adapter->mlmepriv.fw_state & WIFI_STATION_STATE) */
		/*  */
		struct security_priv *psec_priv = &adapter->securitypriv;

		psec_priv->dot11AuthAlgrthm = dot11AuthAlgrthm_Open;  /* open system */
		psec_priv->dot11PrivacyAlgrthm = _NO_PRIVACY_;
		psec_priv->dot11PrivacyKeyIndex = 0;

		psec_priv->dot118021XGrpPrivacy = _NO_PRIVACY_;
		psec_priv->dot118021XGrpKeyid = 1;

		psec_priv->ndisauthtype = Ndis802_11AuthModeOpen;
		psec_priv->ndisencryptstatus = Ndis802_11WEPDisabled;
		/*  */
	}
	/*  add for CONFIG_IEEE80211W, none 11w also can use */
	spin_unlock_bh(&adapter->security_key_mutex);
}