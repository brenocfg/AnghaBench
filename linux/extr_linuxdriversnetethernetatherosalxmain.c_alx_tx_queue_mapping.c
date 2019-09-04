#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {unsigned int queue_mapping; } ;
struct alx_tx_queue {int dummy; } ;
struct alx_priv {unsigned int num_txq; TYPE_1__** qnapi; } ;
struct TYPE_2__ {struct alx_tx_queue* txq; } ;

/* Variables and functions */

__attribute__((used)) static struct alx_tx_queue *alx_tx_queue_mapping(struct alx_priv *alx,
						 struct sk_buff *skb)
{
	unsigned int r_idx = skb->queue_mapping;

	if (r_idx >= alx->num_txq)
		r_idx = r_idx % alx->num_txq;

	return alx->qnapi[r_idx]->txq;
}