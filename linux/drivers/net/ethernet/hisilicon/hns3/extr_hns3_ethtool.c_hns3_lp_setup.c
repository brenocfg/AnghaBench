#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct net_device {int flags; } ;
struct hnae3_handle {int /*<<< orphan*/  netdev_flags; TYPE_3__* ae_algo; TYPE_1__* pdev; } ;
typedef  enum hnae3_loop { ____Placeholder_hnae3_loop } hnae3_loop ;
struct TYPE_6__ {TYPE_2__* ops; } ;
struct TYPE_5__ {int (* set_loopback ) (struct hnae3_handle*,int,int) ;int /*<<< orphan*/  (* set_promisc_mode ) (struct hnae3_handle*,int,int) ;} ;
struct TYPE_4__ {int revision; } ;

/* Variables and functions */
 int ENOTSUPP ; 
 int EOPNOTSUPP ; 
#define  HNAE3_LOOP_APP 131 
#define  HNAE3_LOOP_PARALLEL_SERDES 130 
#define  HNAE3_LOOP_PHY 129 
#define  HNAE3_LOOP_SERIAL_SERDES 128 
 int IFF_PROMISC ; 
 int /*<<< orphan*/  hns3_enable_vlan_filter (struct net_device*,int) ; 
 struct hnae3_handle* hns3_get_handle (struct net_device*) ; 
 int /*<<< orphan*/  hns3_update_promisc_mode (struct net_device*,int /*<<< orphan*/ ) ; 
 int stub1 (struct hnae3_handle*,int,int) ; 
 int /*<<< orphan*/  stub2 (struct hnae3_handle*,int,int) ; 

__attribute__((used)) static int hns3_lp_setup(struct net_device *ndev, enum hnae3_loop loop, bool en)
{
	struct hnae3_handle *h = hns3_get_handle(ndev);
	bool vlan_filter_enable;
	int ret;

	if (!h->ae_algo->ops->set_loopback ||
	    !h->ae_algo->ops->set_promisc_mode)
		return -EOPNOTSUPP;

	switch (loop) {
	case HNAE3_LOOP_SERIAL_SERDES:
	case HNAE3_LOOP_PARALLEL_SERDES:
	case HNAE3_LOOP_APP:
	case HNAE3_LOOP_PHY:
		ret = h->ae_algo->ops->set_loopback(h, loop, en);
		break;
	default:
		ret = -ENOTSUPP;
		break;
	}

	if (ret || h->pdev->revision >= 0x21)
		return ret;

	if (en) {
		h->ae_algo->ops->set_promisc_mode(h, true, true);
	} else {
		/* recover promisc mode before loopback test */
		hns3_update_promisc_mode(ndev, h->netdev_flags);
		vlan_filter_enable = ndev->flags & IFF_PROMISC ? false : true;
		hns3_enable_vlan_filter(ndev, vlan_filter_enable);
	}

	return ret;
}