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
typedef  int /*<<< orphan*/  u8 ;
struct tx_complete_mon_data {size_t size; int /*<<< orphan*/  buff; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int EFAULT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  kfree (struct tx_complete_mon_data*) ; 
 struct tx_complete_mon_data* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmemdup (int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mgmt_tx_complete ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int /*<<< orphan*/  wilc_wlan_txq_add_mgmt_pkt (struct net_device*,struct tx_complete_mon_data*,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mon_mgmt_tx(struct net_device *dev, const u8 *buf, size_t len)
{
	struct tx_complete_mon_data *mgmt_tx = NULL;

	if (!dev)
		return -EFAULT;

	netif_stop_queue(dev);
	mgmt_tx = kmalloc(sizeof(*mgmt_tx), GFP_ATOMIC);
	if (!mgmt_tx)
		return -ENOMEM;

	mgmt_tx->buff = kmemdup(buf, len, GFP_ATOMIC);
	if (!mgmt_tx->buff) {
		kfree(mgmt_tx);
		return -ENOMEM;
	}

	mgmt_tx->size = len;

	wilc_wlan_txq_add_mgmt_pkt(dev, mgmt_tx, mgmt_tx->buff, mgmt_tx->size,
				   mgmt_tx_complete);

	netif_wake_queue(dev);
	return 0;
}