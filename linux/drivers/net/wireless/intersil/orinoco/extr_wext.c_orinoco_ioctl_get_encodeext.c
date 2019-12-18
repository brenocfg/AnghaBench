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
struct orinoco_private {int tx_key; int encode_alg; TYPE_1__* keys; } ;
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;
struct iw_encode_ext {void* key_len; int /*<<< orphan*/  key; int /*<<< orphan*/  alg; } ;
struct TYPE_2__ {int /*<<< orphan*/  key; int /*<<< orphan*/  key_len; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  IW_ENCODE_ALG_NONE ; 
 int /*<<< orphan*/  IW_ENCODE_ALG_TKIP ; 
 int /*<<< orphan*/  IW_ENCODE_ALG_WEP ; 
 int IW_ENCODE_DISABLED ; 
 int IW_ENCODE_ENABLED ; 
 int IW_ENCODE_INDEX ; 
#define  ORINOCO_ALG_NONE 130 
#define  ORINOCO_ALG_TKIP 129 
#define  ORINOCO_ALG_WEP 128 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  memset (struct iw_encode_ext*,int /*<<< orphan*/ ,int) ; 
 void* min (int /*<<< orphan*/ ,int) ; 
 struct orinoco_private* ndev_priv (struct net_device*) ; 
 scalar_t__ orinoco_lock (struct orinoco_private*,unsigned long*) ; 
 int /*<<< orphan*/  orinoco_unlock (struct orinoco_private*,unsigned long*) ; 

__attribute__((used)) static int orinoco_ioctl_get_encodeext(struct net_device *dev,
				       struct iw_request_info *info,
				       union iwreq_data *wrqu,
				       char *extra)
{
	struct orinoco_private *priv = ndev_priv(dev);
	struct iw_point *encoding = &wrqu->encoding;
	struct iw_encode_ext *ext = (struct iw_encode_ext *)extra;
	int idx, max_key_len;
	unsigned long flags;
	int err;

	if (orinoco_lock(priv, &flags) != 0)
		return -EBUSY;

	err = -EINVAL;
	max_key_len = encoding->length - sizeof(*ext);
	if (max_key_len < 0)
		goto out;

	idx = encoding->flags & IW_ENCODE_INDEX;
	if (idx) {
		if ((idx < 1) || (idx > 4))
			goto out;
		idx--;
	} else
		idx = priv->tx_key;

	encoding->flags = idx + 1;
	memset(ext, 0, sizeof(*ext));

	switch (priv->encode_alg) {
	case ORINOCO_ALG_NONE:
		ext->alg = IW_ENCODE_ALG_NONE;
		ext->key_len = 0;
		encoding->flags |= IW_ENCODE_DISABLED;
		break;
	case ORINOCO_ALG_WEP:
		ext->alg = IW_ENCODE_ALG_WEP;
		ext->key_len = min(priv->keys[idx].key_len, max_key_len);
		memcpy(ext->key, priv->keys[idx].key, ext->key_len);
		encoding->flags |= IW_ENCODE_ENABLED;
		break;
	case ORINOCO_ALG_TKIP:
		ext->alg = IW_ENCODE_ALG_TKIP;
		ext->key_len = min(priv->keys[idx].key_len, max_key_len);
		memcpy(ext->key, priv->keys[idx].key, ext->key_len);
		encoding->flags |= IW_ENCODE_ENABLED;
		break;
	}

	err = 0;
 out:
	orinoco_unlock(priv, &flags);

	return err;
}