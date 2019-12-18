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
struct orinoco_private {int preamble; int /*<<< orphan*/  has_preamble; } ;
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINPROGRESS ; 
 int EOPNOTSUPP ; 
 struct orinoco_private* ndev_priv (struct net_device*) ; 
 scalar_t__ orinoco_lock (struct orinoco_private*,unsigned long*) ; 
 int /*<<< orphan*/  orinoco_unlock (struct orinoco_private*,unsigned long*) ; 

__attribute__((used)) static int orinoco_ioctl_setpreamble(struct net_device *dev,
				     struct iw_request_info *info,
				     void *wrqu,
				     char *extra)
{
	struct orinoco_private *priv = ndev_priv(dev);
	unsigned long flags;
	int val;

	if (!priv->has_preamble)
		return -EOPNOTSUPP;

	/* 802.11b has recently defined some short preamble.
	 * Basically, the Phy header has been reduced in size.
	 * This increase performance, especially at high rates
	 * (the preamble is transmitted at 1Mb/s), unfortunately
	 * this give compatibility troubles... - Jean II */
	val = *((int *) extra);

	if (orinoco_lock(priv, &flags) != 0)
		return -EBUSY;

	if (val)
		priv->preamble = 1;
	else
		priv->preamble = 0;

	orinoco_unlock(priv, &flags);

	return -EINPROGRESS;		/* Call commit handler */
}