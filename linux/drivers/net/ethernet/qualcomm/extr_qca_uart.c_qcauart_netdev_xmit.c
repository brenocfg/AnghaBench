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
typedef  scalar_t__ u8 ;
struct sk_buff {scalar_t__ len; int /*<<< orphan*/  data; } ;
struct qcauart {int tx_left; scalar_t__* tx_buffer; scalar_t__* tx_head; int /*<<< orphan*/  lock; int /*<<< orphan*/  serdev; int /*<<< orphan*/  net_dev; } ;
struct net_device_stats {int tx_bytes; } ;
struct net_device {struct net_device_stats stats; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;

/* Variables and functions */
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 scalar_t__ QCAFRM_MIN_LEN ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  memset (scalar_t__*,int /*<<< orphan*/ ,scalar_t__) ; 
 struct qcauart* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netdev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_trans_update (struct net_device*) ; 
 int /*<<< orphan*/  qcafrm_create_footer (scalar_t__*) ; 
 int /*<<< orphan*/  qcafrm_create_header (scalar_t__*,scalar_t__) ; 
 int serdev_device_write_buf (int /*<<< orphan*/ ,scalar_t__*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static netdev_tx_t
qcauart_netdev_xmit(struct sk_buff *skb, struct net_device *dev)
{
	struct net_device_stats *n_stats = &dev->stats;
	struct qcauart *qca = netdev_priv(dev);
	u8 pad_len = 0;
	int written;
	u8 *pos;

	spin_lock(&qca->lock);

	WARN_ON(qca->tx_left);

	if (!netif_running(dev))  {
		spin_unlock(&qca->lock);
		netdev_warn(qca->net_dev, "xmit: iface is down\n");
		goto out;
	}

	pos = qca->tx_buffer;

	if (skb->len < QCAFRM_MIN_LEN)
		pad_len = QCAFRM_MIN_LEN - skb->len;

	pos += qcafrm_create_header(pos, skb->len + pad_len);

	memcpy(pos, skb->data, skb->len);
	pos += skb->len;

	if (pad_len) {
		memset(pos, 0, pad_len);
		pos += pad_len;
	}

	pos += qcafrm_create_footer(pos);

	netif_stop_queue(qca->net_dev);

	written = serdev_device_write_buf(qca->serdev, qca->tx_buffer,
					  pos - qca->tx_buffer);
	if (written > 0) {
		qca->tx_left = (pos - qca->tx_buffer) - written;
		qca->tx_head = qca->tx_buffer + written;
		n_stats->tx_bytes += written;
	}
	spin_unlock(&qca->lock);

	netif_trans_update(dev);
out:
	dev_kfree_skb_any(skb);
	return NETDEV_TX_OK;
}