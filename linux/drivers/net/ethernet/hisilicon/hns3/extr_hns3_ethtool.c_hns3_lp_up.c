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
struct hnae3_handle {int dummy; } ;
typedef  enum hnae3_loop { ____Placeholder_hnae3_loop } hnae3_loop ;

/* Variables and functions */
 int HNS3_NIC_LB_SETUP_USEC ; 
 struct hnae3_handle* hns3_get_handle (struct net_device*) ; 
 int hns3_lp_setup (struct net_device*,int,int) ; 
 int hns3_nic_reset_all_ring (struct hnae3_handle*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int hns3_lp_up(struct net_device *ndev, enum hnae3_loop loop_mode)
{
	struct hnae3_handle *h = hns3_get_handle(ndev);
	int ret;

	ret = hns3_nic_reset_all_ring(h);
	if (ret)
		return ret;

	ret = hns3_lp_setup(ndev, loop_mode, true);
	usleep_range(HNS3_NIC_LB_SETUP_USEC, HNS3_NIC_LB_SETUP_USEC * 2);

	return ret;
}