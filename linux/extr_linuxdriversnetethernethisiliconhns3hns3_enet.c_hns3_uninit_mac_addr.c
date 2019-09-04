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
struct net_device {int /*<<< orphan*/  dev_addr; } ;
struct hns3_nic_priv {struct hnae3_handle* ae_handle; } ;
struct hnae3_handle {TYPE_2__* ae_algo; } ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* rm_uc_addr ) (struct hnae3_handle*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 struct hns3_nic_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  stub1 (struct hnae3_handle*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hns3_uninit_mac_addr(struct net_device *netdev)
{
	struct hns3_nic_priv *priv = netdev_priv(netdev);
	struct hnae3_handle *h = priv->ae_handle;

	if (h->ae_algo->ops->rm_uc_addr)
		h->ae_algo->ops->rm_uc_addr(h, netdev->dev_addr);
}