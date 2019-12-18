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
typedef  int u32 ;
struct sk_buff {int dummy; } ;
struct page {int dummy; } ;
struct mt7601u_rxwi {int rxinfo; } ;
struct mt7601u_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  MT_RXINFO_L2PAD ; 
 struct sk_buff* alloc_skb (int,int /*<<< orphan*/ ) ; 
 int cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err_ratelimited (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  get_page (struct page*) ; 
 int ieee80211_get_hdrlen_from_buf (void*,int) ; 
 int mt76_mac_process_rx (struct mt7601u_dev*,struct sk_buff*,void*,struct mt7601u_rxwi*) ; 
 int page_address (struct page*) ; 
 int /*<<< orphan*/  skb_add_rx_frag (struct sk_buff*,int /*<<< orphan*/ ,struct page*,void*,int,int) ; 
 int /*<<< orphan*/  skb_put_data (struct sk_buff*,void*,int) ; 
 int skb_tailroom (struct sk_buff*) ; 

__attribute__((used)) static struct sk_buff *
mt7601u_rx_skb_from_seg(struct mt7601u_dev *dev, struct mt7601u_rxwi *rxwi,
			void *data, u32 seg_len, u32 truesize, struct page *p)
{
	struct sk_buff *skb;
	u32 true_len, hdr_len = 0, copy, frag;

	skb = alloc_skb(p ? 128 : seg_len, GFP_ATOMIC);
	if (!skb)
		return NULL;

	true_len = mt76_mac_process_rx(dev, skb, data, rxwi);
	if (!true_len || true_len > seg_len)
		goto bad_frame;

	hdr_len = ieee80211_get_hdrlen_from_buf(data, true_len);
	if (!hdr_len)
		goto bad_frame;

	if (rxwi->rxinfo & cpu_to_le32(MT_RXINFO_L2PAD)) {
		skb_put_data(skb, data, hdr_len);

		data += hdr_len + 2;
		true_len -= hdr_len;
		hdr_len = 0;
	}

	/* If not doing paged RX allocated skb will always have enough space */
	copy = (true_len <= skb_tailroom(skb)) ? true_len : hdr_len + 8;
	frag = true_len - copy;

	skb_put_data(skb, data, copy);
	data += copy;

	if (frag) {
		skb_add_rx_frag(skb, 0, p, data - page_address(p),
				frag, truesize);
		get_page(p);
	}

	return skb;

bad_frame:
	dev_err_ratelimited(dev->dev, "Error: incorrect frame len:%u hdr:%u\n",
			    true_len, hdr_len);
	dev_kfree_skb(skb);
	return NULL;
}