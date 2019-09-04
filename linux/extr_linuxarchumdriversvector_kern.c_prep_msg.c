#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  sg_ok; } ;
struct vector_private {scalar_t__ header_size; TYPE_1__ estats; int /*<<< orphan*/  (* form_header ) (int /*<<< orphan*/ ,struct sk_buff*,struct vector_private*) ;} ;
struct sk_buff {scalar_t__ len; scalar_t__ data_len; int /*<<< orphan*/  data; } ;
struct iovec {scalar_t__ iov_len; int /*<<< orphan*/  iov_base; } ;
typedef  int /*<<< orphan*/  skb_frag_t ;
struct TYPE_4__ {int nr_frags; int /*<<< orphan*/ * frags; } ;

/* Variables and functions */
 int MAX_IOV_SIZE ; 
 int /*<<< orphan*/  skb_frag_address_safe (int /*<<< orphan*/ *) ; 
 scalar_t__ skb_frag_size (int /*<<< orphan*/ *) ; 
 scalar_t__ skb_linearize (struct sk_buff*) ; 
 TYPE_2__* skb_shinfo (struct sk_buff*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct sk_buff*,struct vector_private*) ; 

__attribute__((used)) static int prep_msg(struct vector_private *vp,
	struct sk_buff *skb,
	struct iovec *iov)
{
	int iov_index = 0;
	int nr_frags, frag;
	skb_frag_t *skb_frag;

	nr_frags = skb_shinfo(skb)->nr_frags;
	if (nr_frags > MAX_IOV_SIZE) {
		if (skb_linearize(skb) != 0)
			goto drop;
	}
	if (vp->header_size > 0) {
		iov[iov_index].iov_len = vp->header_size;
		vp->form_header(iov[iov_index].iov_base, skb, vp);
		iov_index++;
	}
	iov[iov_index].iov_base = skb->data;
	if (nr_frags > 0) {
		iov[iov_index].iov_len = skb->len - skb->data_len;
		vp->estats.sg_ok++;
	} else
		iov[iov_index].iov_len = skb->len;
	iov_index++;
	for (frag = 0; frag < nr_frags; frag++) {
		skb_frag = &skb_shinfo(skb)->frags[frag];
		iov[iov_index].iov_base = skb_frag_address_safe(skb_frag);
		iov[iov_index].iov_len = skb_frag_size(skb_frag);
		iov_index++;
	}
	return iov_index;
drop:
	return -1;
}