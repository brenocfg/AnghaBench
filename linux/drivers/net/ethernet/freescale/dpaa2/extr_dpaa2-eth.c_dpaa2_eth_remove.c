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
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct net_device {int /*<<< orphan*/  name; TYPE_1__ dev; } ;
struct device {int dummy; } ;
struct fsl_mc_device {struct device dev; } ;
struct dpaa2_eth_priv {int /*<<< orphan*/  mc_io; int /*<<< orphan*/  percpu_extras; int /*<<< orphan*/  percpu_stats; int /*<<< orphan*/  poll_thread; scalar_t__ do_link_poll; } ;

/* Variables and functions */
 int /*<<< orphan*/  del_ch_napi (struct dpaa2_eth_priv*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct net_device* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  dpaa2_dbg_remove (struct dpaa2_eth_priv*) ; 
 int /*<<< orphan*/  free_dpbp (struct dpaa2_eth_priv*) ; 
 int /*<<< orphan*/  free_dpio (struct dpaa2_eth_priv*) ; 
 int /*<<< orphan*/  free_dpni (struct dpaa2_eth_priv*) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  free_percpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_rings (struct dpaa2_eth_priv*) ; 
 int /*<<< orphan*/  fsl_mc_free_irqs (struct fsl_mc_device*) ; 
 int /*<<< orphan*/  fsl_mc_portal_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kthread_stop (int /*<<< orphan*/ ) ; 
 struct dpaa2_eth_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 

__attribute__((used)) static int dpaa2_eth_remove(struct fsl_mc_device *ls_dev)
{
	struct device *dev;
	struct net_device *net_dev;
	struct dpaa2_eth_priv *priv;

	dev = &ls_dev->dev;
	net_dev = dev_get_drvdata(dev);
	priv = netdev_priv(net_dev);

#ifdef CONFIG_DEBUG_FS
	dpaa2_dbg_remove(priv);
#endif
	unregister_netdev(net_dev);

	if (priv->do_link_poll)
		kthread_stop(priv->poll_thread);
	else
		fsl_mc_free_irqs(ls_dev);

	free_rings(priv);
	free_percpu(priv->percpu_stats);
	free_percpu(priv->percpu_extras);

	del_ch_napi(priv);
	free_dpbp(priv);
	free_dpio(priv);
	free_dpni(priv);

	fsl_mc_portal_free(priv->mc_io);

	free_netdev(net_dev);

	dev_dbg(net_dev->dev.parent, "Removed interface %s\n", net_dev->name);

	return 0;
}