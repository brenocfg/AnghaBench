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
struct net_device {int /*<<< orphan*/  name; } ;
struct ipoib_dev_priv {int pkey; int /*<<< orphan*/  flags; int /*<<< orphan*/  ah_reap_task; TYPE_1__* rn_ops; int /*<<< orphan*/  wq; } ;
struct TYPE_2__ {scalar_t__ (* ndo_open ) (struct net_device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  HZ ; 
 int /*<<< orphan*/  IPOIB_FLAG_INITIALIZED ; 
 int /*<<< orphan*/  IPOIB_PKEY_ASSIGNED ; 
 int /*<<< orphan*/  IPOIB_STOP_REAPER ; 
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipoib_ib_dev_stop (struct net_device*) ; 
 int /*<<< orphan*/  ipoib_pkey_dev_check_presence (struct net_device*) ; 
 struct ipoib_dev_priv* ipoib_priv (struct net_device*) ; 
 int /*<<< orphan*/  ipoib_warn (struct ipoib_dev_priv*,char*,int,char*) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  round_jiffies_relative (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ stub1 (struct net_device*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int ipoib_ib_dev_open(struct net_device *dev)
{
	struct ipoib_dev_priv *priv = ipoib_priv(dev);

	ipoib_pkey_dev_check_presence(dev);

	if (!test_bit(IPOIB_PKEY_ASSIGNED, &priv->flags)) {
		ipoib_warn(priv, "P_Key 0x%04x is %s\n", priv->pkey,
			   (!(priv->pkey & 0x7fff) ? "Invalid" : "not found"));
		return -1;
	}

	clear_bit(IPOIB_STOP_REAPER, &priv->flags);
	queue_delayed_work(priv->wq, &priv->ah_reap_task,
			   round_jiffies_relative(HZ));

	if (priv->rn_ops->ndo_open(dev)) {
		pr_warn("%s: Failed to open dev\n", dev->name);
		goto dev_stop;
	}

	set_bit(IPOIB_FLAG_INITIALIZED, &priv->flags);

	return 0;

dev_stop:
	set_bit(IPOIB_STOP_REAPER, &priv->flags);
	cancel_delayed_work(&priv->ah_reap_task);
	set_bit(IPOIB_FLAG_INITIALIZED, &priv->flags);
	ipoib_ib_dev_stop(dev);
	return -1;
}