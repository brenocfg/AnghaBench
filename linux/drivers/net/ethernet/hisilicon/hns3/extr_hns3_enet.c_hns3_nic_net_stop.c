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
struct hns3_nic_priv {int /*<<< orphan*/  ae_handle; int /*<<< orphan*/  state; } ;
struct hnae3_handle {TYPE_1__* ae_algo; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* set_timer_task ) (int /*<<< orphan*/ ,int) ;} ;
struct TYPE_3__ {TYPE_2__* ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  HNS3_NIC_STATE_DOWN ; 
 int /*<<< orphan*/  drv ; 
 struct hnae3_handle* hns3_get_handle (struct net_device*) ; 
 int /*<<< orphan*/  hns3_nic_net_down (struct net_device*) ; 
 struct hns3_nic_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  netif_dbg (struct hnae3_handle*,int /*<<< orphan*/ ,struct net_device*,char*) ; 
 int /*<<< orphan*/  netif_tx_stop_all_queues (struct net_device*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hns3_nic_net_stop(struct net_device *netdev)
{
	struct hns3_nic_priv *priv = netdev_priv(netdev);
	struct hnae3_handle *h = hns3_get_handle(netdev);

	if (test_and_set_bit(HNS3_NIC_STATE_DOWN, &priv->state))
		return 0;

	netif_dbg(h, drv, netdev, "net stop\n");

	if (h->ae_algo->ops->set_timer_task)
		h->ae_algo->ops->set_timer_task(priv->ae_handle, false);

	netif_tx_stop_all_queues(netdev);
	netif_carrier_off(netdev);

	hns3_nic_net_down(netdev);

	return 0;
}