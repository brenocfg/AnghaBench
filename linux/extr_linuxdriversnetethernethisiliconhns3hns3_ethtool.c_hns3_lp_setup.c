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
struct TYPE_3__ {int (* set_loopback ) (struct hnae3_handle*,int,int) ;int /*<<< orphan*/  (* set_promisc_mode ) (struct hnae3_handle*,int,int) ;} ;

/* Variables and functions */
 int ENOTSUPP ; 
 int EOPNOTSUPP ; 
#define  HNAE3_MAC_INTER_LOOP_MAC 129 
#define  HNAE3_MAC_INTER_LOOP_SERDES 128 
 struct hnae3_handle* hns3_get_handle (struct net_device*) ; 
 int stub1 (struct hnae3_handle*,int,int) ; 
 int /*<<< orphan*/  stub2 (struct hnae3_handle*,int,int) ; 

__attribute__((used)) static int hns3_lp_setup(struct net_device *ndev, enum hnae3_loop loop, bool en)
{
	struct hnae3_handle *h = hns3_get_handle(ndev);
	int ret;

	if (!h->ae_algo->ops->set_loopback ||
	    !h->ae_algo->ops->set_promisc_mode)
		return -EOPNOTSUPP;

	switch (loop) {
	case HNAE3_MAC_INTER_LOOP_SERDES:
	case HNAE3_MAC_INTER_LOOP_MAC:
		ret = h->ae_algo->ops->set_loopback(h, loop, en);
		break;
	default:
		ret = -ENOTSUPP;
		break;
	}

	if (ret)
		return ret;

	h->ae_algo->ops->set_promisc_mode(h, en, en);

	return ret;
}