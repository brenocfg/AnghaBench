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
typedef  int u8 ;
struct net_device {int dummy; } ;
struct hns3_nic_priv {struct hnae3_handle* ae_handle; } ;
struct hnae3_handle {TYPE_2__* ae_algo; } ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct TYPE_3__ {int (* set_promisc_mode ) (struct hnae3_handle*,int,int) ;} ;

/* Variables and functions */
 int HNAE3_MPE ; 
 int HNAE3_UPE ; 
 struct hns3_nic_priv* netdev_priv (struct net_device*) ; 
 int stub1 (struct hnae3_handle*,int,int) ; 

int hns3_update_promisc_mode(struct net_device *netdev, u8 promisc_flags)
{
	struct hns3_nic_priv *priv = netdev_priv(netdev);
	struct hnae3_handle *h = priv->ae_handle;

	if (h->ae_algo->ops->set_promisc_mode) {
		return h->ae_algo->ops->set_promisc_mode(h,
						promisc_flags & HNAE3_UPE,
						promisc_flags & HNAE3_MPE);
	}

	return 0;
}