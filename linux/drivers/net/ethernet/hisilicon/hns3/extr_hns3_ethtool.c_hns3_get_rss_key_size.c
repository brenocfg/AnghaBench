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
typedef  int /*<<< orphan*/  u32 ;
struct net_device {int dummy; } ;
struct hnae3_handle {TYPE_2__* ae_algo; } ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* get_rss_key_size ) (struct hnae3_handle*) ;} ;

/* Variables and functions */
 struct hnae3_handle* hns3_get_handle (struct net_device*) ; 
 int /*<<< orphan*/  stub1 (struct hnae3_handle*) ; 

__attribute__((used)) static u32 hns3_get_rss_key_size(struct net_device *netdev)
{
	struct hnae3_handle *h = hns3_get_handle(netdev);

	if (!h->ae_algo->ops->get_rss_key_size)
		return 0;

	return h->ae_algo->ops->get_rss_key_size(h);
}