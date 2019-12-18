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
struct txentry_desc {scalar_t__ iv_len; scalar_t__ length; scalar_t__ iv_offset; } ;
struct skb_frame_desc {int /*<<< orphan*/  flags; int /*<<< orphan*/  iv; } ;
struct sk_buff {scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  SKBDESC_IV_STRIPPED ; 
 struct skb_frame_desc* get_skb_frame_desc (struct sk_buff*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  memmove (scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,scalar_t__) ; 
 scalar_t__ unlikely (int) ; 

void rt2x00crypto_tx_remove_iv(struct sk_buff *skb, struct txentry_desc *txdesc)
{
	struct skb_frame_desc *skbdesc = get_skb_frame_desc(skb);

	if (unlikely(!txdesc->iv_len))
		return;

	/* Copy IV/EIV data */
	memcpy(skbdesc->iv, skb->data + txdesc->iv_offset, txdesc->iv_len);

	/* Move ieee80211 header */
	memmove(skb->data + txdesc->iv_len, skb->data, txdesc->iv_offset);

	/* Pull buffer to correct size */
	skb_pull(skb, txdesc->iv_len);
	txdesc->length -= txdesc->iv_len;

	/* IV/EIV data has officially been stripped */
	skbdesc->flags |= SKBDESC_IV_STRIPPED;
}