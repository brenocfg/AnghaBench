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
struct dpni_rx_tc_dist_cfg {int /*<<< orphan*/  dist_mode; int /*<<< orphan*/  dist_size; int /*<<< orphan*/  key_cfg_iova; } ;
struct dpaa2_eth_priv {int /*<<< orphan*/  mc_token; int /*<<< orphan*/  mc_io; TYPE_2__* net_dev; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
typedef  int /*<<< orphan*/  dist_cfg ;
struct TYPE_3__ {struct device* parent; } ;
struct TYPE_4__ {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPNI_DIST_MODE_HASH ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dpaa2_eth_queue_count (struct dpaa2_eth_priv*) ; 
 int dpni_set_rx_tc_dist (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dpni_rx_tc_dist_cfg*) ; 
 int /*<<< orphan*/  memset (struct dpni_rx_tc_dist_cfg*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int config_legacy_hash_key(struct dpaa2_eth_priv *priv, dma_addr_t key)
{
	struct device *dev = priv->net_dev->dev.parent;
	struct dpni_rx_tc_dist_cfg dist_cfg;
	int err;

	memset(&dist_cfg, 0, sizeof(dist_cfg));

	dist_cfg.key_cfg_iova = key;
	dist_cfg.dist_size = dpaa2_eth_queue_count(priv);
	dist_cfg.dist_mode = DPNI_DIST_MODE_HASH;

	err = dpni_set_rx_tc_dist(priv->mc_io, 0, priv->mc_token, 0, &dist_cfg);
	if (err)
		dev_err(dev, "dpni_set_rx_tc_dist failed\n");

	return err;
}