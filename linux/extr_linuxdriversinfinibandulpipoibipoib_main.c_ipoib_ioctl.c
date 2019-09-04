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
struct net_device {int dummy; } ;
struct ipoib_dev_priv {TYPE_1__* rn_ops; } ;
struct ifreq {int dummy; } ;
struct TYPE_2__ {int (* ndo_do_ioctl ) (struct net_device*,struct ifreq*,int) ;} ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 struct ipoib_dev_priv* ipoib_priv (struct net_device*) ; 
 int stub1 (struct net_device*,struct ifreq*,int) ; 

__attribute__((used)) static int ipoib_ioctl(struct net_device *dev, struct ifreq *ifr,
		       int cmd)
{
	struct ipoib_dev_priv *priv = ipoib_priv(dev);

	if (!priv->rn_ops->ndo_do_ioctl)
		return -EOPNOTSUPP;

	return priv->rn_ops->ndo_do_ioctl(dev, ifr, cmd);
}