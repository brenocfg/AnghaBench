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
struct net_device {int flags; int /*<<< orphan*/  name; } ;
struct ipoib_dev_priv {int /*<<< orphan*/ * wq; int /*<<< orphan*/ * pd; TYPE_1__* rn_ops; TYPE_2__* ca; int /*<<< orphan*/ * qp; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;
struct TYPE_3__ {int (* ndo_init ) (struct net_device*) ;} ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int IFF_UP ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WQ_MEM_RECLAIM ; 
 int /*<<< orphan*/ * alloc_ordered_workqueue (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ib_alloc_pd (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_dealloc_pd (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipoib_ib_dev_cleanup (struct net_device*) ; 
 scalar_t__ ipoib_ib_dev_open (struct net_device*) ; 
 int ipoib_neigh_hash_init (struct ipoib_dev_priv*) ; 
 int /*<<< orphan*/  ipoib_neigh_hash_uninit (struct net_device*) ; 
 struct ipoib_dev_priv* ipoib_priv (struct net_device*) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ) ; 
 int stub1 (struct net_device*) ; 

__attribute__((used)) static int ipoib_dev_init(struct net_device *dev)
{
	struct ipoib_dev_priv *priv = ipoib_priv(dev);
	int ret = -ENOMEM;

	priv->qp = NULL;

	/*
	 * the various IPoIB tasks assume they will never race against
	 * themselves, so always use a single thread workqueue
	 */
	priv->wq = alloc_ordered_workqueue("ipoib_wq", WQ_MEM_RECLAIM);
	if (!priv->wq) {
		pr_warn("%s: failed to allocate device WQ\n", dev->name);
		goto out;
	}

	/* create pd, which used both for control and datapath*/
	priv->pd = ib_alloc_pd(priv->ca, 0);
	if (IS_ERR(priv->pd)) {
		pr_warn("%s: failed to allocate PD\n", priv->ca->name);
		goto clean_wq;
	}

	ret = priv->rn_ops->ndo_init(dev);
	if (ret) {
		pr_warn("%s failed to init HW resource\n", dev->name);
		goto out_free_pd;
	}

	ret = ipoib_neigh_hash_init(priv);
	if (ret) {
		pr_warn("%s failed to init neigh hash\n", dev->name);
		goto out_dev_uninit;
	}

	if (dev->flags & IFF_UP) {
		if (ipoib_ib_dev_open(dev)) {
			pr_warn("%s failed to open device\n", dev->name);
			ret = -ENODEV;
			goto out_hash_uninit;
		}
	}

	return 0;

out_hash_uninit:
	ipoib_neigh_hash_uninit(dev);

out_dev_uninit:
	ipoib_ib_dev_cleanup(dev);

out_free_pd:
	if (priv->pd) {
		ib_dealloc_pd(priv->pd);
		priv->pd = NULL;
	}

clean_wq:
	if (priv->wq) {
		destroy_workqueue(priv->wq);
		priv->wq = NULL;
	}

out:
	return ret;
}