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
struct TYPE_4__ {TYPE_1__* ops; } ;
struct TYPE_3__ {int (* add_uc_addr ) (struct hnae3_handle*,unsigned char const*) ;} ;

/* Variables and functions */
 struct hnae3_handle* hns3_get_handle (struct net_device*) ; 
 int stub1 (struct hnae3_handle*,unsigned char const*) ; 

__attribute__((used)) static int hns3_nic_uc_sync(struct net_device *netdev,
			    const unsigned char *addr)
{
	struct hnae3_handle *h = hns3_get_handle(netdev);

	if (h->ae_algo->ops->add_uc_addr)
		return h->ae_algo->ops->add_uc_addr(h, addr);

	return 0;
}