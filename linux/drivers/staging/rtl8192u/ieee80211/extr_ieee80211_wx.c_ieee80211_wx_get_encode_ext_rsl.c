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
struct iw_point {int length; int flags; } ;
union iwreq_data {struct iw_point encoding; } ;
struct iw_request_info {int dummy; } ;
struct iw_encode_ext {int ext_flags; scalar_t__ alg; scalar_t__ key_len; int /*<<< orphan*/  key; } ;
struct ieee80211_device {int tx_keyidx; scalar_t__ iw_mode; struct ieee80211_crypt_data** crypt; } ;
struct ieee80211_crypt_data {int /*<<< orphan*/  priv; TYPE_1__* ops; } ;
struct TYPE_2__ {scalar_t__ (* get_key ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IW_ENCODE_ALG_CCMP ; 
 scalar_t__ IW_ENCODE_ALG_NONE ; 
 scalar_t__ IW_ENCODE_ALG_TKIP ; 
 scalar_t__ IW_ENCODE_ALG_WEP ; 
 int IW_ENCODE_DISABLED ; 
 int IW_ENCODE_ENABLED ; 
 int IW_ENCODE_EXT_GROUP_KEY ; 
 int IW_ENCODE_EXT_TX_SEQ_VALID ; 
 int IW_ENCODE_INDEX ; 
 scalar_t__ IW_MODE_INFRA ; 
 int /*<<< orphan*/  SCM_KEY_LEN ; 
 int WEP_KEYS ; 
 int /*<<< orphan*/  memset (struct iw_encode_ext*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int ieee80211_wx_get_encode_ext(struct ieee80211_device *ieee,
			       struct iw_request_info *info,
			       union iwreq_data *wrqu, char *extra)
{
	struct iw_point *encoding = &wrqu->encoding;
	struct iw_encode_ext *ext = (struct iw_encode_ext *)extra;
	struct ieee80211_crypt_data *crypt;
	int idx, max_key_len;

	max_key_len = encoding->length - sizeof(*ext);
	if (max_key_len < 0)
		return -EINVAL;

	idx = encoding->flags & IW_ENCODE_INDEX;
	if (idx) {
		if (idx < 1 || idx > WEP_KEYS)
			return -EINVAL;
		idx--;
	} else
		idx = ieee->tx_keyidx;

	if (!(ext->ext_flags & IW_ENCODE_EXT_GROUP_KEY) &&
	    ext->alg != IW_ENCODE_ALG_WEP)
		if (idx != 0 || ieee->iw_mode != IW_MODE_INFRA)
			return -EINVAL;

	crypt = ieee->crypt[idx];
	encoding->flags = idx + 1;
	memset(ext, 0, sizeof(*ext));

	if (!crypt || !crypt->ops) {
		ext->alg = IW_ENCODE_ALG_NONE;
		ext->key_len = 0;
		encoding->flags |= IW_ENCODE_DISABLED;
	} else {
		if (strcmp(crypt->ops->name, "WEP") == 0)
			ext->alg = IW_ENCODE_ALG_WEP;
		else if (strcmp(crypt->ops->name, "TKIP"))
			ext->alg = IW_ENCODE_ALG_TKIP;
		else if (strcmp(crypt->ops->name, "CCMP"))
			ext->alg = IW_ENCODE_ALG_CCMP;
		else
			return -EINVAL;
		ext->key_len = crypt->ops->get_key(ext->key, SCM_KEY_LEN, NULL, crypt->priv);
		encoding->flags |= IW_ENCODE_ENABLED;
		if (ext->key_len &&
		    (ext->alg == IW_ENCODE_ALG_TKIP ||
		     ext->alg == IW_ENCODE_ALG_CCMP))
			ext->ext_flags |= IW_ENCODE_EXT_TX_SEQ_VALID;
	}

	return 0;
}