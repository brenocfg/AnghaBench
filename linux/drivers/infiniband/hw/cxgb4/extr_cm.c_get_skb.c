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
struct sk_buff {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 struct sk_buff* alloc_skb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_cloned (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_get (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_is_nonlinear (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_reset_transport_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_trim (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t4_set_arp_err_handler (struct sk_buff*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct sk_buff *get_skb(struct sk_buff *skb, int len, gfp_t gfp)
{
	if (skb && !skb_is_nonlinear(skb) && !skb_cloned(skb)) {
		skb_trim(skb, 0);
		skb_get(skb);
		skb_reset_transport_header(skb);
	} else {
		skb = alloc_skb(len, gfp);
		if (!skb)
			return NULL;
	}
	t4_set_arp_err_handler(skb, NULL, NULL);
	return skb;
}