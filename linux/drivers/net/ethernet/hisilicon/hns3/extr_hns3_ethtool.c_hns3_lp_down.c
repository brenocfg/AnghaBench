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
typedef  enum hnae3_loop { ____Placeholder_hnae3_loop } hnae3_loop ;

/* Variables and functions */
 int HNS3_NIC_LB_SETUP_USEC ; 
 int hns3_lp_setup (struct net_device*,int,int) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int hns3_lp_down(struct net_device *ndev, enum hnae3_loop loop_mode)
{
	int ret;

	ret = hns3_lp_setup(ndev, loop_mode, false);
	if (ret) {
		netdev_err(ndev, "lb_setup return error: %d\n", ret);
		return ret;
	}

	usleep_range(HNS3_NIC_LB_SETUP_USEC, HNS3_NIC_LB_SETUP_USEC * 2);

	return 0;
}