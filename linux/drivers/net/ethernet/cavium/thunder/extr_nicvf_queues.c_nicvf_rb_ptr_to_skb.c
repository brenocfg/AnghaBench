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
typedef  int /*<<< orphan*/  u64 ;
struct sk_buff {int /*<<< orphan*/  data; } ;
struct nicvf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RCV_FRAG_LEN ; 
 struct sk_buff* build_skb (void*,int /*<<< orphan*/ ) ; 
 void* phys_to_virt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prefetch (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virt_to_page (void*) ; 

__attribute__((used)) static struct sk_buff *nicvf_rb_ptr_to_skb(struct nicvf *nic,
					   u64 rb_ptr, int len)
{
	void *data;
	struct sk_buff *skb;

	data = phys_to_virt(rb_ptr);

	/* Now build an skb to give to stack */
	skb = build_skb(data, RCV_FRAG_LEN);
	if (!skb) {
		put_page(virt_to_page(data));
		return NULL;
	}

	prefetch(skb->data);
	return skb;
}