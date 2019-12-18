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
struct zd1201 {int encode_enabled; int encode_restricted; int /*<<< orphan*/ * encode_keys; int /*<<< orphan*/ * encode_keylen; } ;
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;
struct iw_point {int flags; int /*<<< orphan*/  length; } ;

/* Variables and functions */
 int EINVAL ; 
 int IW_ENCODE_DISABLED ; 
 int IW_ENCODE_INDEX ; 
 int IW_ENCODE_MODE ; 
 int IW_ENCODE_RESTRICTED ; 
 short ZD1201_CNFAUTHENTICATION_OPENSYSTEM ; 
 short ZD1201_CNFAUTHENTICATION_SHAREDKEY ; 
 int /*<<< orphan*/  ZD1201_MAXKEYLEN ; 
 short ZD1201_NUMKEYS ; 
 int /*<<< orphan*/  ZD1201_RID_CNFAUTHENTICATION ; 
 short ZD1201_RID_CNFDEFAULTKEY0 ; 
 int /*<<< orphan*/  ZD1201_RID_CNFDEFAULTKEYID ; 
 int /*<<< orphan*/  ZD1201_RID_CNFWEBFLAGS ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct zd1201* netdev_priv (struct net_device*) ; 
 int zd1201_getconfig16 (struct zd1201*,int /*<<< orphan*/ ,short*) ; 
 int zd1201_mac_reset (struct zd1201*) ; 
 int zd1201_setconfig (struct zd1201*,int,char*,int /*<<< orphan*/ ,int) ; 
 int zd1201_setconfig16 (struct zd1201*,int /*<<< orphan*/ ,short) ; 

__attribute__((used)) static int zd1201_set_encode(struct net_device *dev,
    struct iw_request_info *info, struct iw_point *erq, char *key)
{
	struct zd1201 *zd = netdev_priv(dev);
	short i;
	int err, rid;

	if (erq->length > ZD1201_MAXKEYLEN)
		return -EINVAL;

	i = (erq->flags & IW_ENCODE_INDEX)-1;
	if (i == -1) {
		err = zd1201_getconfig16(zd,ZD1201_RID_CNFDEFAULTKEYID,&i);
		if (err)
			return err;
	} else {
		err = zd1201_setconfig16(zd, ZD1201_RID_CNFDEFAULTKEYID, i);
		if (err)
			return err;
	}

	if (i < 0 || i >= ZD1201_NUMKEYS)
		return -EINVAL;

	rid = ZD1201_RID_CNFDEFAULTKEY0 + i;
	err = zd1201_setconfig(zd, rid, key, erq->length, 1);
	if (err)
		return err;
	zd->encode_keylen[i] = erq->length;
	memcpy(zd->encode_keys[i], key, erq->length);

	i=0;
	if (!(erq->flags & IW_ENCODE_DISABLED & IW_ENCODE_MODE)) {
		i |= 0x01;
		zd->encode_enabled = 1;
	} else
		zd->encode_enabled = 0;
	if (erq->flags & IW_ENCODE_RESTRICTED & IW_ENCODE_MODE) {
		i |= 0x02;
		zd->encode_restricted = 1;
	} else
		zd->encode_restricted = 0;
	err = zd1201_setconfig16(zd, ZD1201_RID_CNFWEBFLAGS, i);
	if (err)
		return err;

	if (zd->encode_enabled)
		i = ZD1201_CNFAUTHENTICATION_SHAREDKEY;
	else
		i = ZD1201_CNFAUTHENTICATION_OPENSYSTEM;
	err = zd1201_setconfig16(zd, ZD1201_RID_CNFAUTHENTICATION, i);
	if (err)
		return err;

	return zd1201_mac_reset(zd);
}