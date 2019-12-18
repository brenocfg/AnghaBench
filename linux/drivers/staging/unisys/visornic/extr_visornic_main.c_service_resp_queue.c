#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  got_enbdisack; int /*<<< orphan*/  xmit_fail; int /*<<< orphan*/  got_xmit_done; int /*<<< orphan*/  got_rcv; } ;
struct visornic_devdata {int enab_dis_acked; int server_down; int server_change_state; int enabled; int /*<<< orphan*/  priv_lock; struct net_device* netdev; TYPE_3__ chstat; int /*<<< orphan*/  xmitbufhead; int /*<<< orphan*/  flow_control_lower_hits; int /*<<< orphan*/  lower_threshold_net_xmits; TYPE_1__* dev; } ;
struct TYPE_9__ {int enable; scalar_t__ context; } ;
struct TYPE_7__ {int /*<<< orphan*/  xmt_done_result; } ;
struct TYPE_10__ {int type; TYPE_4__ enbdis; scalar_t__ buf; TYPE_2__ xmtdone; } ;
struct uiscmdrsp {TYPE_5__ net; } ;
struct sk_buff {struct net_device* dev; } ;
struct net_device {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  visorchannel; } ;

/* Variables and functions */
 int /*<<< orphan*/  IOCHAN_FROM_IOPART ; 
#define  NET_CONNECT_STATUS 131 
#define  NET_RCV 130 
#define  NET_RCV_ENBDIS_ACK 129 
#define  NET_XMIT_DONE 128 
 int /*<<< orphan*/  kfree_skb (scalar_t__) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_on (struct net_device*) ; 
 int /*<<< orphan*/  netif_queue_stopped (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int /*<<< orphan*/  skb_unlink (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ visorchannel_signalremove (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct uiscmdrsp*) ; 
 int visornic_rx (struct uiscmdrsp*) ; 
 int /*<<< orphan*/  vnic_hit_low_watermark (struct visornic_devdata*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void service_resp_queue(struct uiscmdrsp *cmdrsp,
			       struct visornic_devdata *devdata,
			       int *rx_work_done, int budget)
{
	unsigned long flags;
	struct net_device *netdev;

	while (*rx_work_done < budget) {
		/* TODO: CLIENT ACQUIRE -- Don't really need this at the
		 * moment
		 */
		/* queue empty */
		if (visorchannel_signalremove(devdata->dev->visorchannel,
					      IOCHAN_FROM_IOPART,
					      cmdrsp))
			break;

		switch (cmdrsp->net.type) {
		case NET_RCV:
			devdata->chstat.got_rcv++;
			/* process incoming packet */
			*rx_work_done += visornic_rx(cmdrsp);
			break;
		case NET_XMIT_DONE:
			spin_lock_irqsave(&devdata->priv_lock, flags);
			devdata->chstat.got_xmit_done++;
			if (cmdrsp->net.xmtdone.xmt_done_result)
				devdata->chstat.xmit_fail++;
			/* only call queue wake if we stopped it */
			netdev = ((struct sk_buff *)cmdrsp->net.buf)->dev;
			/* ASSERT netdev == vnicinfo->netdev; */
			if (netdev == devdata->netdev &&
			    netif_queue_stopped(netdev)) {
				/* check if we have crossed the lower watermark
				 * for netif_wake_queue()
				 */
				if (vnic_hit_low_watermark
				    (devdata,
				     devdata->lower_threshold_net_xmits)) {
					/* enough NET_XMITs completed
					 * so can restart netif queue
					 */
					netif_wake_queue(netdev);
					devdata->flow_control_lower_hits++;
				}
			}
			skb_unlink(cmdrsp->net.buf, &devdata->xmitbufhead);
			spin_unlock_irqrestore(&devdata->priv_lock, flags);
			kfree_skb(cmdrsp->net.buf);
			break;
		case NET_RCV_ENBDIS_ACK:
			devdata->chstat.got_enbdisack++;
			netdev = (struct net_device *)
			cmdrsp->net.enbdis.context;
			spin_lock_irqsave(&devdata->priv_lock, flags);
			devdata->enab_dis_acked = 1;
			spin_unlock_irqrestore(&devdata->priv_lock, flags);

			if (devdata->server_down &&
			    devdata->server_change_state) {
				/* Inform Linux that the link is up */
				devdata->server_down = false;
				devdata->server_change_state = false;
				netif_wake_queue(netdev);
				netif_carrier_on(netdev);
			}
			break;
		case NET_CONNECT_STATUS:
			netdev = devdata->netdev;
			if (cmdrsp->net.enbdis.enable == 1) {
				spin_lock_irqsave(&devdata->priv_lock, flags);
				devdata->enabled = cmdrsp->net.enbdis.enable;
				spin_unlock_irqrestore(&devdata->priv_lock,
						       flags);
				netif_wake_queue(netdev);
				netif_carrier_on(netdev);
			} else {
				netif_stop_queue(netdev);
				netif_carrier_off(netdev);
				spin_lock_irqsave(&devdata->priv_lock, flags);
				devdata->enabled = cmdrsp->net.enbdis.enable;
				spin_unlock_irqrestore(&devdata->priv_lock,
						       flags);
			}
			break;
		default:
			break;
		}
		/* cmdrsp is now available for reuse  */
	}
}