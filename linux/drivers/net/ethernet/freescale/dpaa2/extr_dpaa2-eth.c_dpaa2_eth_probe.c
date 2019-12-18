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
struct net_device {int features; int /*<<< orphan*/  name; } ;
struct device {int dummy; } ;
struct fsl_mc_device {struct device dev; } ;
struct dpaa2_eth_priv {int do_link_poll; int /*<<< orphan*/  mc_io; int /*<<< orphan*/ * percpu_stats; int /*<<< orphan*/ * percpu_extras; int /*<<< orphan*/  poll_thread; int /*<<< orphan*/  iommu_domain; struct net_device* net_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPAA2_ETH_MAX_NETDEV_QUEUES ; 
 int ENOMEM ; 
 int ENXIO ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  FSL_MC_IO_ATOMIC_CONTEXT_PORTAL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int NETIF_F_IPV6_CSUM ; 
 int NETIF_F_IP_CSUM ; 
 int NETIF_F_RXCSUM ; 
 int /*<<< orphan*/  SET_NETDEV_DEV (struct net_device*,struct device*) ; 
 int /*<<< orphan*/  add_ch_napi (struct dpaa2_eth_priv*) ; 
 struct net_device* alloc_etherdev_mq (int,int /*<<< orphan*/ ) ; 
 void* alloc_percpu (int /*<<< orphan*/ ) ; 
 int alloc_rings (struct dpaa2_eth_priv*) ; 
 int bind_dpni (struct dpaa2_eth_priv*) ; 
 int /*<<< orphan*/  del_ch_napi (struct dpaa2_eth_priv*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct net_device*) ; 
 int /*<<< orphan*/  dpaa2_dbg_add (struct dpaa2_eth_priv*) ; 
 int /*<<< orphan*/  free_dpbp (struct dpaa2_eth_priv*) ; 
 int /*<<< orphan*/  free_dpio (struct dpaa2_eth_priv*) ; 
 int /*<<< orphan*/  free_dpni (struct dpaa2_eth_priv*) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  free_percpu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_rings (struct dpaa2_eth_priv*) ; 
 int /*<<< orphan*/  fsl_mc_free_irqs (struct fsl_mc_device*) ; 
 int fsl_mc_portal_allocate (struct fsl_mc_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fsl_mc_portal_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iommu_get_domain_for_dev (struct device*) ; 
 int /*<<< orphan*/  kthread_run (int /*<<< orphan*/ ,struct dpaa2_eth_priv*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kthread_stop (int /*<<< orphan*/ ) ; 
 int netdev_init (struct net_device*) ; 
 struct dpaa2_eth_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netdev_warn (struct net_device*,char*) ; 
 int /*<<< orphan*/  poll_link_state ; 
 int register_netdev (struct net_device*) ; 
 int set_rx_csum (struct dpaa2_eth_priv*,int) ; 
 int set_tx_csum (struct dpaa2_eth_priv*,int) ; 
 int setup_dpbp (struct dpaa2_eth_priv*) ; 
 int setup_dpio (struct dpaa2_eth_priv*) ; 
 int setup_dpni (struct fsl_mc_device*) ; 
 int /*<<< orphan*/  setup_fqs (struct dpaa2_eth_priv*) ; 
 int setup_irqs (struct fsl_mc_device*) ; 

__attribute__((used)) static int dpaa2_eth_probe(struct fsl_mc_device *dpni_dev)
{
	struct device *dev;
	struct net_device *net_dev = NULL;
	struct dpaa2_eth_priv *priv = NULL;
	int err = 0;

	dev = &dpni_dev->dev;

	/* Net device */
	net_dev = alloc_etherdev_mq(sizeof(*priv), DPAA2_ETH_MAX_NETDEV_QUEUES);
	if (!net_dev) {
		dev_err(dev, "alloc_etherdev_mq() failed\n");
		return -ENOMEM;
	}

	SET_NETDEV_DEV(net_dev, dev);
	dev_set_drvdata(dev, net_dev);

	priv = netdev_priv(net_dev);
	priv->net_dev = net_dev;

	priv->iommu_domain = iommu_get_domain_for_dev(dev);

	/* Obtain a MC portal */
	err = fsl_mc_portal_allocate(dpni_dev, FSL_MC_IO_ATOMIC_CONTEXT_PORTAL,
				     &priv->mc_io);
	if (err) {
		if (err == -ENXIO)
			err = -EPROBE_DEFER;
		else
			dev_err(dev, "MC portal allocation failed\n");
		goto err_portal_alloc;
	}

	/* MC objects initialization and configuration */
	err = setup_dpni(dpni_dev);
	if (err)
		goto err_dpni_setup;

	err = setup_dpio(priv);
	if (err)
		goto err_dpio_setup;

	setup_fqs(priv);

	err = setup_dpbp(priv);
	if (err)
		goto err_dpbp_setup;

	err = bind_dpni(priv);
	if (err)
		goto err_bind;

	/* Add a NAPI context for each channel */
	add_ch_napi(priv);

	/* Percpu statistics */
	priv->percpu_stats = alloc_percpu(*priv->percpu_stats);
	if (!priv->percpu_stats) {
		dev_err(dev, "alloc_percpu(percpu_stats) failed\n");
		err = -ENOMEM;
		goto err_alloc_percpu_stats;
	}
	priv->percpu_extras = alloc_percpu(*priv->percpu_extras);
	if (!priv->percpu_extras) {
		dev_err(dev, "alloc_percpu(percpu_extras) failed\n");
		err = -ENOMEM;
		goto err_alloc_percpu_extras;
	}

	err = netdev_init(net_dev);
	if (err)
		goto err_netdev_init;

	/* Configure checksum offload based on current interface flags */
	err = set_rx_csum(priv, !!(net_dev->features & NETIF_F_RXCSUM));
	if (err)
		goto err_csum;

	err = set_tx_csum(priv, !!(net_dev->features &
				   (NETIF_F_IP_CSUM | NETIF_F_IPV6_CSUM)));
	if (err)
		goto err_csum;

	err = alloc_rings(priv);
	if (err)
		goto err_alloc_rings;

	err = setup_irqs(dpni_dev);
	if (err) {
		netdev_warn(net_dev, "Failed to set link interrupt, fall back to polling\n");
		priv->poll_thread = kthread_run(poll_link_state, priv,
						"%s_poll_link", net_dev->name);
		if (IS_ERR(priv->poll_thread)) {
			dev_err(dev, "Error starting polling thread\n");
			goto err_poll_thread;
		}
		priv->do_link_poll = true;
	}

	err = register_netdev(net_dev);
	if (err < 0) {
		dev_err(dev, "register_netdev() failed\n");
		goto err_netdev_reg;
	}

#ifdef CONFIG_DEBUG_FS
	dpaa2_dbg_add(priv);
#endif

	dev_info(dev, "Probed interface %s\n", net_dev->name);
	return 0;

err_netdev_reg:
	if (priv->do_link_poll)
		kthread_stop(priv->poll_thread);
	else
		fsl_mc_free_irqs(dpni_dev);
err_poll_thread:
	free_rings(priv);
err_alloc_rings:
err_csum:
err_netdev_init:
	free_percpu(priv->percpu_extras);
err_alloc_percpu_extras:
	free_percpu(priv->percpu_stats);
err_alloc_percpu_stats:
	del_ch_napi(priv);
err_bind:
	free_dpbp(priv);
err_dpbp_setup:
	free_dpio(priv);
err_dpio_setup:
	free_dpni(priv);
err_dpni_setup:
	fsl_mc_portal_free(priv->mc_io);
err_portal_alloc:
	dev_set_drvdata(dev, NULL);
	free_netdev(net_dev);

	return err;
}