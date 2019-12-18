#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct net_device {int dummy; } ;
struct hnae3_handle {TYPE_1__* ae_algo; } ;
struct hnae3_ae_ops {int /*<<< orphan*/  (* get_strings ) (struct hnae3_handle*,int,int /*<<< orphan*/ *) ;} ;
struct TYPE_2__ {struct hnae3_ae_ops* ops; } ;

/* Variables and functions */
#define  ETH_SS_STATS 129 
#define  ETH_SS_TEST 128 
 struct hnae3_handle* hns3_get_handle (struct net_device*) ; 
 char* hns3_get_strings_tqps (struct hnae3_handle*,char*) ; 
 int /*<<< orphan*/  stub1 (struct hnae3_handle*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (struct hnae3_handle*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hns3_get_strings(struct net_device *netdev, u32 stringset, u8 *data)
{
	struct hnae3_handle *h = hns3_get_handle(netdev);
	const struct hnae3_ae_ops *ops = h->ae_algo->ops;
	char *buff = (char *)data;

	if (!ops->get_strings)
		return;

	switch (stringset) {
	case ETH_SS_STATS:
		buff = hns3_get_strings_tqps(h, buff);
		ops->get_strings(h, stringset, (u8 *)buff);
		break;
	case ETH_SS_TEST:
		ops->get_strings(h, stringset, data);
		break;
	default:
		break;
	}
}