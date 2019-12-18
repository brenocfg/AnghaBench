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
struct rdma_netdev {int (* detach_mcast ) (struct net_device*,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ;} ;
struct net_device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  raw; } ;
struct TYPE_3__ {int /*<<< orphan*/  mlid; TYPE_2__ mgid; } ;
struct ipoib_mcast {int /*<<< orphan*/  flags; TYPE_1__ mcmember; int /*<<< orphan*/  mc; } ;
struct ipoib_dev_priv {int /*<<< orphan*/  ca; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPOIB_MCAST_FLAG_ATTACHED ; 
 int /*<<< orphan*/  IPOIB_MCAST_FLAG_BUSY ; 
 int /*<<< orphan*/  IPOIB_MCAST_FLAG_SENDONLY ; 
 int /*<<< orphan*/  IS_ERR_OR_NULL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_sa_free_multicast (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipoib_dbg (struct ipoib_dev_priv*,char*) ; 
 int /*<<< orphan*/  ipoib_dbg_mcast (struct ipoib_dev_priv*,char*,int /*<<< orphan*/ ) ; 
 struct ipoib_dev_priv* ipoib_priv (struct net_device*) ; 
 int /*<<< orphan*/  ipoib_warn (struct ipoib_dev_priv*,char*,...) ; 
 struct rdma_netdev* netdev_priv (struct net_device*) ; 
 int stub1 (struct net_device*,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ipoib_mcast_leave(struct net_device *dev, struct ipoib_mcast *mcast)
{
	struct ipoib_dev_priv *priv = ipoib_priv(dev);
	struct rdma_netdev *rn = netdev_priv(dev);
	int ret = 0;

	if (test_and_clear_bit(IPOIB_MCAST_FLAG_BUSY, &mcast->flags))
		ipoib_warn(priv, "ipoib_mcast_leave on an in-flight join\n");

	if (!IS_ERR_OR_NULL(mcast->mc))
		ib_sa_free_multicast(mcast->mc);

	if (test_and_clear_bit(IPOIB_MCAST_FLAG_ATTACHED, &mcast->flags)) {
		ipoib_dbg_mcast(priv, "leaving MGID %pI6\n",
				mcast->mcmember.mgid.raw);

		/* Remove ourselves from the multicast group */
		ret = rn->detach_mcast(dev, priv->ca, &mcast->mcmember.mgid,
				       be16_to_cpu(mcast->mcmember.mlid));
		if (ret)
			ipoib_warn(priv, "ib_detach_mcast failed (result = %d)\n", ret);
	} else if (!test_bit(IPOIB_MCAST_FLAG_SENDONLY, &mcast->flags))
		ipoib_dbg(priv, "leaving with no mcmember but not a "
			  "SENDONLY join\n");

	return 0;
}