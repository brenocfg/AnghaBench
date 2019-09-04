#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct sk_buff {int dummy; } ;
struct net_device_stats {int /*<<< orphan*/  rx_errors; int /*<<< orphan*/  rx_over_errors; } ;
struct net_device {struct net_device_stats stats; } ;
struct ican3_msg {scalar_t__ spec; int /*<<< orphan*/ * data; } ;
struct ican3_dev {struct net_device* ndev; } ;
struct can_frame {int /*<<< orphan*/ * data; int /*<<< orphan*/  can_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAN_ERR_CRTL ; 
 int /*<<< orphan*/  CAN_ERR_CRTL_RX_OVERFLOW ; 
 scalar_t__ MSG_MSGLOST ; 
 struct sk_buff* alloc_can_err_skb (struct net_device*,struct can_frame**) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_rx (struct sk_buff*) ; 

__attribute__((used)) static void ican3_handle_msglost(struct ican3_dev *mod, struct ican3_msg *msg)
{
	struct net_device *dev = mod->ndev;
	struct net_device_stats *stats = &dev->stats;
	struct can_frame *cf;
	struct sk_buff *skb;

	/*
	 * Report that communication messages with the microcontroller firmware
	 * are being lost. These are never CAN frames, so we do not generate an
	 * error frame for userspace
	 */
	if (msg->spec == MSG_MSGLOST) {
		netdev_err(mod->ndev, "lost %d control messages\n", msg->data[0]);
		return;
	}

	/*
	 * Oops, this indicates that we have lost messages in the fast queue,
	 * which are exclusively CAN messages. Our driver isn't reading CAN
	 * frames fast enough.
	 *
	 * We'll pretend that the SJA1000 told us that it ran out of buffer
	 * space, because there is not a better message for this.
	 */
	skb = alloc_can_err_skb(dev, &cf);
	if (skb) {
		cf->can_id |= CAN_ERR_CRTL;
		cf->data[1] = CAN_ERR_CRTL_RX_OVERFLOW;
		stats->rx_over_errors++;
		stats->rx_errors++;
		netif_rx(skb);
	}
}