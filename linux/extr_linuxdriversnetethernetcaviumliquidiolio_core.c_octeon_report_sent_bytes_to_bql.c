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
struct sk_buff {int /*<<< orphan*/  len; int /*<<< orphan*/  dev; } ;
struct octnet_buf_free_info {struct sk_buff* skb; } ;
struct octeon_soft_command {struct sk_buff* callback_arg; } ;
struct netdev_queue {int dummy; } ;

/* Variables and functions */
#define  REQTYPE_NORESP_NET 131 
#define  REQTYPE_NORESP_NET_SG 130 
#define  REQTYPE_RESP_NET 129 
#define  REQTYPE_RESP_NET_SG 128 
 struct netdev_queue* netdev_get_tx_queue (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_tx_sent_queue (struct netdev_queue*,int /*<<< orphan*/ ) ; 
 int netif_xmit_stopped (struct netdev_queue*) ; 
 int /*<<< orphan*/  skb_get_queue_mapping (struct sk_buff*) ; 

int octeon_report_sent_bytes_to_bql(void *buf, int reqtype)
{
	struct octnet_buf_free_info *finfo;
	struct sk_buff *skb;
	struct octeon_soft_command *sc;
	struct netdev_queue *txq;

	switch (reqtype) {
	case REQTYPE_NORESP_NET:
	case REQTYPE_NORESP_NET_SG:
		finfo = buf;
		skb = finfo->skb;
		break;

	case REQTYPE_RESP_NET_SG:
	case REQTYPE_RESP_NET:
		sc = buf;
		skb = sc->callback_arg;
		break;

	default:
		return 0;
	}

	txq = netdev_get_tx_queue(skb->dev, skb_get_queue_mapping(skb));
	netdev_tx_sent_queue(txq, skb->len);

	return netif_xmit_stopped(txq);
}