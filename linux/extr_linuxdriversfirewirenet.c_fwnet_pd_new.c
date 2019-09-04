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
struct net_device {int dummy; } ;
struct fwnet_peer {int /*<<< orphan*/  pd_list; } ;
struct fwnet_partial_datagram {unsigned int datagram_size; unsigned int pbuf; int /*<<< orphan*/  pd_link; int /*<<< orphan*/ * skb; int /*<<< orphan*/  datagram_label; int /*<<< orphan*/  fi_list; } ;
struct fwnet_fragment_info {unsigned int datagram_size; unsigned int pbuf; int /*<<< orphan*/  pd_link; int /*<<< orphan*/ * skb; int /*<<< orphan*/  datagram_label; int /*<<< orphan*/  fi_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 unsigned int LL_RESERVED_SPACE (struct net_device*) ; 
 int /*<<< orphan*/ * dev_alloc_skb (unsigned int) ; 
 struct fwnet_partial_datagram* fwnet_frag_new (struct fwnet_partial_datagram*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  kfree (struct fwnet_partial_datagram*) ; 
 struct fwnet_partial_datagram* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (unsigned int,void*,unsigned int) ; 
 unsigned int skb_put (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  skb_reserve (int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static struct fwnet_partial_datagram *fwnet_pd_new(struct net_device *net,
		struct fwnet_peer *peer, u16 datagram_label, unsigned dg_size,
		void *frag_buf, unsigned frag_off, unsigned frag_len)
{
	struct fwnet_partial_datagram *new;
	struct fwnet_fragment_info *fi;

	new = kmalloc(sizeof(*new), GFP_ATOMIC);
	if (!new)
		goto fail;

	INIT_LIST_HEAD(&new->fi_list);
	fi = fwnet_frag_new(new, frag_off, frag_len);
	if (fi == NULL)
		goto fail_w_new;

	new->datagram_label = datagram_label;
	new->datagram_size = dg_size;
	new->skb = dev_alloc_skb(dg_size + LL_RESERVED_SPACE(net));
	if (new->skb == NULL)
		goto fail_w_fi;

	skb_reserve(new->skb, LL_RESERVED_SPACE(net));
	new->pbuf = skb_put(new->skb, dg_size);
	memcpy(new->pbuf + frag_off, frag_buf, frag_len);
	list_add_tail(&new->pd_link, &peer->pd_list);

	return new;

fail_w_fi:
	kfree(fi);
fail_w_new:
	kfree(new);
fail:
	return NULL;
}