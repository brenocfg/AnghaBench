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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct net_device {int dummy; } ;
struct ipoib_dev_priv {int /*<<< orphan*/  qp; int /*<<< orphan*/  flags; int /*<<< orphan*/  pkey; int /*<<< orphan*/  port; int /*<<< orphan*/  ca; } ;
struct ib_qp_attr {int /*<<< orphan*/  qkey; } ;
struct ib_device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IB_QP_QKEY ; 
 int /*<<< orphan*/  IPOIB_PKEY_ASSIGNED ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int ib_attach_mcast (int /*<<< orphan*/ ,union ib_gid*,int /*<<< orphan*/ ) ; 
 scalar_t__ ib_find_pkey (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int ib_modify_qp (int /*<<< orphan*/ ,struct ib_qp_attr*,int /*<<< orphan*/ ) ; 
 struct ipoib_dev_priv* ipoib_priv (struct net_device*) ; 
 int /*<<< orphan*/  ipoib_warn (struct ipoib_dev_priv*,char*,int) ; 
 int /*<<< orphan*/  kfree (struct ib_qp_attr*) ; 
 struct ib_qp_attr* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int ipoib_mcast_attach(struct net_device *dev, struct ib_device *hca,
		       union ib_gid *mgid, u16 mlid, int set_qkey, u32 qkey)
{
	struct ipoib_dev_priv *priv = ipoib_priv(dev);
	struct ib_qp_attr *qp_attr = NULL;
	int ret;
	u16 pkey_index;

	if (ib_find_pkey(priv->ca, priv->port, priv->pkey, &pkey_index)) {
		clear_bit(IPOIB_PKEY_ASSIGNED, &priv->flags);
		ret = -ENXIO;
		goto out;
	}
	set_bit(IPOIB_PKEY_ASSIGNED, &priv->flags);

	if (set_qkey) {
		ret = -ENOMEM;
		qp_attr = kmalloc(sizeof(*qp_attr), GFP_KERNEL);
		if (!qp_attr)
			goto out;

		/* set correct QKey for QP */
		qp_attr->qkey = qkey;
		ret = ib_modify_qp(priv->qp, qp_attr, IB_QP_QKEY);
		if (ret) {
			ipoib_warn(priv, "failed to modify QP, ret = %d\n", ret);
			goto out;
		}
	}

	/* attach QP to multicast group */
	ret = ib_attach_mcast(priv->qp, mgid, mlid);
	if (ret)
		ipoib_warn(priv, "failed to attach to multicast group, ret = %d\n", ret);

out:
	kfree(qp_attr);
	return ret;
}