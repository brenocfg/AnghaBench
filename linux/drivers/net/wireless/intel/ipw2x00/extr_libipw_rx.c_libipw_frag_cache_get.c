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
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {int dummy; } ;
struct libipw_hdr_4addr {int /*<<< orphan*/  addr1; int /*<<< orphan*/  addr2; int /*<<< orphan*/  seq_ctl; } ;
struct libipw_frag_entry {unsigned int seq; unsigned int last_frag; struct sk_buff* skb; int /*<<< orphan*/  dst_addr; int /*<<< orphan*/  src_addr; int /*<<< orphan*/  first_frag_time; } ;
struct libipw_device {size_t frag_next_idx; struct libipw_frag_entry* frag_cache; TYPE_1__* dev; } ;
struct TYPE_2__ {scalar_t__ mtu; } ;

/* Variables and functions */
 scalar_t__ ETH_ALEN ; 
 size_t LIBIPW_FRAG_CACHE_LEN ; 
 unsigned int WLAN_GET_SEQ_FRAG (int /*<<< orphan*/ ) ; 
 unsigned int WLAN_GET_SEQ_SEQ (int /*<<< orphan*/ ) ; 
 struct sk_buff* dev_alloc_skb (scalar_t__) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 struct libipw_frag_entry* libipw_frag_cache_find (struct libipw_device*,unsigned int,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static struct sk_buff *libipw_frag_cache_get(struct libipw_device *ieee,
						struct libipw_hdr_4addr *hdr)
{
	struct sk_buff *skb = NULL;
	u16 sc;
	unsigned int frag, seq;
	struct libipw_frag_entry *entry;

	sc = le16_to_cpu(hdr->seq_ctl);
	frag = WLAN_GET_SEQ_FRAG(sc);
	seq = WLAN_GET_SEQ_SEQ(sc);

	if (frag == 0) {
		/* Reserve enough space to fit maximum frame length */
		skb = dev_alloc_skb(ieee->dev->mtu +
				    sizeof(struct libipw_hdr_4addr) +
				    8 /* LLC */  +
				    2 /* alignment */  +
				    8 /* WEP */  + ETH_ALEN /* WDS */ );
		if (skb == NULL)
			return NULL;

		entry = &ieee->frag_cache[ieee->frag_next_idx];
		ieee->frag_next_idx++;
		if (ieee->frag_next_idx >= LIBIPW_FRAG_CACHE_LEN)
			ieee->frag_next_idx = 0;

		if (entry->skb != NULL)
			dev_kfree_skb_any(entry->skb);

		entry->first_frag_time = jiffies;
		entry->seq = seq;
		entry->last_frag = frag;
		entry->skb = skb;
		memcpy(entry->src_addr, hdr->addr2, ETH_ALEN);
		memcpy(entry->dst_addr, hdr->addr1, ETH_ALEN);
	} else {
		/* received a fragment of a frame for which the head fragment
		 * should have already been received */
		entry = libipw_frag_cache_find(ieee, seq, frag, hdr->addr2,
						  hdr->addr1);
		if (entry != NULL) {
			entry->last_frag = frag;
			skb = entry->skb;
		}
	}

	return skb;
}