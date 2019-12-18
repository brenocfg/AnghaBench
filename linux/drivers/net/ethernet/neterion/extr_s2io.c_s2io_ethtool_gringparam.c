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
struct TYPE_6__ {int rx_ring_num; int tx_fifo_num; int /*<<< orphan*/  max_txds; TYPE_2__* tx_cfg; TYPE_1__* rx_cfg; } ;
struct s2io_nic {scalar_t__ rxd_mode; TYPE_3__ config; } ;
struct net_device {int dummy; } ;
struct ethtool_ringparam {int rx_pending; int rx_jumbo_pending; int tx_pending; int /*<<< orphan*/  tx_max_pending; void* rx_jumbo_max_pending; void* rx_max_pending; } ;
struct TYPE_5__ {scalar_t__ fifo_len; } ;
struct TYPE_4__ {scalar_t__ num_rxd; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_PRINT (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INFO_DBG ; 
 void* MAX_RX_DESC_1 ; 
 void* MAX_RX_DESC_2 ; 
 int /*<<< orphan*/  MAX_TX_DESC ; 
 scalar_t__ RXD_MODE_1 ; 
 struct s2io_nic* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void s2io_ethtool_gringparam(struct net_device *dev,
				    struct ethtool_ringparam *ering)
{
	struct s2io_nic *sp = netdev_priv(dev);
	int i, tx_desc_count = 0, rx_desc_count = 0;

	if (sp->rxd_mode == RXD_MODE_1) {
		ering->rx_max_pending = MAX_RX_DESC_1;
		ering->rx_jumbo_max_pending = MAX_RX_DESC_1;
	} else {
		ering->rx_max_pending = MAX_RX_DESC_2;
		ering->rx_jumbo_max_pending = MAX_RX_DESC_2;
	}

	ering->tx_max_pending = MAX_TX_DESC;

	for (i = 0; i < sp->config.rx_ring_num; i++)
		rx_desc_count += sp->config.rx_cfg[i].num_rxd;
	ering->rx_pending = rx_desc_count;
	ering->rx_jumbo_pending = rx_desc_count;

	for (i = 0; i < sp->config.tx_fifo_num; i++)
		tx_desc_count += sp->config.tx_cfg[i].fifo_len;
	ering->tx_pending = tx_desc_count;
	DBG_PRINT(INFO_DBG, "max txds: %d\n", sp->config.max_txds);
}