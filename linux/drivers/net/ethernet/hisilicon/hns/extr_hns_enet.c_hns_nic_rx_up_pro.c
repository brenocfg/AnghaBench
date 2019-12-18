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
struct sk_buff {int /*<<< orphan*/  protocol; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {struct net_device* dev; } ;
struct hns_nic_ring_data {TYPE_1__ napi; } ;

/* Variables and functions */
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,struct net_device*) ; 
 int /*<<< orphan*/  napi_gro_receive (TYPE_1__*,struct sk_buff*) ; 

__attribute__((used)) static void hns_nic_rx_up_pro(struct hns_nic_ring_data *ring_data,
			      struct sk_buff *skb)
{
	struct net_device *ndev = ring_data->napi.dev;

	skb->protocol = eth_type_trans(skb, ndev);
	(void)napi_gro_receive(&ring_data->napi, skb);
}