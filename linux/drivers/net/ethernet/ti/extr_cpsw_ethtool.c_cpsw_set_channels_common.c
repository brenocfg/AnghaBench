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
struct net_device {int dummy; } ;
struct ethtool_channels {scalar_t__ rx_count; scalar_t__ tx_count; } ;
struct cpsw_priv {int /*<<< orphan*/  dev; struct cpsw_common* cpsw; } ;
struct TYPE_3__ {int slaves; } ;
struct cpsw_common {scalar_t__ rx_ch_num; int /*<<< orphan*/  tx_ch_num; TYPE_2__* slaves; TYPE_1__ data; scalar_t__ usage_count; } ;
typedef  int /*<<< orphan*/  cpdma_handler_fn ;
struct TYPE_4__ {struct net_device* ndev; } ;

/* Variables and functions */
 int cpsw_check_ch_settings (struct cpsw_common*,struct ethtool_channels*) ; 
 int cpsw_create_xdp_rxqs (struct cpsw_common*) ; 
 int /*<<< orphan*/  cpsw_destroy_xdp_rxqs (struct cpsw_common*) ; 
 int /*<<< orphan*/  cpsw_fail (struct cpsw_common*) ; 
 int cpsw_resume_data_pass (struct net_device*) ; 
 int /*<<< orphan*/  cpsw_split_res (struct cpsw_common*) ; 
 int /*<<< orphan*/  cpsw_suspend_data_pass (struct net_device*) ; 
 int cpsw_update_channels_res (struct cpsw_priv*,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct cpsw_priv* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 int netif_set_real_num_rx_queues (struct net_device*,scalar_t__) ; 
 int netif_set_real_num_tx_queues (struct net_device*,int /*<<< orphan*/ ) ; 

int cpsw_set_channels_common(struct net_device *ndev,
			     struct ethtool_channels *chs,
			     cpdma_handler_fn rx_handler)
{
	struct cpsw_priv *priv = netdev_priv(ndev);
	struct cpsw_common *cpsw = priv->cpsw;
	struct net_device *sl_ndev;
	int i, new_pools, ret;

	ret = cpsw_check_ch_settings(cpsw, chs);
	if (ret < 0)
		return ret;

	cpsw_suspend_data_pass(ndev);

	new_pools = (chs->rx_count != cpsw->rx_ch_num) && cpsw->usage_count;

	ret = cpsw_update_channels_res(priv, chs->rx_count, 1, rx_handler);
	if (ret)
		goto err;

	ret = cpsw_update_channels_res(priv, chs->tx_count, 0, rx_handler);
	if (ret)
		goto err;

	for (i = 0; i < cpsw->data.slaves; i++) {
		sl_ndev = cpsw->slaves[i].ndev;
		if (!(sl_ndev && netif_running(sl_ndev)))
			continue;

		/* Inform stack about new count of queues */
		ret = netif_set_real_num_tx_queues(sl_ndev, cpsw->tx_ch_num);
		if (ret) {
			dev_err(priv->dev, "cannot set real number of tx queues\n");
			goto err;
		}

		ret = netif_set_real_num_rx_queues(sl_ndev, cpsw->rx_ch_num);
		if (ret) {
			dev_err(priv->dev, "cannot set real number of rx queues\n");
			goto err;
		}
	}

	cpsw_split_res(cpsw);

	if (new_pools) {
		cpsw_destroy_xdp_rxqs(cpsw);
		ret = cpsw_create_xdp_rxqs(cpsw);
		if (ret)
			goto err;
	}

	ret = cpsw_resume_data_pass(ndev);
	if (!ret)
		return 0;
err:
	dev_err(priv->dev, "cannot update channels number, closing device\n");
	cpsw_fail(cpsw);
	return ret;
}