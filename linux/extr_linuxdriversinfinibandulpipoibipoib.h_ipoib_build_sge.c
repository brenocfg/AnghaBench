#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  void* u64 ;
struct sk_buff {int dummy; } ;
struct ipoib_tx_buf {void** mapping; struct sk_buff* skb; } ;
struct TYPE_6__ {int num_sge; } ;
struct TYPE_7__ {TYPE_2__ wr; } ;
struct ipoib_dev_priv {TYPE_3__ tx_wr; TYPE_1__* tx_sge; } ;
typedef  int /*<<< orphan*/  skb_frag_t ;
struct TYPE_8__ {int nr_frags; int /*<<< orphan*/ * frags; } ;
struct TYPE_5__ {scalar_t__ length; void* addr; } ;

/* Variables and functions */
 scalar_t__ skb_frag_size (int /*<<< orphan*/ *) ; 
 scalar_t__ skb_headlen (struct sk_buff*) ; 
 TYPE_4__* skb_shinfo (struct sk_buff*) ; 

__attribute__((used)) static inline void ipoib_build_sge(struct ipoib_dev_priv *priv,
				   struct ipoib_tx_buf *tx_req)
{
	int i, off;
	struct sk_buff *skb = tx_req->skb;
	skb_frag_t *frags = skb_shinfo(skb)->frags;
	int nr_frags = skb_shinfo(skb)->nr_frags;
	u64 *mapping = tx_req->mapping;

	if (skb_headlen(skb)) {
		priv->tx_sge[0].addr         = mapping[0];
		priv->tx_sge[0].length       = skb_headlen(skb);
		off = 1;
	} else
		off = 0;

	for (i = 0; i < nr_frags; ++i) {
		priv->tx_sge[i + off].addr = mapping[i + off];
		priv->tx_sge[i + off].length = skb_frag_size(&frags[i]);
	}
	priv->tx_wr.wr.num_sge	     = nr_frags + off;
}