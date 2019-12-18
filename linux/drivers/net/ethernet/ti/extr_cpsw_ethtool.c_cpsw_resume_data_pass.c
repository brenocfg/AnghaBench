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
struct cpsw_priv {struct cpsw_common* cpsw; } ;
struct TYPE_4__ {int slaves; } ;
struct cpsw_common {TYPE_1__* slaves; TYPE_2__ data; int /*<<< orphan*/  dma; scalar_t__ usage_count; } ;
struct TYPE_3__ {struct net_device* ndev; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpdma_ctlr_start (int /*<<< orphan*/ ) ; 
 int cpsw_fill_rx_channels (struct cpsw_priv*) ; 
 int /*<<< orphan*/  cpsw_intr_enable (struct cpsw_common*) ; 
 struct cpsw_priv* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 int /*<<< orphan*/  netif_tx_start_all_queues (struct net_device*) ; 

__attribute__((used)) static int cpsw_resume_data_pass(struct net_device *ndev)
{
	struct cpsw_priv *priv = netdev_priv(ndev);
	struct cpsw_common *cpsw = priv->cpsw;
	int i, ret;

	/* After this receive is started */
	if (cpsw->usage_count) {
		ret = cpsw_fill_rx_channels(priv);
		if (ret)
			return ret;

		cpdma_ctlr_start(cpsw->dma);
		cpsw_intr_enable(cpsw);
	}

	/* Resume transmit for every affected interface */
	for (i = 0; i < cpsw->data.slaves; i++) {
		ndev = cpsw->slaves[i].ndev;
		if (ndev && netif_running(ndev))
			netif_tx_start_all_queues(ndev);
	}

	return 0;
}