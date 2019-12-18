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
typedef  scalar_t__ u8 ;
struct net_device {int dummy; } ;
struct hnae3_knic_private_info {struct net_device* netdev; } ;
struct hnae3_handle {struct hnae3_knic_private_info kinfo; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 scalar_t__ HNAE3_MAX_TC ; 
 int hns3_nic_set_real_num_queue (struct net_device*) ; 

__attribute__((used)) static int hns3_client_setup_tc(struct hnae3_handle *handle, u8 tc)
{
	struct hnae3_knic_private_info *kinfo = &handle->kinfo;
	struct net_device *ndev = kinfo->netdev;

	if (tc > HNAE3_MAX_TC)
		return -EINVAL;

	if (!ndev)
		return -ENODEV;

	return hns3_nic_set_real_num_queue(ndev);
}