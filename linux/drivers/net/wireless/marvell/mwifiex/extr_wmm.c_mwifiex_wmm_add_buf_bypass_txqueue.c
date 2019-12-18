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
struct mwifiex_private {int /*<<< orphan*/  bypass_txq; } ;

/* Variables and functions */
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 

void
mwifiex_wmm_add_buf_bypass_txqueue(struct mwifiex_private *priv,
				   struct sk_buff *skb)
{
	skb_queue_tail(&priv->bypass_txq, skb);
}