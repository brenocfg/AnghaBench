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
struct xmit_priv {int /*<<< orphan*/  frag_len; int /*<<< orphan*/  rts_thresh; int /*<<< orphan*/  vcs_type; int /*<<< orphan*/  vcs; int /*<<< orphan*/  vcs_setting; } ;
struct security_priv {int /*<<< orphan*/  binstallGrpkey; int /*<<< orphan*/  sw_decrypt; int /*<<< orphan*/  sw_encrypt; } ;
struct registry_priv {int /*<<< orphan*/  software_decrypt; int /*<<< orphan*/  software_encrypt; int /*<<< orphan*/  frag_thresh; int /*<<< orphan*/  rts_thresh; int /*<<< orphan*/  vcs_type; int /*<<< orphan*/  vrtl_carrier_sense; } ;
struct ht_priv {int ampdu_enable; int* baddbareq_issued; } ;
struct mlme_priv {int passive_mode; struct ht_priv htpriv; } ;
struct _adapter {struct security_priv securitypriv; struct mlme_priv mlmepriv; struct xmit_priv xmitpriv; struct registry_priv registrypriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  _FAIL ; 
 int /*<<< orphan*/  r8712_init_registrypriv_dev_network (struct _adapter*) ; 
 int /*<<< orphan*/  r8712_update_registrypriv_dev_network (struct _adapter*) ; 

__attribute__((used)) static void init_default_value(struct _adapter *padapter)
{
	struct registry_priv *pregistrypriv = &padapter->registrypriv;
	struct xmit_priv *pxmitpriv = &padapter->xmitpriv;
	struct mlme_priv *pmlmepriv = &padapter->mlmepriv;
	struct security_priv *psecuritypriv = &padapter->securitypriv;

	/*xmit_priv*/
	pxmitpriv->vcs_setting = pregistrypriv->vrtl_carrier_sense;
	pxmitpriv->vcs = pregistrypriv->vcs_type;
	pxmitpriv->vcs_type = pregistrypriv->vcs_type;
	pxmitpriv->rts_thresh = pregistrypriv->rts_thresh;
	pxmitpriv->frag_len = pregistrypriv->frag_thresh;
	/* mlme_priv */
	/* Maybe someday we should rename this variable to "active_mode"(Jeff)*/
	pmlmepriv->passive_mode = 1; /* 1: active, 0: passive. */
	/*ht_priv*/
	{
		int i;
		struct ht_priv	 *phtpriv = &pmlmepriv->htpriv;

		phtpriv->ampdu_enable = false;/*set to disabled*/
		for (i = 0; i < 16; i++)
			phtpriv->baddbareq_issued[i] = false;
	}
	/*security_priv*/
	psecuritypriv->sw_encrypt = pregistrypriv->software_encrypt;
	psecuritypriv->sw_decrypt = pregistrypriv->software_decrypt;
	psecuritypriv->binstallGrpkey = _FAIL;
	/*pwrctrl_priv*/
	/*registry_priv*/
	r8712_init_registrypriv_dev_network(padapter);
	r8712_update_registrypriv_dev_network(padapter);
	/*misc.*/
}