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
struct net_device {scalar_t__ watchdog_timeo; } ;
struct hns3_nic_priv {int /*<<< orphan*/  tx_timeout_count; struct hnae3_handle* ae_handle; } ;
struct hnae3_handle {TYPE_1__* ae_algo; scalar_t__ last_reset_time; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* reset_event ) (struct hnae3_handle*) ;} ;
struct TYPE_3__ {TYPE_2__* ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  hns3_get_tx_timeo_queue_info (struct net_device*) ; 
 int /*<<< orphan*/  jiffies ; 
 struct hns3_nic_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  stub1 (struct hnae3_handle*) ; 
 scalar_t__ time_before (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void hns3_nic_net_timeout(struct net_device *ndev)
{
	struct hns3_nic_priv *priv = netdev_priv(ndev);
	struct hnae3_handle *h = priv->ae_handle;

	if (!hns3_get_tx_timeo_queue_info(ndev))
		return;

	priv->tx_timeout_count++;

	if (time_before(jiffies, (h->last_reset_time + ndev->watchdog_timeo)))
		return;

	/* request the reset */
	if (h->ae_algo->ops->reset_event)
		h->ae_algo->ops->reset_event(h);
}