#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct net_device {int dummy; } ;
struct cpsw_slave {struct net_device* ndev; } ;
struct cpsw_priv {int /*<<< orphan*/  dev; struct cpsw_common* cpsw; } ;
struct TYPE_5__ {int slaves; } ;
struct cpsw_common {int speed; struct cpsw_slave* slaves; TYPE_2__ data; int /*<<< orphan*/  dev; TYPE_1__* txv; int /*<<< orphan*/  dma; } ;
struct TYPE_6__ {int tx_maxrate; } ;
struct TYPE_4__ {int /*<<< orphan*/  ch; } ;

/* Variables and functions */
 int EINVAL ; 
 int cpdma_chan_get_min_rate (int /*<<< orphan*/ ) ; 
 int cpdma_chan_set_rate (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cpsw_split_res (struct cpsw_common*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 TYPE_3__* netdev_get_tx_queue (struct net_device*,int) ; 
 struct cpsw_priv* netdev_priv (struct net_device*) ; 
 int pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_noidle (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cpsw_ndo_set_tx_maxrate(struct net_device *ndev, int queue, u32 rate)
{
	struct cpsw_priv *priv = netdev_priv(ndev);
	struct cpsw_common *cpsw = priv->cpsw;
	struct cpsw_slave *slave;
	u32 min_rate;
	u32 ch_rate;
	int i, ret;

	ch_rate = netdev_get_tx_queue(ndev, queue)->tx_maxrate;
	if (ch_rate == rate)
		return 0;

	ch_rate = rate * 1000;
	min_rate = cpdma_chan_get_min_rate(cpsw->dma);
	if ((ch_rate < min_rate && ch_rate)) {
		dev_err(priv->dev, "The channel rate cannot be less than %dMbps",
			min_rate);
		return -EINVAL;
	}

	if (rate > cpsw->speed) {
		dev_err(priv->dev, "The channel rate cannot be more than 2Gbps");
		return -EINVAL;
	}

	ret = pm_runtime_get_sync(cpsw->dev);
	if (ret < 0) {
		pm_runtime_put_noidle(cpsw->dev);
		return ret;
	}

	ret = cpdma_chan_set_rate(cpsw->txv[queue].ch, ch_rate);
	pm_runtime_put(cpsw->dev);

	if (ret)
		return ret;

	/* update rates for slaves tx queues */
	for (i = 0; i < cpsw->data.slaves; i++) {
		slave = &cpsw->slaves[i];
		if (!slave->ndev)
			continue;

		netdev_get_tx_queue(slave->ndev, queue)->tx_maxrate = rate;
	}

	cpsw_split_res(cpsw);
	return ret;
}