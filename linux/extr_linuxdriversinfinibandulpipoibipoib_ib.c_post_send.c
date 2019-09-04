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
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int dummy; } ;
struct ipoib_tx_buf {struct sk_buff* skb; } ;
struct TYPE_6__ {unsigned int wr_id; int /*<<< orphan*/  opcode; } ;
struct TYPE_4__ {int hlen; TYPE_3__ wr; void* header; int /*<<< orphan*/  mss; struct ib_ah* ah; int /*<<< orphan*/  remote_qpn; } ;
struct ipoib_dev_priv {TYPE_1__ tx_wr; int /*<<< orphan*/  qp; } ;
struct ib_ah {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  gso_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  IB_WR_LSO ; 
 int /*<<< orphan*/  IB_WR_SEND ; 
 int ib_post_send (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipoib_build_sge (struct ipoib_dev_priv*,struct ipoib_tx_buf*) ; 
 TYPE_2__* skb_shinfo (struct sk_buff*) ; 

__attribute__((used)) static inline int post_send(struct ipoib_dev_priv *priv,
			    unsigned int wr_id,
			    struct ib_ah *address, u32 dqpn,
			    struct ipoib_tx_buf *tx_req,
			    void *head, int hlen)
{
	struct sk_buff *skb = tx_req->skb;

	ipoib_build_sge(priv, tx_req);

	priv->tx_wr.wr.wr_id	= wr_id;
	priv->tx_wr.remote_qpn	= dqpn;
	priv->tx_wr.ah		= address;

	if (head) {
		priv->tx_wr.mss		= skb_shinfo(skb)->gso_size;
		priv->tx_wr.header	= head;
		priv->tx_wr.hlen	= hlen;
		priv->tx_wr.wr.opcode	= IB_WR_LSO;
	} else
		priv->tx_wr.wr.opcode	= IB_WR_SEND;

	return ib_post_send(priv->qp, &priv->tx_wr.wr, NULL);
}