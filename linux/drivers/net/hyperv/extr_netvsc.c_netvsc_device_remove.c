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
struct netvsc_device {int num_chn; TYPE_1__* chan_table; } ;
struct net_device_context {int /*<<< orphan*/  nvdev; } ;
struct net_device {int dummy; } ;
struct hv_device {int /*<<< orphan*/  channel; } ;
struct TYPE_2__ {int /*<<< orphan*/  napi; } ;

/* Variables and functions */
 int /*<<< orphan*/  RCU_INIT_POINTER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ VERSION_WIN10 ; 
 int /*<<< orphan*/  free_netvsc_device_rcu (struct netvsc_device*) ; 
 struct net_device* hv_get_drvdata (struct hv_device*) ; 
 int /*<<< orphan*/  netdev_dbg (struct net_device*,char*) ; 
 struct net_device_context* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_napi_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netvsc_revoke_recv_buf (struct hv_device*,struct netvsc_device*,struct net_device*) ; 
 int /*<<< orphan*/  netvsc_revoke_send_buf (struct hv_device*,struct netvsc_device*,struct net_device*) ; 
 int /*<<< orphan*/  netvsc_teardown_recv_gpadl (struct hv_device*,struct netvsc_device*,struct net_device*) ; 
 int /*<<< orphan*/  netvsc_teardown_send_gpadl (struct hv_device*,struct netvsc_device*,struct net_device*) ; 
 struct netvsc_device* rtnl_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmbus_close (int /*<<< orphan*/ ) ; 
 scalar_t__ vmbus_proto_version ; 

void netvsc_device_remove(struct hv_device *device)
{
	struct net_device *ndev = hv_get_drvdata(device);
	struct net_device_context *net_device_ctx = netdev_priv(ndev);
	struct netvsc_device *net_device
		= rtnl_dereference(net_device_ctx->nvdev);
	int i;

	/*
	 * Revoke receive buffer. If host is pre-Win2016 then tear down
	 * receive buffer GPADL. Do the same for send buffer.
	 */
	netvsc_revoke_recv_buf(device, net_device, ndev);
	if (vmbus_proto_version < VERSION_WIN10)
		netvsc_teardown_recv_gpadl(device, net_device, ndev);

	netvsc_revoke_send_buf(device, net_device, ndev);
	if (vmbus_proto_version < VERSION_WIN10)
		netvsc_teardown_send_gpadl(device, net_device, ndev);

	RCU_INIT_POINTER(net_device_ctx->nvdev, NULL);

	/* And disassociate NAPI context from device */
	for (i = 0; i < net_device->num_chn; i++)
		netif_napi_del(&net_device->chan_table[i].napi);

	/*
	 * At this point, no one should be accessing net_device
	 * except in here
	 */
	netdev_dbg(ndev, "net device safe to remove\n");

	/* Now, we can close the channel safely */
	vmbus_close(device->channel);

	/*
	 * If host is Win2016 or higher then we do the GPADL tear down
	 * here after VMBus is closed.
	*/
	if (vmbus_proto_version >= VERSION_WIN10) {
		netvsc_teardown_recv_gpadl(device, net_device, ndev);
		netvsc_teardown_send_gpadl(device, net_device, ndev);
	}

	/* Release all resources */
	free_netvsc_device_rcu(net_device);
}