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
typedef  scalar_t__ u16 ;
struct TYPE_5__ {scalar_t__ sub_channel_index; } ;
struct TYPE_6__ {TYPE_2__ offer; } ;
struct vmbus_channel {TYPE_3__ offermsg; TYPE_1__* primary_channel; } ;
struct netvsc_device {scalar_t__ num_chn; int /*<<< orphan*/  subchan_open; int /*<<< orphan*/  open_chn; struct netvsc_channel* chan_table; } ;
struct netvsc_channel {int /*<<< orphan*/  napi; struct vmbus_channel* channel; } ;
struct net_device_context {int /*<<< orphan*/  nvdev; } ;
struct net_device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  device_obj; } ;

/* Variables and functions */
 int /*<<< orphan*/  HV_CALL_ISR ; 
 scalar_t__ atomic_inc_return (int /*<<< orphan*/ *) ; 
 struct net_device* hv_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  napi_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_notice (struct net_device*,char*,int) ; 
 struct net_device_context* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netvsc_channel_cb ; 
 int /*<<< orphan*/  netvsc_ring_bytes ; 
 struct netvsc_device* rcu_dereference_raw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_channel_read_mode (struct vmbus_channel*,int /*<<< orphan*/ ) ; 
 int vmbus_open (struct vmbus_channel*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct netvsc_channel*) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void netvsc_sc_open(struct vmbus_channel *new_sc)
{
	struct net_device *ndev =
		hv_get_drvdata(new_sc->primary_channel->device_obj);
	struct net_device_context *ndev_ctx = netdev_priv(ndev);
	struct netvsc_device *nvscdev;
	u16 chn_index = new_sc->offermsg.offer.sub_channel_index;
	struct netvsc_channel *nvchan;
	int ret;

	/* This is safe because this callback only happens when
	 * new device is being setup and waiting on the channel_init_wait.
	 */
	nvscdev = rcu_dereference_raw(ndev_ctx->nvdev);
	if (!nvscdev || chn_index >= nvscdev->num_chn)
		return;

	nvchan = nvscdev->chan_table + chn_index;

	/* Because the device uses NAPI, all the interrupt batching and
	 * control is done via Net softirq, not the channel handling
	 */
	set_channel_read_mode(new_sc, HV_CALL_ISR);

	/* Set the channel before opening.*/
	nvchan->channel = new_sc;

	ret = vmbus_open(new_sc, netvsc_ring_bytes,
			 netvsc_ring_bytes, NULL, 0,
			 netvsc_channel_cb, nvchan);
	if (ret == 0)
		napi_enable(&nvchan->napi);
	else
		netdev_notice(ndev, "sub channel open failed: %d\n", ret);

	if (atomic_inc_return(&nvscdev->open_chn) == nvscdev->num_chn)
		wake_up(&nvscdev->subchan_open);
}