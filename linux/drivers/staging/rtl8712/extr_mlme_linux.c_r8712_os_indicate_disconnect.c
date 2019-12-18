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
struct security_priv {int AuthAlgrthm; int XGrpKeyid; int wps_phase; int /*<<< orphan*/  ndisencryptstatus; int /*<<< orphan*/  ndisauthtype; void* XGrpPrivacy; scalar_t__ PrivacyKeyIndex; void* PrivacyAlgrthm; void* btkip_countermeasure; void* PMKIDIndex; int /*<<< orphan*/ * PMKIDList; int /*<<< orphan*/  tkip_timer; } ;
struct _adapter {struct security_priv securitypriv; int /*<<< orphan*/  pnetdev; } ;
struct RT_PMKID_LIST {int dummy; } ;

/* Variables and functions */
 int NUM_PMKID_CACHE ; 
 int /*<<< orphan*/  Ndis802_11AuthModeOpen ; 
 int /*<<< orphan*/  Ndis802_11WEPDisabled ; 
 void* _NO_PRIVACY_ ; 
 int /*<<< orphan*/ * backupPMKIDList ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netif_carrier_off (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r8712_indicate_wx_disassoc_event (struct _adapter*) ; 
 int /*<<< orphan*/  r8712_use_tkipkey_handler ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void r8712_os_indicate_disconnect(struct _adapter *adapter)
{
	u8 backupPMKIDIndex = 0;
	u8 backupTKIPCountermeasure = 0x00;

	r8712_indicate_wx_disassoc_event(adapter);
	netif_carrier_off(adapter->pnetdev);
	if (adapter->securitypriv.AuthAlgrthm == 2) { /*/802.1x*/
		/* We have to backup the PMK information for WiFi PMK Caching
		 * test item. Backup the btkip_countermeasure information.
		 * When the countermeasure is trigger, the driver have to
		 * disconnect with AP for 60 seconds.
		 */

		memcpy(&backupPMKIDList[0],
		       &adapter->securitypriv.PMKIDList[0],
		       sizeof(struct RT_PMKID_LIST) * NUM_PMKID_CACHE);
		backupPMKIDIndex = adapter->securitypriv.PMKIDIndex;
		backupTKIPCountermeasure =
			adapter->securitypriv.btkip_countermeasure;
		memset((unsigned char *)&adapter->securitypriv, 0,
		       sizeof(struct security_priv));
		timer_setup(&adapter->securitypriv.tkip_timer,
			    r8712_use_tkipkey_handler, 0);
		/* Restore the PMK information to securitypriv structure
		 * for the following connection.
		 */
		memcpy(&adapter->securitypriv.PMKIDList[0],
		       &backupPMKIDList[0],
		       sizeof(struct RT_PMKID_LIST) * NUM_PMKID_CACHE);
		adapter->securitypriv.PMKIDIndex = backupPMKIDIndex;
		adapter->securitypriv.btkip_countermeasure =
					 backupTKIPCountermeasure;
	} else { /*reset values in securitypriv*/
		struct security_priv *sec_priv = &adapter->securitypriv;

		sec_priv->AuthAlgrthm = 0; /*open system*/
		sec_priv->PrivacyAlgrthm = _NO_PRIVACY_;
		sec_priv->PrivacyKeyIndex = 0;
		sec_priv->XGrpPrivacy = _NO_PRIVACY_;
		sec_priv->XGrpKeyid = 1;
		sec_priv->ndisauthtype = Ndis802_11AuthModeOpen;
		sec_priv->ndisencryptstatus = Ndis802_11WEPDisabled;
		sec_priv->wps_phase = false;
	}
}