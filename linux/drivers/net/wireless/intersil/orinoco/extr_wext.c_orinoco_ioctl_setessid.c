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
struct orinoco_private {int /*<<< orphan*/  desired_essid; } ;
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;
struct iw_point {int /*<<< orphan*/  length; scalar_t__ flags; } ;

/* Variables and functions */
 int E2BIG ; 
 int EBUSY ; 
 int EINPROGRESS ; 
 int /*<<< orphan*/  IW_ESSID_MAX_SIZE ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct orinoco_private* ndev_priv (struct net_device*) ; 
 scalar_t__ orinoco_lock (struct orinoco_private*,unsigned long*) ; 
 int /*<<< orphan*/  orinoco_unlock (struct orinoco_private*,unsigned long*) ; 

__attribute__((used)) static int orinoco_ioctl_setessid(struct net_device *dev,
				  struct iw_request_info *info,
				  struct iw_point *erq,
				  char *essidbuf)
{
	struct orinoco_private *priv = ndev_priv(dev);
	unsigned long flags;

	/* Note : ESSID is ignored in Ad-Hoc demo mode, but we can set it
	 * anyway... - Jean II */

	/* Hum... Should not use Wireless Extension constant (may change),
	 * should use our own... - Jean II */
	if (erq->length > IW_ESSID_MAX_SIZE)
		return -E2BIG;

	if (orinoco_lock(priv, &flags) != 0)
		return -EBUSY;

	/* NULL the string (for NULL termination & ESSID = ANY) - Jean II */
	memset(priv->desired_essid, 0, sizeof(priv->desired_essid));

	/* If not ANY, get the new ESSID */
	if (erq->flags)
		memcpy(priv->desired_essid, essidbuf, erq->length);

	orinoco_unlock(priv, &flags);

	return -EINPROGRESS;		/* Call commit handler */
}