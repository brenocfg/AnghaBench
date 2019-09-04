#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct net_device {int dummy; } ;
struct TYPE_5__ {TYPE_1__* api; } ;
struct TYPE_4__ {int (* recv_pkt ) (TYPE_2__*,int /*<<< orphan*/ ,struct sk_buff*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  NES_DBG_CM ; 
 int /*<<< orphan*/  cm_packets_received ; 
 TYPE_2__* g_cm_core ; 
 int /*<<< orphan*/  nes_debug (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  netdev_priv (struct net_device*) ; 
 int stub1 (TYPE_2__*,int /*<<< orphan*/ ,struct sk_buff*) ; 

int nes_cm_recv(struct sk_buff *skb, struct net_device *netdevice)
{
	int rc = 0;

	cm_packets_received++;
	if ((g_cm_core) && (g_cm_core->api))
		rc = g_cm_core->api->recv_pkt(g_cm_core, netdev_priv(netdevice), skb);
	else
		nes_debug(NES_DBG_CM, "Unable to process packet for CM,"
			  " cm is not setup properly.\n");

	return rc;
}