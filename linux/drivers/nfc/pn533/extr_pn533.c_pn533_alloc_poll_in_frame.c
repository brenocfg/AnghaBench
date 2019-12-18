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
struct pn533_poll_modulations {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct pn533 {int dummy; } ;

/* Variables and functions */
 struct sk_buff* pn533_alloc_skb (struct pn533*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_put_data (struct sk_buff*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct sk_buff *pn533_alloc_poll_in_frame(struct pn533 *dev,
					struct pn533_poll_modulations *mod)
{
	struct sk_buff *skb;

	skb = pn533_alloc_skb(dev, mod->len);
	if (!skb)
		return NULL;

	skb_put_data(skb, &mod->data, mod->len);

	return skb;
}