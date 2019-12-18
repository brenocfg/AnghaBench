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
struct xmit_priv {int /*<<< orphan*/  frag_len; int /*<<< orphan*/  vcs_type; int /*<<< orphan*/  vcs; int /*<<< orphan*/  vcs_setting; } ;
struct security_priv {int dot118021XGrpKeyid; int /*<<< orphan*/  ndisencryptstatus; int /*<<< orphan*/  ndisauthtype; void* dot118021XGrpPrivacy; scalar_t__ dot11PrivacyKeyIndex; void* dot11PrivacyAlgrthm; int /*<<< orphan*/  dot11AuthAlgrthm; int /*<<< orphan*/  sw_decrypt; int /*<<< orphan*/  sw_encrypt; void* binstallKCK_KEK; void* binstallGrpkey; } ;
struct registry_priv {int /*<<< orphan*/  software_decrypt; int /*<<< orphan*/  software_encrypt; int /*<<< orphan*/  frag_thresh; int /*<<< orphan*/  vcs_type; int /*<<< orphan*/  vrtl_carrier_sense; } ;
struct TYPE_2__ {int ampdu_enable; } ;
struct mlme_priv {TYPE_1__ htpriv; int /*<<< orphan*/  scan_mode; } ;
struct adapter {int fix_rate; int driver_ampdu_spacing; int driver_rx_ampdu_factor; scalar_t__ bNotifyChannelChange; scalar_t__ bLinkInfoDump; struct security_priv securitypriv; struct mlme_priv mlmepriv; struct xmit_priv xmitpriv; struct registry_priv registrypriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  DF_RX_BIT ; 
 int /*<<< orphan*/  DF_TX_BIT ; 
 int /*<<< orphan*/  Ndis802_11AuthModeOpen ; 
 int /*<<< orphan*/  Ndis802_11WEPDisabled ; 
 int /*<<< orphan*/  RTW_ENABLE_FUNC (struct adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCAN_ACTIVE ; 
 void* _FAIL ; 
 void* _NO_PRIVACY_ ; 
 int /*<<< orphan*/  dot11AuthAlgrthm_Open ; 
 int /*<<< orphan*/  rtw_hal_def_value_init (struct adapter*) ; 
 int /*<<< orphan*/  rtw_init_registrypriv_dev_network (struct adapter*) ; 
 int /*<<< orphan*/  rtw_update_registrypriv_dev_network (struct adapter*) ; 

__attribute__((used)) static void rtw_init_default_value(struct adapter *padapter)
{
	struct registry_priv *pregistrypriv = &padapter->registrypriv;
	struct xmit_priv *pxmitpriv = &padapter->xmitpriv;
	struct mlme_priv *pmlmepriv = &padapter->mlmepriv;
	struct security_priv *psecuritypriv = &padapter->securitypriv;

	/* xmit_priv */
	pxmitpriv->vcs_setting = pregistrypriv->vrtl_carrier_sense;
	pxmitpriv->vcs = pregistrypriv->vcs_type;
	pxmitpriv->vcs_type = pregistrypriv->vcs_type;
	/* pxmitpriv->rts_thresh = pregistrypriv->rts_thresh; */
	pxmitpriv->frag_len = pregistrypriv->frag_thresh;

	/* recv_priv */

	/* mlme_priv */
	pmlmepriv->scan_mode = SCAN_ACTIVE;

	/* qos_priv */
	/* pmlmepriv->qospriv.qos_option = pregistrypriv->wmm_enable; */

	/* ht_priv */
	pmlmepriv->htpriv.ampdu_enable = false;/* set to disabled */

	/* security_priv */
	/* rtw_get_encrypt_decrypt_from_registrypriv(padapter); */
	psecuritypriv->binstallGrpkey = _FAIL;
#ifdef CONFIG_GTK_OL
	psecuritypriv->binstallKCK_KEK = _FAIL;
#endif /* CONFIG_GTK_OL */
	psecuritypriv->sw_encrypt = pregistrypriv->software_encrypt;
	psecuritypriv->sw_decrypt = pregistrypriv->software_decrypt;

	psecuritypriv->dot11AuthAlgrthm = dot11AuthAlgrthm_Open; /* open system */
	psecuritypriv->dot11PrivacyAlgrthm = _NO_PRIVACY_;

	psecuritypriv->dot11PrivacyKeyIndex = 0;

	psecuritypriv->dot118021XGrpPrivacy = _NO_PRIVACY_;
	psecuritypriv->dot118021XGrpKeyid = 1;

	psecuritypriv->ndisauthtype = Ndis802_11AuthModeOpen;
	psecuritypriv->ndisencryptstatus = Ndis802_11WEPDisabled;

	/* registry_priv */
	rtw_init_registrypriv_dev_network(padapter);
	rtw_update_registrypriv_dev_network(padapter);

	/* hal_priv */
	rtw_hal_def_value_init(padapter);

	/* misc. */
	RTW_ENABLE_FUNC(padapter, DF_RX_BIT);
	RTW_ENABLE_FUNC(padapter, DF_TX_BIT);
	padapter->bLinkInfoDump = 0;
	padapter->bNotifyChannelChange = 0;

	/* for debug purpose */
	padapter->fix_rate = 0xFF;
	padapter->driver_ampdu_spacing = 0xFF;
	padapter->driver_rx_ampdu_factor =  0xFF;

}