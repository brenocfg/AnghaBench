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
typedef  union ib_gid {int dummy; } ib_gid ;
typedef  int /*<<< orphan*/  u16 ;
struct net_device {int dummy; } ;
struct ipoib_dev_priv {int /*<<< orphan*/  qp; } ;
struct ib_device {int dummy; } ;

/* Variables and functions */
 int ib_detach_mcast (int /*<<< orphan*/ ,union ib_gid*,int /*<<< orphan*/ ) ; 
 struct ipoib_dev_priv* ipoib_priv (struct net_device*) ; 

int ipoib_mcast_detach(struct net_device *dev, struct ib_device *hca,
		       union ib_gid *mgid, u16 mlid)
{
	struct ipoib_dev_priv *priv = ipoib_priv(dev);
	int ret;

	ret = ib_detach_mcast(priv->qp, mgid, mlid);

	return ret;
}