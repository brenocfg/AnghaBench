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
struct hns3_nic_priv {struct hnae3_handle* ae_handle; } ;
struct hnae3_handle {int /*<<< orphan*/  pdev; TYPE_2__* ae_algo; } ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* reset_event ) (int /*<<< orphan*/ ,struct hnae3_handle*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  hns3_get_tx_timeo_queue_info (struct net_device*) ; 
 struct hns3_nic_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct hnae3_handle*) ; 

__attribute__((used)) static void hns3_nic_net_timeout(struct net_device *ndev)
{
	struct hns3_nic_priv *priv = netdev_priv(ndev);
	struct hnae3_handle *h = priv->ae_handle;

	if (!hns3_get_tx_timeo_queue_info(ndev))
		return;

	/* request the reset, and let the hclge to determine
	 * which reset level should be done
	 */
	if (h->ae_algo->ops->reset_event)
		h->ae_algo->ops->reset_event(h->pdev, h);
}