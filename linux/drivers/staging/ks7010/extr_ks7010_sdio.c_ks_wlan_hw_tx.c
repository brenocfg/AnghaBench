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
struct sk_buff {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  tx_dev_lock; } ;
struct TYPE_3__ {size_t qtail; scalar_t__* buff; } ;
struct ks_wlan_private {int /*<<< orphan*/  rw_dwork; int /*<<< orphan*/  wq; TYPE_2__ tx_dev; TYPE_1__ hostt; int /*<<< orphan*/  net_dev; } ;
struct hostif_hdr {int /*<<< orphan*/  event; } ;

/* Variables and functions */
 scalar_t__ HIF_DATA_REQ ; 
 scalar_t__ HIF_REQ_MAX ; 
 int SME_EVENT_BUFF_SIZE ; 
 int enqueue_txdev (struct ks_wlan_private*,void*,unsigned long,void (*) (struct ks_wlan_private*,struct sk_buff*),struct sk_buff*) ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ txq_has_space (struct ks_wlan_private*) ; 

int ks_wlan_hw_tx(struct ks_wlan_private *priv, void *p, unsigned long size,
		  void (*complete_handler)(struct ks_wlan_private *priv,
					   struct sk_buff *skb),
		  struct sk_buff *skb)
{
	int result;
	struct hostif_hdr *hdr;

	hdr = (struct hostif_hdr *)p;

	if (le16_to_cpu(hdr->event) < HIF_DATA_REQ ||
	    le16_to_cpu(hdr->event) > HIF_REQ_MAX) {
		netdev_err(priv->net_dev, "unknown event=%04X\n", hdr->event);
		return 0;
	}

	/* add event to hostt buffer */
	priv->hostt.buff[priv->hostt.qtail] = le16_to_cpu(hdr->event);
	priv->hostt.qtail = (priv->hostt.qtail + 1) % SME_EVENT_BUFF_SIZE;

	spin_lock(&priv->tx_dev.tx_dev_lock);
	result = enqueue_txdev(priv, p, size, complete_handler, skb);
	spin_unlock(&priv->tx_dev.tx_dev_lock);

	if (txq_has_space(priv))
		queue_delayed_work(priv->wq, &priv->rw_dwork, 0);

	return result;
}