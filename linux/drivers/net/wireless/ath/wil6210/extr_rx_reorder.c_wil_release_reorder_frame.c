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
struct wil_tid_ampdu_rx {int /*<<< orphan*/  head_seq_num; struct sk_buff** reorder_buf; int /*<<< orphan*/  stored_mpdu_num; } ;
struct sk_buff {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  seq_inc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wil_netif_rx_any (struct sk_buff*,struct net_device*) ; 

__attribute__((used)) static void wil_release_reorder_frame(struct net_device *ndev,
				      struct wil_tid_ampdu_rx *r,
				      int index)
{
	struct sk_buff *skb = r->reorder_buf[index];

	if (!skb)
		goto no_frame;

	/* release the frame from the reorder ring buffer */
	r->stored_mpdu_num--;
	r->reorder_buf[index] = NULL;
	wil_netif_rx_any(skb, ndev);

no_frame:
	r->head_seq_num = seq_inc(r->head_seq_num);
}