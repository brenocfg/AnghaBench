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
struct hnae3_handle {TYPE_2__* ae_algo; } ;
typedef  enum hnae3_loop { ____Placeholder_hnae3_loop } hnae3_loop ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct TYPE_3__ {int (* start ) (struct hnae3_handle*) ;} ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 struct hnae3_handle* hns3_get_handle (struct net_device*) ; 
 int hns3_lp_setup (struct net_device*,int,int) ; 
 int hns3_nic_reset_all_ring (struct hnae3_handle*) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,int) ; 
 int stub1 (struct hnae3_handle*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int hns3_lp_up(struct net_device *ndev, enum hnae3_loop loop_mode)
{
	struct hnae3_handle *h = hns3_get_handle(ndev);
	int ret;

	if (!h->ae_algo->ops->start)
		return -EOPNOTSUPP;

	ret = hns3_nic_reset_all_ring(h);
	if (ret)
		return ret;

	ret = h->ae_algo->ops->start(h);
	if (ret) {
		netdev_err(ndev,
			   "hns3_lb_up ae start return error: %d\n", ret);
		return ret;
	}

	ret = hns3_lp_setup(ndev, loop_mode, true);
	usleep_range(10000, 20000);

	return ret;
}