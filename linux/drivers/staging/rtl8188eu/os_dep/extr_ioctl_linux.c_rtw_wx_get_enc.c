#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct iw_point {int length; int flags; } ;
union iwreq_data {struct iw_point encoding; } ;
typedef  int uint ;
struct net_device {int dummy; } ;
struct mlme_priv {int dummy; } ;
struct iw_request_info {int dummy; } ;
struct TYPE_4__ {int dot11PrivacyKeyIndex; int ndisencryptstatus; int* dot11DefKeylen; int /*<<< orphan*/  ndisauthtype; TYPE_1__* dot11DefKey; } ;
struct adapter {TYPE_2__ securitypriv; struct mlme_priv mlmepriv; } ;
struct TYPE_3__ {int /*<<< orphan*/  skey; } ;

/* Variables and functions */
 int EINVAL ; 
 int IW_ENCODE_DISABLED ; 
 int IW_ENCODE_ENABLED ; 
 int IW_ENCODE_INDEX ; 
 int IW_ENCODE_NOKEY ; 
 int IW_ENCODE_OPEN ; 
 int IW_ENCODE_RESTRICTED ; 
 int /*<<< orphan*/  Ndis802_11AuthModeOpen ; 
 int /*<<< orphan*/  Ndis802_11AuthModeShared ; 
#define  Ndis802_11Encryption1Enabled 132 
#define  Ndis802_11Encryption2Enabled 131 
#define  Ndis802_11Encryption3Enabled 130 
#define  Ndis802_11EncryptionDisabled 129 
#define  Ndis802_11EncryptionNotSupported 128 
 int WEP_KEYS ; 
 int /*<<< orphan*/  WIFI_ADHOC_MASTER_STATE ; 
 int /*<<< orphan*/  _FW_LINKED ; 
 int /*<<< orphan*/  check_fwstate (struct mlme_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ rtw_netdev_priv (struct net_device*) ; 

__attribute__((used)) static int rtw_wx_get_enc(struct net_device *dev,
			    struct iw_request_info *info,
			    union iwreq_data *wrqu, char *keybuf)
{
	uint key;
	struct adapter *padapter = (struct adapter *)rtw_netdev_priv(dev);
	struct iw_point *erq = &(wrqu->encoding);
	struct	mlme_priv	*pmlmepriv = &(padapter->mlmepriv);

	if (!check_fwstate(pmlmepriv, _FW_LINKED)) {
		if (!check_fwstate(pmlmepriv, WIFI_ADHOC_MASTER_STATE)) {
			erq->length = 0;
			erq->flags |= IW_ENCODE_DISABLED;
			return 0;
		}
	}

	key = erq->flags & IW_ENCODE_INDEX;

	if (key) {
		if (key > WEP_KEYS)
			return -EINVAL;
		key--;
	} else {
		key = padapter->securitypriv.dot11PrivacyKeyIndex;
	}

	erq->flags = key + 1;

	switch (padapter->securitypriv.ndisencryptstatus) {
	case Ndis802_11EncryptionNotSupported:
	case Ndis802_11EncryptionDisabled:
		erq->length = 0;
		erq->flags |= IW_ENCODE_DISABLED;
		break;
	case Ndis802_11Encryption1Enabled:
		erq->length = padapter->securitypriv.dot11DefKeylen[key];
		if (erq->length) {
			memcpy(keybuf, padapter->securitypriv.dot11DefKey[key].skey, padapter->securitypriv.dot11DefKeylen[key]);

			erq->flags |= IW_ENCODE_ENABLED;

			if (padapter->securitypriv.ndisauthtype == Ndis802_11AuthModeOpen)
				erq->flags |= IW_ENCODE_OPEN;
			else if (padapter->securitypriv.ndisauthtype == Ndis802_11AuthModeShared)
				erq->flags |= IW_ENCODE_RESTRICTED;
		} else {
			erq->length = 0;
			erq->flags |= IW_ENCODE_DISABLED;
		}
		break;
	case Ndis802_11Encryption2Enabled:
	case Ndis802_11Encryption3Enabled:
		erq->length = 16;
		erq->flags |= (IW_ENCODE_ENABLED | IW_ENCODE_OPEN | IW_ENCODE_NOKEY);
		break;
	default:
		erq->length = 0;
		erq->flags |= IW_ENCODE_DISABLED;
		break;
	}

	return 0;
}