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
typedef  int /*<<< orphan*/  u8 ;
struct tty_struct {struct ser_device* disc_data; } ;
struct sk_buff {int /*<<< orphan*/  protocol; } ;
struct TYPE_4__ {int /*<<< orphan*/  use_stx; } ;
struct ser_device {TYPE_3__* dev; int /*<<< orphan*/  tx_started; TYPE_1__ common; } ;
struct TYPE_5__ {int rx_bytes; int /*<<< orphan*/  rx_dropped; int /*<<< orphan*/  rx_packets; } ;
struct TYPE_6__ {TYPE_2__ stats; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ETH_P_CAIF ; 
 int /*<<< orphan*/  debugfs_rx (struct ser_device*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 struct sk_buff* netdev_alloc_skb (TYPE_3__*,int) ; 
 int netif_rx_ni (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_put_data (struct sk_buff*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  skb_reset_mac_header (struct sk_buff*) ; 
 int /*<<< orphan*/  update_tty_status (struct ser_device*) ; 

__attribute__((used)) static void ldisc_receive(struct tty_struct *tty, const u8 *data,
			char *flags, int count)
{
	struct sk_buff *skb = NULL;
	struct ser_device *ser;
	int ret;

	ser = tty->disc_data;

	/*
	 * NOTE: flags may contain information about break or overrun.
	 * This is not yet handled.
	 */


	/*
	 * Workaround for garbage at start of transmission,
	 * only enable if STX handling is not enabled.
	 */
	if (!ser->common.use_stx && !ser->tx_started) {
		dev_info(&ser->dev->dev,
			"Bytes received before initial transmission -"
			"bytes discarded.\n");
		return;
	}

	BUG_ON(ser->dev == NULL);

	/* Get a suitable caif packet and copy in data. */
	skb = netdev_alloc_skb(ser->dev, count+1);
	if (skb == NULL)
		return;
	skb_put_data(skb, data, count);

	skb->protocol = htons(ETH_P_CAIF);
	skb_reset_mac_header(skb);
	debugfs_rx(ser, data, count);
	/* Push received packet up the stack. */
	ret = netif_rx_ni(skb);
	if (!ret) {
		ser->dev->stats.rx_packets++;
		ser->dev->stats.rx_bytes += count;
	} else
		++ser->dev->stats.rx_dropped;
	update_tty_status(ser);
}