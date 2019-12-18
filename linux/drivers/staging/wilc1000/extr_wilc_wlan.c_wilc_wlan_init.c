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
struct wilc_vif {struct wilc* wilc; } ;
struct wilc {int /*<<< orphan*/ * tx_buffer; int /*<<< orphan*/ * rx_buffer; TYPE_1__* hif_func; scalar_t__ quit; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* hif_init ) (struct wilc*,int) ;} ;

/* Variables and functions */
 int EIO ; 
 int ENOBUFS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  WILC_RX_BUFF_SIZE ; 
 int /*<<< orphan*/  WILC_TX_BUFF_SIZE ; 
 int /*<<< orphan*/  init_chip (struct net_device*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 void* kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct wilc_vif* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  stub1 (struct wilc*,int) ; 

int wilc_wlan_init(struct net_device *dev)
{
	int ret = 0;
	struct wilc_vif *vif = netdev_priv(dev);
	struct wilc *wilc;

	wilc = vif->wilc;

	wilc->quit = 0;

	if (!wilc->hif_func->hif_init(wilc, false)) {
		ret = -EIO;
		goto fail;
	}

	if (!wilc->tx_buffer)
		wilc->tx_buffer = kmalloc(WILC_TX_BUFF_SIZE, GFP_KERNEL);

	if (!wilc->tx_buffer) {
		ret = -ENOBUFS;
		goto fail;
	}

	if (!wilc->rx_buffer)
		wilc->rx_buffer = kmalloc(WILC_RX_BUFF_SIZE, GFP_KERNEL);

	if (!wilc->rx_buffer) {
		ret = -ENOBUFS;
		goto fail;
	}

	if (!init_chip(dev)) {
		ret = -EIO;
		goto fail;
	}

	return 1;

fail:

	kfree(wilc->rx_buffer);
	wilc->rx_buffer = NULL;
	kfree(wilc->tx_buffer);
	wilc->tx_buffer = NULL;

	return ret;
}