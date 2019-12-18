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
struct tun_file {int /*<<< orphan*/  napi; } ;
struct sk_buff {size_t len; size_t data_len; size_t truesize; } ;
struct page {int dummy; } ;
struct iov_iter {int nr_segs; TYPE_1__* iov; } ;
struct TYPE_2__ {size_t iov_len; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 struct sk_buff* ERR_PTR (int) ; 
 int MAX_SKB_FRAGS ; 
 size_t PAGE_SIZE ; 
 int __skb_grow (struct sk_buff*,size_t) ; 
 size_t iov_iter_single_seg_count (struct iov_iter const*) ; 
 int /*<<< orphan*/  local_bh_disable () ; 
 int /*<<< orphan*/  local_bh_enable () ; 
 int /*<<< orphan*/  napi_free_frags (int /*<<< orphan*/ *) ; 
 struct sk_buff* napi_get_frags (int /*<<< orphan*/ *) ; 
 void* netdev_alloc_frag (size_t) ; 
 int page_address (struct page*) ; 
 int /*<<< orphan*/  skb_fill_page_desc (struct sk_buff*,int,struct page*,void*,size_t) ; 
 struct page* virt_to_head_page (void*) ; 

__attribute__((used)) static struct sk_buff *tun_napi_alloc_frags(struct tun_file *tfile,
					    size_t len,
					    const struct iov_iter *it)
{
	struct sk_buff *skb;
	size_t linear;
	int err;
	int i;

	if (it->nr_segs > MAX_SKB_FRAGS + 1)
		return ERR_PTR(-ENOMEM);

	local_bh_disable();
	skb = napi_get_frags(&tfile->napi);
	local_bh_enable();
	if (!skb)
		return ERR_PTR(-ENOMEM);

	linear = iov_iter_single_seg_count(it);
	err = __skb_grow(skb, linear);
	if (err)
		goto free;

	skb->len = len;
	skb->data_len = len - linear;
	skb->truesize += skb->data_len;

	for (i = 1; i < it->nr_segs; i++) {
		size_t fragsz = it->iov[i].iov_len;
		struct page *page;
		void *frag;

		if (fragsz == 0 || fragsz > PAGE_SIZE) {
			err = -EINVAL;
			goto free;
		}
		frag = netdev_alloc_frag(fragsz);
		if (!frag) {
			err = -ENOMEM;
			goto free;
		}
		page = virt_to_head_page(frag);
		skb_fill_page_desc(skb, i - 1, page,
				   frag - page_address(page), fragsz);
	}

	return skb;
free:
	/* frees skb and all frags allocated with napi_alloc_frag() */
	napi_free_frags(&tfile->napi);
	return ERR_PTR(err);
}