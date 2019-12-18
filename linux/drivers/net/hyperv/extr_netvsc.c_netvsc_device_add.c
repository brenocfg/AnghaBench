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
struct netvsc_device_info {int dummy; } ;
struct netvsc_device {int /*<<< orphan*/  rcu; struct netvsc_channel* chan_table; } ;
struct TYPE_4__ {int /*<<< orphan*/  syncp; } ;
struct TYPE_3__ {int /*<<< orphan*/  syncp; } ;
struct netvsc_channel {int /*<<< orphan*/  napi; TYPE_2__ rx_stats; TYPE_1__ tx_stats; struct netvsc_device* net_device; int /*<<< orphan*/  channel; } ;
struct net_device_context {int /*<<< orphan*/  nvdev; scalar_t__* tx_table; } ;
struct net_device {int dummy; } ;
struct hv_device {int /*<<< orphan*/  channel; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct netvsc_device* ERR_PTR (int) ; 
 int /*<<< orphan*/  HV_CALL_ISR ; 
 int /*<<< orphan*/  NAPI_POLL_WEIGHT ; 
 int /*<<< orphan*/  RCU_INIT_POINTER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int VRSS_CHANNEL_MAX ; 
 int VRSS_SEND_TAB_SIZE ; 
 struct netvsc_device* alloc_net_device () ; 
 int /*<<< orphan*/  free_netvsc_device (int /*<<< orphan*/ *) ; 
 struct net_device* hv_get_drvdata (struct hv_device*) ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  napi_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_dbg (struct net_device*,char*) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,int) ; 
 struct net_device_context* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_napi_add (struct net_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_napi_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netvsc_channel_cb ; 
 int netvsc_connect_vsp (struct hv_device*,struct netvsc_device*,struct netvsc_device_info const*) ; 
 int /*<<< orphan*/  netvsc_poll ; 
 int /*<<< orphan*/  netvsc_ring_bytes ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct netvsc_device*) ; 
 int /*<<< orphan*/  set_channel_read_mode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  u64_stats_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmbus_close (int /*<<< orphan*/ ) ; 
 int vmbus_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct netvsc_channel*) ; 

struct netvsc_device *netvsc_device_add(struct hv_device *device,
				const struct netvsc_device_info *device_info)
{
	int i, ret = 0;
	struct netvsc_device *net_device;
	struct net_device *ndev = hv_get_drvdata(device);
	struct net_device_context *net_device_ctx = netdev_priv(ndev);

	net_device = alloc_net_device();
	if (!net_device)
		return ERR_PTR(-ENOMEM);

	for (i = 0; i < VRSS_SEND_TAB_SIZE; i++)
		net_device_ctx->tx_table[i] = 0;

	/* Because the device uses NAPI, all the interrupt batching and
	 * control is done via Net softirq, not the channel handling
	 */
	set_channel_read_mode(device->channel, HV_CALL_ISR);

	/* If we're reopening the device we may have multiple queues, fill the
	 * chn_table with the default channel to use it before subchannels are
	 * opened.
	 * Initialize the channel state before we open;
	 * we can be interrupted as soon as we open the channel.
	 */

	for (i = 0; i < VRSS_CHANNEL_MAX; i++) {
		struct netvsc_channel *nvchan = &net_device->chan_table[i];

		nvchan->channel = device->channel;
		nvchan->net_device = net_device;
		u64_stats_init(&nvchan->tx_stats.syncp);
		u64_stats_init(&nvchan->rx_stats.syncp);
	}

	/* Enable NAPI handler before init callbacks */
	netif_napi_add(ndev, &net_device->chan_table[0].napi,
		       netvsc_poll, NAPI_POLL_WEIGHT);

	/* Open the channel */
	ret = vmbus_open(device->channel, netvsc_ring_bytes,
			 netvsc_ring_bytes,  NULL, 0,
			 netvsc_channel_cb, net_device->chan_table);

	if (ret != 0) {
		netdev_err(ndev, "unable to open channel: %d\n", ret);
		goto cleanup;
	}

	/* Channel is opened */
	netdev_dbg(ndev, "hv_netvsc channel opened successfully\n");

	napi_enable(&net_device->chan_table[0].napi);

	/* Connect with the NetVsp */
	ret = netvsc_connect_vsp(device, net_device, device_info);
	if (ret != 0) {
		netdev_err(ndev,
			"unable to connect to NetVSP - %d\n", ret);
		goto close;
	}

	/* Writing nvdev pointer unlocks netvsc_send(), make sure chn_table is
	 * populated.
	 */
	rcu_assign_pointer(net_device_ctx->nvdev, net_device);

	return net_device;

close:
	RCU_INIT_POINTER(net_device_ctx->nvdev, NULL);
	napi_disable(&net_device->chan_table[0].napi);

	/* Now, we can close the channel safely */
	vmbus_close(device->channel);

cleanup:
	netif_napi_del(&net_device->chan_table[0].napi);
	free_netvsc_device(&net_device->rcu);

	return ERR_PTR(ret);
}