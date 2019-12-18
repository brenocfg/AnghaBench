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
typedef  int /*<<< orphan*/  u16 ;
struct wil6210_priv {int dummy; } ;
struct vring_rx_desc {int dummy; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int wil_rxdesc_mcast (struct vring_rx_desc*) ; 
 int wil_rxdesc_mid (struct vring_rx_desc*) ; 
 int wil_rxdesc_retry (struct vring_rx_desc*) ; 
 int /*<<< orphan*/  wil_rxdesc_seq (struct vring_rx_desc*) ; 
 int wil_rxdesc_tid (struct vring_rx_desc*) ; 
 int wil_skb_get_cid (struct sk_buff*) ; 
 struct vring_rx_desc* wil_skb_rxdesc (struct sk_buff*) ; 

__attribute__((used)) static void wil_get_reorder_params(struct wil6210_priv *wil,
				   struct sk_buff *skb, int *tid, int *cid,
				   int *mid, u16 *seq, int *mcast, int *retry)
{
	struct vring_rx_desc *d = wil_skb_rxdesc(skb);

	*tid = wil_rxdesc_tid(d);
	*cid = wil_skb_get_cid(skb);
	*mid = wil_rxdesc_mid(d);
	*seq = wil_rxdesc_seq(d);
	*mcast = wil_rxdesc_mcast(d);
	*retry = wil_rxdesc_retry(d);
}