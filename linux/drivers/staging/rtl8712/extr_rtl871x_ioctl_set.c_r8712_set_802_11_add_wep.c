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
struct security_priv {size_t PrivacyKeyIndex; int /*<<< orphan*/ * DefKeylen; TYPE_1__* DefKey; int /*<<< orphan*/  PrivacyAlgrthm; } ;
struct _adapter {struct security_priv securitypriv; } ;
struct NDIS_802_11_WEP {int KeyIndex; int /*<<< orphan*/  KeyLength; int /*<<< orphan*/  KeyMaterial; } ;
typedef  size_t sint ;
struct TYPE_2__ {int /*<<< orphan*/  skey; } ;

/* Variables and functions */
 int EINVAL ; 
 size_t WEP_KEYS ; 
 int /*<<< orphan*/  _NO_PRIVACY_ ; 
 int /*<<< orphan*/  _WEP104_ ; 
 int /*<<< orphan*/  _WEP40_ ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int r8712_set_key (struct _adapter*,struct security_priv*,size_t) ; 

int r8712_set_802_11_add_wep(struct _adapter *padapter,
			     struct NDIS_802_11_WEP *wep)
{
	sint	keyid;
	struct security_priv *psecuritypriv = &padapter->securitypriv;

	keyid = wep->KeyIndex & 0x3fffffff;
	if (keyid >= WEP_KEYS)
		return -EINVAL;
	switch (wep->KeyLength) {
	case 5:
		psecuritypriv->PrivacyAlgrthm = _WEP40_;
		break;
	case 13:
		psecuritypriv->PrivacyAlgrthm = _WEP104_;
		break;
	default:
		psecuritypriv->PrivacyAlgrthm = _NO_PRIVACY_;
		break;
	}
	memcpy(psecuritypriv->DefKey[keyid].skey, &wep->KeyMaterial,
		wep->KeyLength);
	psecuritypriv->DefKeylen[keyid] = wep->KeyLength;
	psecuritypriv->PrivacyKeyIndex = keyid;
	return r8712_set_key(padapter, psecuritypriv, keyid);
}