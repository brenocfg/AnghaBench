#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
union oid_res_t {int u; struct obj_key* ptr; } ;
struct iw_point {int length; int flags; } ;
union iwreq_data {struct iw_point encoding; } ;
struct obj_key {int length; int type; int /*<<< orphan*/  key; } ;
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;
struct iw_encode_ext {int key_len; int /*<<< orphan*/  alg; int /*<<< orphan*/  key; } ;
struct TYPE_5__ {int wpa; int /*<<< orphan*/  mib_sem; } ;
typedef  TYPE_1__ islpci_private ;

/* Variables and functions */
#define  DOT11_AUTH_BOTH 132 
#define  DOT11_AUTH_OS 131 
#define  DOT11_AUTH_SK 130 
 int /*<<< orphan*/  DOT11_OID_AUTHENABLE ; 
 int /*<<< orphan*/  DOT11_OID_DEFKEYID ; 
 int /*<<< orphan*/  DOT11_OID_DEFKEYX ; 
 int /*<<< orphan*/  DOT11_OID_EXUNENCRYPTED ; 
 int /*<<< orphan*/  DOT11_OID_PRIVACYINVOKED ; 
#define  DOT11_PRIV_TKIP 129 
#define  DOT11_PRIV_WEP 128 
 int E2BIG ; 
 int EINVAL ; 
 int /*<<< orphan*/  IW_ENCODE_ALG_NONE ; 
 int /*<<< orphan*/  IW_ENCODE_ALG_TKIP ; 
 int /*<<< orphan*/  IW_ENCODE_ALG_WEP ; 
 int IW_ENCODE_DISABLED ; 
 int IW_ENCODE_ENABLED ; 
 int IW_ENCODE_INDEX ; 
 int IW_ENCODE_OPEN ; 
 int IW_ENCODE_RESTRICTED ; 
 scalar_t__ PRV_STATE_INIT ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 scalar_t__ islpci_get_state (TYPE_1__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct iw_encode_ext*,int /*<<< orphan*/ ,int) ; 
 int mgt_get_request (TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,union oid_res_t*) ; 
 TYPE_1__* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int prism54_get_encodeext(struct net_device *ndev,
				 struct iw_request_info *info,
				 union iwreq_data *wrqu,
				 char *extra)
{
	islpci_private *priv = netdev_priv(ndev);
	struct iw_point *encoding = &wrqu->encoding;
	struct iw_encode_ext *ext = (struct iw_encode_ext *)extra;
	int idx, max_key_len;
	union oid_res_t r;
	int authen = DOT11_AUTH_OS, invoke = 0, exunencrypt = 0, wpa = 0;
	int ret = 0;

	if (islpci_get_state(priv) < PRV_STATE_INIT)
		return 0;

	/* first get the flags */
	ret = mgt_get_request(priv, DOT11_OID_AUTHENABLE, 0, NULL, &r);
	authen = r.u;
	ret = mgt_get_request(priv, DOT11_OID_PRIVACYINVOKED, 0, NULL, &r);
	invoke = r.u;
	ret = mgt_get_request(priv, DOT11_OID_EXUNENCRYPTED, 0, NULL, &r);
	exunencrypt = r.u;
	if (ret < 0)
		goto out;

	max_key_len = encoding->length - sizeof(*ext);
	if (max_key_len < 0)
		return -EINVAL;

	idx = (encoding->flags & IW_ENCODE_INDEX) - 1;
	if (idx) {
		if (idx < 0 || idx > 3)
			return -EINVAL;
	} else {
		ret = mgt_get_request(priv, DOT11_OID_DEFKEYID, 0, NULL, &r);
		if (ret < 0)
			goto out;
		idx = r.u;
	}

	encoding->flags = idx + 1;
	memset(ext, 0, sizeof(*ext));

	switch (authen) {
	case DOT11_AUTH_BOTH:
	case DOT11_AUTH_SK:
		wrqu->encoding.flags |= IW_ENCODE_RESTRICTED;
		/* fall through */
	case DOT11_AUTH_OS:
	default:
		wrqu->encoding.flags |= IW_ENCODE_OPEN;
		break;
	}

	down_write(&priv->mib_sem);
	wpa = priv->wpa;
	up_write(&priv->mib_sem);

	if (authen == DOT11_AUTH_OS && !exunencrypt && !invoke && !wpa) {
		/* No encryption */
		ext->alg = IW_ENCODE_ALG_NONE;
		ext->key_len = 0;
		wrqu->encoding.flags |= IW_ENCODE_DISABLED;
	} else {
		struct obj_key *key;

		ret = mgt_get_request(priv, DOT11_OID_DEFKEYX, idx, NULL, &r);
		if (ret < 0)
			goto out;
		key = r.ptr;
		if (max_key_len < key->length) {
			ret = -E2BIG;
			goto out;
		}
		memcpy(ext->key, key->key, key->length);
		ext->key_len = key->length;

		switch (key->type) {
		case DOT11_PRIV_TKIP:
			ext->alg = IW_ENCODE_ALG_TKIP;
			break;
		default:
		case DOT11_PRIV_WEP:
			ext->alg = IW_ENCODE_ALG_WEP;
			break;
		}
		wrqu->encoding.flags |= IW_ENCODE_ENABLED;
	}

out:
	return ret;
}