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
typedef  int /*<<< orphan*/  u8 ;
struct xmit_priv {int /*<<< orphan*/  frag_len; int /*<<< orphan*/  vcs_type; int /*<<< orphan*/  vcs; int /*<<< orphan*/  vcs_setting; } ;
struct security_priv {int dot118021XGrpKeyid; int /*<<< orphan*/  ndisencryptstatus; int /*<<< orphan*/  ndisauthtype; void* dot118021XGrpPrivacy; scalar_t__ dot11PrivacyKeyIndex; void* dot11PrivacyAlgrthm; int /*<<< orphan*/  dot11AuthAlgrthm; int /*<<< orphan*/  binstallGrpkey; } ;
struct registry_priv {int /*<<< orphan*/  frag_thresh; int /*<<< orphan*/  vcs_type; int /*<<< orphan*/  vrtl_carrier_sense; } ;
struct TYPE_2__ {int ampdu_enable; } ;
struct mlme_priv {TYPE_1__ htpriv; int /*<<< orphan*/  scan_mode; int /*<<< orphan*/  scan_interval; } ;
struct adapter {int bReadPortCancel; int bWritePortCancel; struct security_priv securitypriv; struct mlme_priv mlmepriv; struct xmit_priv xmitpriv; struct registry_priv registrypriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  Ndis802_11AuthModeOpen ; 
 int /*<<< orphan*/  Ndis802_11WEPDisabled ; 
 int /*<<< orphan*/  SCAN_ACTIVE ; 
 int /*<<< orphan*/  SCAN_INTERVAL ; 
 int /*<<< orphan*/  _FAIL ; 
 void* _NO_PRIVACY_ ; 
 int /*<<< orphan*/  _SUCCESS ; 
 int /*<<< orphan*/  dot11AuthAlgrthm_Open ; 
 int /*<<< orphan*/  rtw_hal_def_value_init (struct adapter*) ; 
 int /*<<< orphan*/  rtw_init_registrypriv_dev_network (struct adapter*) ; 
 int /*<<< orphan*/  rtw_update_registrypriv_dev_network (struct adapter*) ; 

__attribute__((used)) static u8 rtw_init_default_value(struct adapter *padapter)
{
	struct registry_priv *pregistrypriv = &padapter->registrypriv;
	struct xmit_priv *pxmitpriv = &padapter->xmitpriv;
	struct mlme_priv *pmlmepriv = &padapter->mlmepriv;
	struct security_priv *psecuritypriv = &padapter->securitypriv;

	/* xmit_priv */
	pxmitpriv->vcs_setting = pregistrypriv->vrtl_carrier_sense;
	pxmitpriv->vcs = pregistrypriv->vcs_type;
	pxmitpriv->vcs_type = pregistrypriv->vcs_type;
	pxmitpriv->frag_len = pregistrypriv->frag_thresh;

	/* mlme_priv */
	pmlmepriv->scan_interval = SCAN_INTERVAL;/*  30*2 sec = 60sec */
	pmlmepriv->scan_mode = SCAN_ACTIVE;

	/* ht_priv */
	pmlmepriv->htpriv.ampdu_enable = false;/* set to disabled */

	/* security_priv */
	psecuritypriv->binstallGrpkey = _FAIL;
	psecuritypriv->dot11AuthAlgrthm = dot11AuthAlgrthm_Open;
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
	padapter->bReadPortCancel = false;
	padapter->bWritePortCancel = false;
	return _SUCCESS;
}