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
struct net_device {int dummy; } ;
struct dpaa2_eth_priv {int /*<<< orphan*/  mc_token; int /*<<< orphan*/  mc_io; } ;

/* Variables and functions */
 int /*<<< orphan*/  disable_ch_napi (struct dpaa2_eth_priv*) ; 
 int /*<<< orphan*/  dpni_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dpni_is_enabled (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  drain_pool (struct dpaa2_eth_priv*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 struct dpaa2_eth_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netdev_warn (struct net_device*,char*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  netif_tx_stop_all_queues (struct net_device*) ; 
 int /*<<< orphan*/  wait_for_egress_fq_empty (struct dpaa2_eth_priv*) ; 
 int /*<<< orphan*/  wait_for_ingress_fq_empty (struct dpaa2_eth_priv*) ; 

__attribute__((used)) static int dpaa2_eth_stop(struct net_device *net_dev)
{
	struct dpaa2_eth_priv *priv = netdev_priv(net_dev);
	int dpni_enabled = 0;
	int retries = 10;

	netif_tx_stop_all_queues(net_dev);
	netif_carrier_off(net_dev);

	/* On dpni_disable(), the MC firmware will:
	 * - stop MAC Rx and wait for all Rx frames to be enqueued to software
	 * - cut off WRIOP dequeues from egress FQs and wait until transmission
	 * of all in flight Tx frames is finished (and corresponding Tx conf
	 * frames are enqueued back to software)
	 *
	 * Before calling dpni_disable(), we wait for all Tx frames to arrive
	 * on WRIOP. After it finishes, wait until all remaining frames on Rx
	 * and Tx conf queues are consumed on NAPI poll.
	 */
	wait_for_egress_fq_empty(priv);

	do {
		dpni_disable(priv->mc_io, 0, priv->mc_token);
		dpni_is_enabled(priv->mc_io, 0, priv->mc_token, &dpni_enabled);
		if (dpni_enabled)
			/* Allow the hardware some slack */
			msleep(100);
	} while (dpni_enabled && --retries);
	if (!retries) {
		netdev_warn(net_dev, "Retry count exceeded disabling DPNI\n");
		/* Must go on and disable NAPI nonetheless, so we don't crash at
		 * the next "ifconfig up"
		 */
	}

	wait_for_ingress_fq_empty(priv);
	disable_ch_napi(priv);

	/* Empty the buffer pool */
	drain_pool(priv);

	return 0;
}