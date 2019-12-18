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
typedef  int u32 ;
struct TYPE_4__ {int count; scalar_t__ offset; } ;
struct TYPE_6__ {TYPE_1__ send_table; } ;
struct TYPE_5__ {TYPE_3__ v5_msg; } ;
struct nvsp_message {TYPE_2__ msg; } ;
struct net_device_context {int* tx_table; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int VRSS_SEND_TAB_SIZE ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,int) ; 
 struct net_device_context* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void netvsc_send_table(struct net_device *ndev,
			      const struct nvsp_message *nvmsg)
{
	struct net_device_context *net_device_ctx = netdev_priv(ndev);
	u32 count, *tab;
	int i;

	count = nvmsg->msg.v5_msg.send_table.count;
	if (count != VRSS_SEND_TAB_SIZE) {
		netdev_err(ndev, "Received wrong send-table size:%u\n", count);
		return;
	}

	tab = (u32 *)((unsigned long)&nvmsg->msg.v5_msg.send_table +
		      nvmsg->msg.v5_msg.send_table.offset);

	for (i = 0; i < count; i++)
		net_device_ctx->tx_table[i] = tab[i];
}