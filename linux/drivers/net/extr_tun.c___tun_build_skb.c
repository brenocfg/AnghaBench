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
struct TYPE_2__ {int /*<<< orphan*/  sk; } ;
struct tun_file {TYPE_1__ socket; } ;
struct sk_buff {int dummy; } ;
struct page_frag {int offset; int /*<<< orphan*/  page; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct sk_buff* ERR_PTR (int /*<<< orphan*/ ) ; 
 struct sk_buff* build_skb (char*,int) ; 
 int /*<<< orphan*/  get_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_set_owner_w (struct sk_buff*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct sk_buff *__tun_build_skb(struct tun_file *tfile,
				       struct page_frag *alloc_frag, char *buf,
				       int buflen, int len, int pad)
{
	struct sk_buff *skb = build_skb(buf, buflen);

	if (!skb)
		return ERR_PTR(-ENOMEM);

	skb_reserve(skb, pad);
	skb_put(skb, len);
	skb_set_owner_w(skb, tfile->socket.sk);

	get_page(alloc_frag->page);
	alloc_frag->offset += buflen;

	return skb;
}