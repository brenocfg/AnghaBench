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
struct net_device {int dummy; } ;
struct hnae3_knic_private_info {struct net_device* netdev; } ;
struct hnae3_handle {struct hnae3_knic_private_info kinfo; } ;

/* Variables and functions */
 int hns3_nic_net_stop (struct net_device*) ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 

__attribute__((used)) static int hns3_reset_notify_down_enet(struct hnae3_handle *handle)
{
	struct hnae3_knic_private_info *kinfo = &handle->kinfo;
	struct net_device *ndev = kinfo->netdev;

	if (!netif_running(ndev))
		return 0;

	return hns3_nic_net_stop(ndev);
}