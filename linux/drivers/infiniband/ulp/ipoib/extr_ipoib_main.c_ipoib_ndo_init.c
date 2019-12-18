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
struct net_device {int neigh_priv_len; int* broadcast; int /*<<< orphan*/  max_mtu; int /*<<< orphan*/  mtu; } ;
struct ipoib_neigh {int dummy; } ;
struct ipoib_dev_priv {int pkey; int /*<<< orphan*/  vlan_rwsem; int /*<<< orphan*/  child_intfs; int /*<<< orphan*/  list; struct net_device* parent; int /*<<< orphan*/  port; TYPE_2__* dev; TYPE_1__* ca; int /*<<< orphan*/  flags; int /*<<< orphan*/  admin_mtu; int /*<<< orphan*/  mcast_mtu; int /*<<< orphan*/  max_ib_mtu; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPOIB_CM_MTU ; 
 int /*<<< orphan*/  IPOIB_FLAG_DEV_ADDR_SET ; 
 int /*<<< orphan*/  IPOIB_UD_MTU (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_hold (struct net_device*) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipoib_child_init (struct net_device*) ; 
 int ipoib_dev_init (struct net_device*) ; 
 int ipoib_parent_init (struct net_device*) ; 
 struct ipoib_dev_priv* ipoib_priv (struct net_device*) ; 
 int /*<<< orphan*/  ipoib_set_dev_features (struct ipoib_dev_priv*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ipoib_ndo_init(struct net_device *ndev)
{
	struct ipoib_dev_priv *priv = ipoib_priv(ndev);
	int rc;

	if (priv->parent) {
		ipoib_child_init(ndev);
	} else {
		rc = ipoib_parent_init(ndev);
		if (rc)
			return rc;
	}

	/* MTU will be reset when mcast join happens */
	ndev->mtu = IPOIB_UD_MTU(priv->max_ib_mtu);
	priv->mcast_mtu = priv->admin_mtu = ndev->mtu;
	ndev->max_mtu = IPOIB_CM_MTU;

	ndev->neigh_priv_len = sizeof(struct ipoib_neigh);

	/*
	 * Set the full membership bit, so that we join the right
	 * broadcast group, etc.
	 */
	priv->pkey |= 0x8000;

	ndev->broadcast[8] = priv->pkey >> 8;
	ndev->broadcast[9] = priv->pkey & 0xff;
	set_bit(IPOIB_FLAG_DEV_ADDR_SET, &priv->flags);

	ipoib_set_dev_features(priv);

	rc = ipoib_dev_init(ndev);
	if (rc) {
		pr_warn("%s: failed to initialize device: %s port %d (ret = %d)\n",
			priv->ca->name, priv->dev->name, priv->port, rc);
		return rc;
	}

	if (priv->parent) {
		struct ipoib_dev_priv *ppriv = ipoib_priv(priv->parent);

		dev_hold(priv->parent);

		down_write(&ppriv->vlan_rwsem);
		list_add_tail(&priv->list, &ppriv->child_intfs);
		up_write(&ppriv->vlan_rwsem);
	}

	return 0;
}